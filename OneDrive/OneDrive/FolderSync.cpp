#define _CRT_SECURE_NO_WARNINGS
#include "FolderSync.h"
#include "User.h"
#include <sstream>
#include "../../Request/Request/Request.h"
#include "../../Hash/Hash/Hash/Hash.h"

std::vector <std::string> tokenize(char* buff)
{
	std::vector <std::string> tokens;
	std::stringstream check1(buff);
	std::string intermediate;
	while (getline(check1, intermediate, ' '))
	{
		tokens.push_back(intermediate);
	}
	return tokens;
}

std::string correctslashes(std::string path)
{
	for (int i = 0; i < path.length(); i++)
	{
		if (path[i] == '\\') path[i] = '/';
	}
	return path;
}

std::string removelast(std::string path)
{
	int lastpos = 0;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '/' || path[i] == '\\')
		{
			lastpos = i;
		}
	}
	path = path.substr(0, lastpos);
	return path;
}

void FolderSync::RewriteHashFile()
{
	std::ofstream fout("Hashes.txt");
	for (auto it : *m_hashes)
	{
		fout << "@" << it.first << "\n#" << it.second << '\n';
	}
	fout.close();
}

FolderSync::FolderSync() :
	m_stFolderPath(),
	m_ndFolderPath()
{
	m_eof.push_back('1');
	m_eof.push_back(EOF);
	m_eot.push_back('2');
	m_eot.push_back(EOF);
}

std::filesystem::path FolderSync::getFirstFolderPath() const
{
	return this->m_stFolderPath;
}

std::filesystem::path FolderSync::getSecondFolderPath() const
{
	return this->m_ndFolderPath;
}

void FolderSync::setFirstFolderPath(const std::filesystem::path stFolderPath)
{
	this->m_stFolderPath = stFolderPath;
}

void FolderSync::setSecondFolderPath(const std::filesystem::path ndFolderPath)
{
	this->m_ndFolderPath = ndFolderPath;
}

void FolderSync::setUserDatabase(UserDatabase& userDatabase)
{
	this->m_userDatabase = std::make_unique<UserDatabase>(userDatabase);
}

void FolderSync::setHashes(std::unordered_map<std::string, std::string>& hashes)
{
	this->m_hashes = std::make_shared<std::unordered_map<std::string, std::string>>(hashes);
}

std::filesystem::path FolderSync::convertPath(const std::string& path)
{
	std::string secondPath = path;
	auto stFolderCopy = m_stFolderPath.string();
	auto ndFolderCopy = m_ndFolderPath.string();
	secondPath.replace(secondPath.begin(), secondPath.begin() + stFolderCopy.size(), ndFolderCopy.begin(), ndFolderCopy.end());

	return secondPath;
}

