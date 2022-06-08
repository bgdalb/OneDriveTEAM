#include "Connector.h"
#include "../../Request/Request/Request.h"

Connector::~Connector()
{
	//cleanup winsock
	WSACleanup();
}

void Connector::RewriteHashFile()
{
	std::ofstream fout(m_hashFilePath);
	for (auto it : m_hashes)
	{
		fout << "@" << it.first << "\n#" << it.second << '\n';
	}
	fout.close();
}

void Connector::SetupHashes()
{
	//commented to prevent errors for a while, still needed
	/*
	if (std::filesystem::exists(m_hashFilePath))
	{
		std::ifstream fin(m_hashFilePath);
		std::string line;
		std::string file, hash;
		while (std::getline(fin, line))
		{
			if (line[0] == '@')
				file = correctslashes(line.substr(1, line.length() - 1));
			else
				if (line[0] == '#')
				{
					hash = line.substr(1, line.length() - 1);
					if (std::filesystem::exists(file))
					{
						m_hashes.insert({ file, hash });
					}
				}
		}
		fin.close();
	}
	*/

	for (auto& file : std::filesystem::recursive_directory_iterator("Users")) {
		if (!file.is_directory())
		{
			std::string filePath = correctslashes(file.path().string());
			auto it = m_hashes.find(filePath);
			if (it == m_hashes.end())
			{
				std::string hash = std::to_string(Hash(filePath));
				m_hashes.insert({ filePath, hash });
			}
		}
	}

	RewriteHashFile();

}

Connector::Connector(int port)
{
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cout << "Can't initialize winsock! Quitting\n";
		return;
	}

	m_listening = socket(AF_INET, SOCK_STREAM, 0);

	if (m_listening == INVALID_SOCKET)
	{
		std::cout << "Can't create a socket! Quitting\n";
		return;
	}
	//bind the socket to an ip address and port
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port); //port
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(m_listening, (sockaddr*)&hint, sizeof(hint));

	//Tell Winsock the socket is for listening
	listen(m_listening, SOMAXCONN);

	FD_ZERO(&m_master);
	FD_SET(m_listening, &m_master);
	m_hashFilePath = "Hashes.txt";
	SetupHashes();
	m_fs.setHashes(m_hashes);
}

void Connector::setDBPath(const std::string db_path)
{
	m_userDB.setPath(db_path);
	m_fs.setUserDatabase(m_userDB);
}

void Connector::run()
{
	while (true)
	{
		auto copy = m_master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (newConnection(sock))
				std::cout << "New client connected!\n";
			else
			{
				char buff[4096];
				ZeroMemory(buff, 4096);
				int bytesIn = recv(sock, buff, 4096, 0);

				if (bytesIn <= 0)
					dropClient(sock);
				else
				{
					std::vector tokens = tokenize(buff);
					bool valid = processRequest(tokens, sock);
					if (!valid)
					{
						std::cout << buff << " -> ";
						std::cout << "invalid request format!\n";
					}
				}
			}
		}
	}
}

bool Connector::newConnection(const SOCKET sock)
{
	if (sock == m_listening)
	{
		SOCKET client = accept(m_listening, nullptr, nullptr);
		FD_SET(client, &m_master);

		return 1;
	}

	return 0;
}

void Connector::dropClient(SOCKET& sock)
{
	closesocket(sock);
	FD_CLR(sock, &m_master);
}

bool Connector::processRequest(const std::vector<std::string> tokens, const SOCKET& sock)
{
	//TAKING ACTION BASED ON REQUEST TAG

	int requestToken = stoi(tokens[0]);
	switch (requestToken)
	{
	case static_cast<int> (Requests::LOGINATTEMPT):
		m_fs.loginAttempt(sock, tokens);
		return 1;
	case static_cast<int> (Requests::REGISTERATTEMPT):
		m_fs.registerAttempt(sock, tokens);
		return 1;
	case static_cast<int> (Requests::SENDPATH):
		m_fs.sendPath(sock, tokens);
		return 1;
	case static_cast<int> (Requests::CHANGEPATH):
		m_fs.changePath(sock, tokens);
		return 1;
	case static_cast<int> (Requests::REMOVEFILE):
		m_fs.removeFile(sock, tokens);
		return 1;
	case static_cast<int> (Requests::NEWFILE):
		m_fs.copyFile(sock, tokens);
		return 1;
	case static_cast<int> (Requests::MODIFYFILE):
		m_fs.copyFile(sock, tokens);
		return 1;
	case static_cast<int> (Requests::DOWNLOADFILES):
		m_fs.sendAll(sock, tokens);
		return 1;
	case static_cast<int> (Requests::RESETUSER):
		m_fs.resetUser(sock, tokens);
		return 1;
	case static_cast<int> (Requests::VIEWTRASHBIN):
		m_fs.sendTrashBin(sock, tokens);
		return 1;
	case static_cast<int> (Requests::CHECKSTATE):
		m_fs.checkstate(sock, tokens);
		return 1;
	case static_cast<int> (Requests::RESTOREFILE):
		m_fs.restoreFile(sock, tokens);
		return 1;
	case static_cast<int> (Requests::MOVETOTRASH):
		m_fs.sendToTrashBin(sock, tokens);
		return 1;
	case static_cast<int> (Requests::VIEWTRASH):
		m_fs.viewTrash(sock, tokens);
		return 1;
	case static_cast<int> (Requests::PERMANENTLYREMOVEFILE):
		m_fs.permanentlyRemoveFile(sock, tokens);
		return 1;
	case static_cast<int> (Requests::ASKIFSYNCED):
		m_fs.askIfSynched(sock, tokens);
		return 1;
	default:
		return 0;
	}
	return 0;
}

fd_set* Connector::getMaster()
{
	return &m_master;
}

SOCKET* Connector::getListening()
{
	return &m_listening;
}