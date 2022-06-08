#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include "UserDatabase.h"
#include <ws2tcpip.h>

std::vector <std::string> tokenize(char* buff);
std::string correctslashes(std::string path);

class FolderSync
{
private:
	std::string m_eof;
	std::string m_eot;
	std::filesystem::path m_stFolderPath; // first folder path
	std::filesystem::path m_ndFolderPath; // second folder path
	std::unique_ptr<UserDatabase> m_userDatabase;
	std::shared_ptr<std::unordered_map<std::string, std::string>> m_hashes;
public:
	FolderSync();
	std::filesystem::path getFirstFolderPath() const;
	std::filesystem::path getSecondFolderPath() const;
	void setFirstFolderPath(const std::filesystem::path stFolderPath);
	void setSecondFolderPath(const std::filesystem::path ndFolderPath);
	void setUserDatabase(UserDatabase& userDatabase);
	void setHashes(std::unordered_map<std::string, std::string>& hashes);
	void RewriteHashFile();

	FolderSync(const std::filesystem::path stFolderPath, const std::filesystem::path ndFolderPath);
	void readPaths();
	void printPaths() const;
	void copyFile(const SOCKET& sock, const std::vector <std::string>& tokens);
	void removeFile(const SOCKET& sock, const std::vector <std::string>& tokens);
	void modifyFile(const SOCKET& sock, const std::vector <std::string>& tokens);
	void loginAttempt(const SOCKET& sock, const std::vector <std::string>& tokens);
	void registerAttempt(const SOCKET& sock, const std::vector <std::string>& tokens);
	void sendPath(const SOCKET& sock, const std::vector <std::string>& tokens);
	void sendFile(const SOCKET& sock, const std::string& filename, const std::string& localPath);
	void changePath(const SOCKET& sock, const std::vector <std::string>& tokens);
	void sendAll(const SOCKET& sock, const std::vector <std::string>& tokens);
	void resetUser(const SOCKET& sock, const std::vector <std::string>& tokens);
	void sendTrashBin(const SOCKET& sock, const std::vector <std::string>& tokens);
	void checkstate(const SOCKET& sock, const std::vector <std::string>& tokens);
	void restoreFile(const SOCKET& sock, const std::vector <std::string>& tokens);
	void sendToTrashBin(const SOCKET& sock, const std::vector <std::string>& tokens);
	void viewTrash(const SOCKET& sock, const std::vector <std::string>& tokens);
	void permanentlyRemoveFile(const SOCKET& sock, const std::vector <std::string>& tokens);
	void askIfSynched(const SOCKET& sock, const std::vector <std::string>& tokens);
	std::filesystem::path convertPath(const std::string& path);
};