void FolderSync::checkstate(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User user = m_userDatabase->getUser(tokens[1]);
	std::string path = "Users/" + tokens[1] + "/Files";
	char* buff = new char[4096];
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		if (!file.is_directory())
		{
			std::ifstream fin(file.path().string());
			if (!fin.is_open())
			{
				std::cout << "File was locked!\n";
				continue;
			}
			std::string filepath = correctslashes(file.path().string());
			std::string filerelative = filepath.substr(filepath.find(path) + path.size() + 1);

			std::string hash = "Not found!";

			auto it = m_hashes->find(filepath);
			if (it != m_hashes->end())
			{
				hash = it->second;
			}

			send(sock, filerelative.c_str(), filerelative.size() + 1, 0);
			recv(sock, buff, 4096, 0);
			send(sock, hash.c_str(), hash.size() + 1, 0);
			int length = recv(sock, buff, 4096, 0);

			buff[length] = '\0';
			std::string sbuff = std::string(buff);
			if (sbuff == "Not found" || sbuff == "Modified")
			{
				std::cout << "Un clent a solicitat" << filepath << '\n';
				sendFile(sock, filerelative, filepath);
				recv(sock, buff, 4096, 0);
			}
			else
			{
				std::string message = "continue";
				send(sock, message.c_str(), message.size() + 1, 0);
				recv(sock, buff, 4096, 0);
			}
		}
	}
	std::string message = m_eot;
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::restoreFile(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	std::string filename;
	char* buff = new char[4096];
	User* user = m_userDatabase->getUserRef(tokens[1]);
	for (int index = 2; index < tokens.size(); ++index)
	{
		if (index != tokens.size() - 1)
			filename += tokens[index] + ' ';
		else
			filename += tokens[index];
	}
	std::cout << "filename " << filename << '\n';

	std::string recycleBinPath = correctslashes("Users/" + user->getUsername() + "/Recycle Bin/" + filename);
	std::string filesPath = correctslashes("Users/" + user->getUsername() + "/Files/" + filename);
	std::string filefolder = removelast(filesPath);
	std::filesystem::create_directories(filefolder);

	std::filesystem::copy(recycleBinPath, filesPath);
	std::filesystem::remove(recycleBinPath);
	auto it = m_hashes->find(recycleBinPath);
	if (it != m_hashes->end())
	{
		m_hashes->erase(it);
	}
	m_hashes->insert({ filesPath, std::to_string(Hash(filesPath)) });
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::sendToTrashBin(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	std::string filename;
	char* buff = new char[4096];
	User* user = m_userDatabase->getUserRef(tokens[1]);
	for (int index = 2; index < tokens.size(); ++index)
	{
		if (index != tokens.size() - 1)
			filename += tokens[index] + ' ';
		else
			filename += tokens[index];
	}
	filename = correctslashes(filename);
	std::string userPath = user->getPath() + "/" + filename;
	std::string recycleBinPath = correctslashes("Users/" + user->getUsername() + "/Recycle Bin/" + filename);
	std::string filesPath = correctslashes("Users/" + user->getUsername() + "/Files/" + filename);
	std::string filefolder = removelast(recycleBinPath);

	if (std::filesystem::exists(filesPath))
	{
		std::filesystem::create_directories(filefolder);
		std::filesystem::copy(filesPath, recycleBinPath);
		std::filesystem::remove(filesPath);
		auto it = m_hashes->find(correctslashes(filesPath));
		if (it != m_hashes->end())
		{
			m_hashes->erase(it);
		}
		m_hashes->insert({ recycleBinPath, std::to_string(Hash(recycleBinPath)) });
		std::string message = "ok";
		send(sock, message.c_str(), message.size(), 0);
		std::cout << "File " << filename << " sent to trash bin succesfully\n";
	}
	else
	{
		if (std::filesystem::exists(recycleBinPath))
		{
			std::cout << "file already in trash bin\n";
		}
		else
		{
			std::cout << "selected file is not synced!\n";
		}
		std::string message = "undo";
		send(sock, message.c_str(), message.size(), 0);
	}
}

FolderSync::FolderSync(const std::filesystem::path stFolderPath, const std::filesystem::path ndFolderPath) :
	m_stFolderPath(stFolderPath),
	m_ndFolderPath(ndFolderPath) {}

void FolderSync::readPaths()
{
	std::string filename = "paths.txt";
	std::ifstream file(filename);
	if (!(file.peek() == std::ifstream::traits_type::eof())) {

		file >> m_stFolderPath;
		file >> m_ndFolderPath;
	}
	else {
		std::cout << "No paths in " << filename << ".";
		exit(1);
	}
	if (m_ndFolderPath == "") {
		std::cout << "Only one path in " << filename << ".";
		exit(1);
	}

	file.close();
}

void FolderSync::printPaths() const
{
	std::cout << m_stFolderPath << " " << m_ndFolderPath;
}

void FolderSync::copyFile(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	char* buff = new char[4096];
	User* user = m_userDatabase->getUserRef(tokens[1]);
	std::string filename = tokens[2];
	for (int i = 3; i < tokens.size(); i++)
		filename = filename + " " + tokens[i];
	std::string filepath = "Users/" + user->getUsername() + "/Files/" + filename;
	std::string folders = removelast(filepath);
	std::string requestNewFile = std::to_string((int)Requests::NEWFILE);
	std::string requestModifyFile = std::to_string((int)Requests::MODIFYFILE);
	std::filesystem::create_directories(folders);

	std::ofstream fout(filepath, std::ios::binary);
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
	int length = recv(sock, buff, 4095, 0);
	buff[length] = '\0';
	std::string firstbuff(buff);
	if (firstbuff != m_eof)
	{
		while (1)
		{
			fout.write(buff, length);
			std::string message = "ok";
			send(sock, message.c_str(), message.size(), 0);
			length = recv(sock, buff, 4095, 0);
			buff[length] = '\0';
			std::string sbuff(buff);
			if (sbuff == m_eof) break;
		}
	}

	fout.close();

	if (tokens[0] == requestNewFile)
	{
		std::cout << "A fost creata fila " << filename << '\n';
		std::string hash = std::to_string(Hash(filepath));
		std::string path = correctslashes(filepath);
		auto it = m_hashes->find(path);
		if (it != m_hashes->end())
			m_hashes->erase(it);
		m_hashes->insert({ path, hash });
		std::cout << "Am inserat noul hash!\n";
	}
	else
		if (tokens[0] == requestModifyFile)
		{
			std::cout << "Am actualizat fila " << filename << "\n";
			std::string path = correctslashes(filepath);
			auto it = m_hashes->find(path);
			if (it != m_hashes->end())
				m_hashes->erase(it);
			std::string hash = std::to_string(Hash(filepath));
			m_hashes->insert({ path, hash });
		}
	message = "ok";
	send(sock, message.c_str(), message.size(), 0);
	RewriteHashFile();
}

void FolderSync::removeFile(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User* user = m_userDatabase->getUserRef(tokens[1]);
	std::string filename = tokens[2];
	for (int i = 3; i < tokens.size(); i++)
		filename = filename + " " + tokens[i];
	std::string filepath = "Users/" + user->getUsername() + "/Files/" + filename;
	if (std::filesystem::exists(filepath))
	{
		if (!std::filesystem::is_directory(filepath))
		{
			std::filesystem::remove(filepath);
			std::cout << "A fost stearsa fila " << filename << '\n';
			std::string path = correctslashes(filepath);
			auto it = m_hashes->find(path);
			if (it != m_hashes->end())
				m_hashes->erase(it);
			RewriteHashFile();
		}
		else
		{
			std::filesystem::remove_all(filepath);
		}
	}
	else
	{
		std::cout << "Fila " << filename << " nu a fost gasita!\n";
	}
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::modifyFile(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User* user = m_userDatabase->getUserRef(tokens[1]);
	std::string filename = tokens[2];
	for (int i = 3; i < tokens.size(); i++)
		filename = filename + " " + tokens[i];
	std::cout << "A fost modificata fila " << filename << '\n';
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::loginAttempt(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	if (!m_userDatabase->exists(tokens[1]))
	{
		std::cout << "username not registered\n";
		std::string message = "failed";
		send(sock, message.c_str(), message.size(), 0);
	}
	else
	{
		User checkuser = m_userDatabase->getUser(tokens[1]);
		if (tokens[2] == checkuser.getPassword())
		{
			std::cout << "user logged in succesfully\n";
			std::string message = "succes";
			send(sock, message.c_str(), message.size(), 0);
		}
		else
		{
			std::cout << "wrong password\n";
			std::string message = "failed";
			send(sock, message.c_str(), message.size(), 0);
		}
	}
}

void FolderSync::registerAttempt(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	if (m_userDatabase->exists(tokens[1]))
	{
		std::cout << "Username already taken\n";
		std::string message = "failed";
		send(sock, message.c_str(), message.size(), 0);
	}
	else
	{
		User newuser;
		newuser.setUsername(tokens[1]);
		newuser.setPassword(tokens[2]);
		newuser.setPath("notset");
		m_userDatabase->addUser(newuser);
		std::string message = "succes";
		send(sock, message.c_str(), message.size(), 0);
	}
}

void FolderSync::sendPath(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	std::string userpath = m_userDatabase->getUser(tokens[1]).getPath();
	send(sock, userpath.c_str(), userpath.size(), 0);
}

void FolderSync::sendFile(const SOCKET& sock, const std::string& filename, const std::string& localPath)
{
	std::cout << "trimit " << filename << '\n';
	char* buff = new char[4096];
	send(sock, filename.c_str(), filename.size(), 0);
	recv(sock, buff, 4096, 0);

	std::fstream file(localPath.c_str(), std::ios::in | std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "file cannot be opened\n";
		std::string message = m_eof;
		std::cout << "am zis eof\n";
		send(sock, message.c_str(), message.size() + 1, 0);
		file.close();
		return;
	}
	const auto begin = file.tellg();
	file.seekg(0, std::ios::end);
	const auto end = file.tellg();
	int filesize = (end - begin);
	file.clear();
	file.seekg(0);

	char* bytes = new char[4096];

	while (filesize > 0)
	{
		int _min = min(filesize, 4095);
		file.read(bytes, _min);
		bytes[_min] = '\0';
		send(sock, bytes, _min, 0);
		recv(sock, buff, 4096, 0);
		filesize -= 4095;
	}
	std::string message = m_eof;
	std::cout << "am zis eof\n";
	send(sock, message.c_str(), message.size() + 1, 0);
	file.close();
}

void FolderSync::changePath(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User* user = m_userDatabase->getUserRef(tokens[1]);
	std::string newpath;

	if (tokens.size() <= 2)
		newpath = "notset";
	else
		newpath = tokens[2];

	user->setPath(newpath);
	m_userDatabase->fileUpdate();
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::resetUser(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	std::string path = "Users/" + tokens[1] + "/";
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		auto it = m_hashes->find(correctslashes(file.path().string()));
		if (it != m_hashes->end())
			m_hashes->erase(it);
	}

	path = "Users/" + tokens[1] + "/Files/";
	std::filesystem::remove_all(path);
	path = "Users/" + tokens[1] + "/Recycle Bin/";
	std::filesystem::remove_all(path);

	path = "Users/" + tokens[1] + "/Files/";
	std::filesystem::create_directory(path);
	path = "Users/" + tokens[1] + "/Recycle Bin/";
	std::filesystem::create_directory(path);

	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
	RewriteHashFile();
}

void FolderSync::sendTrashBin(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User user = m_userDatabase->getUser(tokens[1]);
	std::string path = "../OneDrive/OneDrive/Users/" + tokens[1] + "/Recycle Bin/";
	send(sock, path.c_str(), path.size(), 0);
}

void FolderSync::sendAll(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	User user = m_userDatabase->getUser(tokens[1]);
	std::string path = "Users/" + tokens[1] + "/Files";
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		if (!file.is_directory())
		{
			std::string filepath = file.path().string();
			std::string message = filepath.substr(filepath.find(path) + path.size() + 1);
			sendFile(sock, message, filepath);
			char* buff = new char[4096];
			recv(sock, buff, 4096, 0);
		}
	}
	std::string message = m_eot;
	std::cout << "over\n";
	char* buff = new char[4096];
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::viewTrash(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	char* buff = new char[4096];
	User user = m_userDatabase->getUser(tokens[1]);
	std::string path = "Users/" + tokens[1] + "/Recycle Bin";
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		if (!file.is_directory())
		{
			std::ifstream check(file.path().string());
			if (!check.is_open())
			{
				std::cout << "iterator was comprimised!\n";
				break;
			}
			std::cout << "userul are in recycle: " << file.path().string() << '\n';
			std::string filepath = file.path().string();
			send(sock, filepath.c_str(), filepath.size() + 1, 0);
			recv(sock, buff, 4096, 0);
		}
	}
	std::cout << "recycle over\n";
	send(sock, m_eot.c_str(), m_eot.size(), 0);
}

void FolderSync::permanentlyRemoveFile(const SOCKET& sock, const std::vector <std::string>& tokens)
{
	std::string filename;
	char* buff = new char[4096];
	User* user = m_userDatabase->getUserRef(tokens[1]);
	for (int index = 2; index < tokens.size(); ++index)
	{
		if (index != tokens.size() - 1)
			filename += tokens[index] + ' ';
		else
			filename += tokens[index];
	}

	std::string recycleBinPath = correctslashes("Users/" + user->getUsername() + "/Recycle Bin/" + filename);
	std::filesystem::remove(recycleBinPath);
	auto it = m_hashes->find(recycleBinPath);
	if (it != m_hashes->end())
	{
		m_hashes->erase(it);
	}
	std::string message = "ok";
	send(sock, message.c_str(), message.size(), 0);
}

void FolderSync::askIfSynched(const SOCKET& sock, const std::vector<std::string>& tokens)
{
	std::string filename;
	char* buff = new char[4096];
	User* user = m_userDatabase->getUserRef(tokens[1]);
	for (int index = 2; index < tokens.size(); ++index)
	{
		if (index != tokens.size() - 1)
			filename += tokens[index] + ' ';
		else
			filename += tokens[index];
	}
	filename = correctslashes(filename);
	std::string filesPath = correctslashes("Users/" + user->getUsername() + "/Files/" + filename);
	std::string recycleBinPath = correctslashes("Users/" + user->getUsername() + "/Recycle Bin/" + filename);
	if (std::filesystem::exists(filesPath))
	{
		std::string message = "Synched";
		send(sock, message.c_str(), message.size(), 0);
	}
	else
		if (std::filesystem::exists(recycleBinPath))
		{
			std::string message = "Trashed";
			send(sock, message.c_str(), message.size(), 0);
		}
		else
		{
			std::string message = "Not Synched";
			send(sock, message.c_str(), message.size(), 0);
		}
}
