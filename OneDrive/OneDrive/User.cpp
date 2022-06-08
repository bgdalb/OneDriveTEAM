#include "User.h"
#include <regex>
#include <iostream>

bool validPath(const std::string& s)
{
	return std::regex_match(s, std::regex("(([A-Z]|[a-z]:/)?(([a-z]|[A-Z])+/)*([a-z]|[A-Z])*?)"));
}

User::User() :
	m_username(),
	m_path()
{
}

User::User(const std::string& username, const std::string& path)
{
	this->m_username = username;
	if (validPath(path))
		this->m_path = path;
	else
	{
		std::cout << "Invalid path introduced, path not set";
	}
}

std::string User::getUsername() const
{
	return this->m_username;
}

std::string User::getPath() const
{
	return this->m_path;
}

std::string User::getPassword() const
{
	return this->m_password;
}

void User::setUsername(const std::string& username)
{
	this->m_username = username;
}

void User::setPath(const std::string& path)
{
	//if (validPath(path))
	this->m_path = path;
	/*else
	{
		std::cout << "Invalid path introduced, path not set";
	}*/
}

void User::setPassword(const std::string& password)
{
	this->m_password = password;
}

