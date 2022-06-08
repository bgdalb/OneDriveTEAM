#pragma once
#include <string>
#include <unordered_map>


class User
{
private:
	std::string m_username;
	std::string m_password;
	std::string m_path;
public:
	User();
	User(const std::string& username, const std::string& path = "");
	std::string getUsername() const;
	std::string getPath() const;
	std::string getPassword() const;
	void setUsername(const std::string& username);
	void setPath(const std::string& path);
	void setPassword(const std::string& password);
};