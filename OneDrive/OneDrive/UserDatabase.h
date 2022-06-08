#pragma once
#include <string>
#include <unordered_map>
#include "User.h"
#include <fstream>
#include <filesystem>

class UserDatabase
{
public:
	UserDatabase() = default;
	UserDatabase(const std::string& databasePath);
	bool exists(const std::string& username) const;
	User getUser(const std::string& username) const;
	User* getUserRef(const std::string& username);
	void addUser(const std::string& username, const std::string& password, const std::string& path);
	void addUser(const User& user);
	void fileUpdate();
	void setPath(const std::string& databasePath);
private:
	std::string m_databasePath;
	std::unordered_map<std::string, User> m_database;
};