#include "folderchecking.h"
#include "../../Request/Request/Request.h"
#include <fstream>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <qmessagebox.h>
#include <filesystem>
#include "../../Hash/Hash/Hash/Hash.h"
#include <QLockFile>

FolderChecking::FolderChecking() :
	m_watching_path(),
	m_watching_paths(),
	m_waitingTime{ 300 }
{
	m_eof.push_back('1');
	m_eof.push_back(EOF);
	m_eot.push_back('2');
	m_eot.push_back(EOF);
}

void FolderChecking::receiveFile(const std::string& filename)
{
	std::string folders = removelast(filename);
	folders = m_watching_path + "/" + folders;
	std::cout << "am facut folderele " << folders << '\n';

	std::filesystem::create_directories(folders);
	std::string createpath = m_watching_path + "/" + filename;
	std::fstream file(createpath, std::ios::out | std::ios::binary);
	int size = 0;
	QByteArray bytes = m_con->CountRequest((char*)"go on1", size);
	char* temp = bytes.data();
	temp[size] = '\0';
	std::string sbytes(temp);
	if (sbytes == m_eot) return;
	else
		while (sbytes != m_eof)
		{
			file.write(bytes, size);
			bytes = m_con->CountRequest((char*)"go on1", size);
			temp = bytes.data();
			temp[size] = '\0';
			sbytes = std::string(temp);
			if (sbytes == m_eof || temp == m_eof)
				break;
		}
	file.close();
	setWatchingPath(m_watching_path);
}

std::string FolderChecking::relativePath(std::string path)
{
	path = path.substr(m_watching_path.size() + 1);
	std::cout << path << "\n";
	return path;
}

void FolderChecking::setWatchingPath(const std::string watching_path) {
	this->m_watching_path = watching_path;
	m_watching_paths.clear();
	for (auto& file : std::filesystem::recursive_directory_iterator(this->m_watching_path)) {
		m_watching_paths[correctslashes(file.path().string())] = { std::filesystem::last_write_time(file), QString::number(Hash(file.path().string())) };
		std::cout << "file: " << correctslashes(file.path().string()) << '\n';
	}
}

void FolderChecking::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

bool FolderChecking::containInWatchingPath(const std::string& key)
{
	auto el = m_watching_paths.find(correctslashes(key));
	return el != m_watching_paths.end();
}

void FolderChecking::setUsername(const QString& username)
{
	this->m_username = username;
}

void FolderChecking::sendFile(const std::string& filePath)
{
	FILE* file;
	file = fopen(filePath.c_str(), "rb");
	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	rewind(file);

	char* bytes = new char[4095];

	while (filesize > 0)
	{
		int _min = min(filesize, 4095);
		fread(bytes, 1, _min, file);
		filesize -= 4095;
		QString response = m_con->request(bytes, _min);
	}

	std::string message = m_eof;
	QString response = m_con->request(message, 1);
	fclose(file);
}

void FolderChecking::start_checking(std::atomic<bool>& stop, bool readOnly, std::vector<std::string>& unsynched, std::vector<std::string>& trashed)
{
	//Checking local modifications

	if (!readOnly)
	{

	std::vector <std::string> deleted;
	for (auto& iterator : m_watching_paths)
	{
		auto [key, value] = iterator;
		if (!std::filesystem::exists(key)) {
			deleted.push_back(key);
		}
	}
	for (int i = 0; i < deleted.size(); i++)
	{
		m_watching_paths.erase(deleted[i]);
		QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::REMOVEFILE)) + ' ');
		QString message = requestIndex + m_username + " " + QString::fromStdString(relativePath(deleted[i]));
		QString received = m_con->request(message);
	}

		for (auto& file : std::filesystem::recursive_directory_iterator(m_watching_path))
		{
			if (!file.is_directory())
			{
				std::ifstream check(file.path().string());
				if (!check.is_open())
				{
					std::cout << "skipped file as it was not accesible!\n";
					check.close();
					continue;
				}
				check.close();
				auto current_file_last_write_time = std::filesystem::last_write_time(file);
				std::string filePath = correctslashes(file.path().string());
				//file creation condition
				if (!containInWatchingPath(filePath)) {
					m_watching_paths[filePath] = { current_file_last_write_time, QString::number(Hash(file.path().string())) };
					QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::NEWFILE)) + ' ');
					QString message = requestIndex + m_username + " " + QString::fromStdString(relativePath(filePath));
					QString received = m_con->request(message);
					sendFile(filePath);
				}
				//file modification
				else {
					if (m_watching_paths[filePath].first != current_file_last_write_time) {
						m_watching_paths[filePath] = { current_file_last_write_time, QString::number(Hash(file.path().string())) };
						QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::MODIFYFILE)) + ' ');
						QString message = requestIndex + m_username + " " + QString::fromStdString(relativePath(filePath));
						QString received = m_con->request(message);
						sendFile(filePath);
					}
				}
			}
		}
	}

	//Checking server modifications

	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::CHECKSTATE)) + ' ');
	QString request = requestIndex + m_username;
	QString check = "0";
	while (check != QString::fromStdString(m_eot))
	{
		QString message = "go on";
		QString serverfilepath = correctslashes(m_con->request(request));
		check = serverfilepath;
		if (check == QString::fromStdString(m_eot)) break;
		QString localfilepath = correctslashes(QString::fromStdString(m_watching_path) + "/" + serverfilepath);

		QString serverhash = m_con->request(message);
		QString localhash = "NOT FOUND!";
		std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>::iterator it = m_watching_paths.find(localfilepath.toStdString().substr(0, localfilepath.length() - 1));
		if (it != m_watching_paths.end())
		{
			localhash = it->second.second;
		}

		QString status;
		bool receive;
		if (!std::filesystem::exists(localfilepath.toStdString()))
		{
			status = "Not found";
			receive = true;
		}
		else
			if (localhash.toStdString() != serverhash.toStdString().substr(0, serverhash.length() - 1))
			{
				status = "Modified";
				receive = true;
			}
			else
			{
				status = "Matching";
				receive = false;
			}
		QString response = m_con->request(status);
		if (receive)
		{
			receiveFile(serverfilepath.toStdString());
		}
	}

	//Check status for colorcode
	trashed.clear();
	unsynched.clear();
	for (auto& file : std::filesystem::recursive_directory_iterator(m_watching_path))
	{
		if (!file.is_directory())
		{
			QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::ASKIFSYNCED)) + ' ');
			QString filename = QString::fromStdString(file.path().string().substr(file.path().string().find(m_watching_path) + m_watching_path.size() + 1));
			QString message = requestIndex + m_username + ' ' + filename;
			QString response = m_con->request(message);
			if (response.toStdString() == "Trashed")
			{
				std::string abspath = correctslashes(file.path().string());
				trashed.push_back(abspath);
				std::cout << "Trashed abspath " << abspath << '\n';
			}
			else
				if (response.toStdString() == "Not Synched")
				{
					std::string abspath = correctslashes(file.path().string());
					unsynched.push_back(abspath);
					std::cout << "Unsynched abspath " << abspath << '\n';
				}
		}
	}

	for (int i = 0; i < 10; i++)
	{
		if (stop) break;
		std::this_thread::sleep_for(m_waitingTime);
	}
}

std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>* FolderChecking::acces_watching_paths()
{
	return &m_watching_paths;
}
