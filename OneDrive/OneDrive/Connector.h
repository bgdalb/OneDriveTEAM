#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ws2tcpip.h>
#include <unordered_map>
#include "FolderSync.h"
#include "UserDatabase.h"
#include "../../Hash/Hash/Hash/Hash.h"
#pragma comment(lib, "Ws2_32.lib")	//  links to Ws2_32.lib

class Connector
{
private:
	std::unordered_map<std::string, std::string> m_hashes;
	fd_set m_master;
	SOCKET m_listening;
	FolderSync m_fs;
	UserDatabase m_userDB;
	std::string m_hashFilePath;
public:
	~Connector();
	Connector(int port);
	void setDBPath(const std::string db_path);
	void run();
	bool newConnection(const SOCKET sock);
	void dropClient(SOCKET& sock);
	bool processRequest(const std::vector<std::string> tokens, const SOCKET& sock);
	void SetupHashes();
	void RewriteHashFile();
	fd_set* getMaster();
	SOCKET* getListening();
};
