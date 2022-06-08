#include "UserDatabase.h"
#include <iostream>

UserDatabase::UserDatabase(const std::string& databasePath)
{
	this->m_databasePath = databasePath;
	std::fstream databaseFile(databasePath);
	std::string username, password, path;
	while (!databaseFile.eof()) {
		User user;
		databaseFile >> username;
		databaseFile >> password;
		databaseFile >> path;
		user.setUsername(username);
		user.setPassword(password);
		user.setPath(path);
		m_database.insert(std::make_pair(username, user));
	}

	databaseFile.close();
}

bool UserDatabase::exists(const std::string& username) const
{
	std::unordered_map<std::string, User>::const_iterator got = m_database.find(username);

	if (got == m_database.end())
		return false;
	return true;
}

User UserDatabase::getUser(const std::string& username) const
{
	std::unordered_map<std::string, User>::const_iterator got = m_database.find(username);

	if (got == m_database.end())
	{
		return User();
	}
	return got->second;
}

User* UserDatabase::getUserRef(const std::string& username)
{
	//std::unordered_map<std::string, User>::const_iterator got = database.find(username);

	for (auto& iterator : m_database)
	{
		if (iterator.second.getUsername() == username)
			return &iterator.second;
	}

	return nullptr;
}

void print_map(std::unordered_map<std::string, User> const& m, std::ostream& fout)
{
	for (auto const& pair : m) {
		fout << pair.second.getUsername() << " " << pair.second.getPassword() << " " << pair.second.getPath() << '\n';
	}
}

void UserDatabase::fileUpdate()
{
	std::ofstream fout(m_databasePath);
	//std::cout << "scriu datele in " << databasePath << '\n';
	print_map(m_database, fout);
	fout.close();
}

void UserDatabase::setPath(const std::string& databasePath)
{
	this->m_databasePath = databasePath;
	std::fstream databaseFile(databasePath);
	std::string username, password, path;
	while (!databaseFile.eof()) {
		User user;
		databaseFile >> username;
		databaseFile >> password;
		databaseFile >> path;
		user.setUsername(username);
		user.setPassword(password);
		user.setPath(path);
		m_database.insert(std::make_pair(username, user));
	}

	databaseFile.close();
}

void UserDatabase::addUser(const User& user)
{
	m_database.insert(std::make_pair(user.getUsername(), user));
	std::cout << "am inserat userul " << user.getUsername() << '\n';
	std::filesystem::create_directory("Users/" + user.getUsername());
	std::filesystem::create_directory("Users/" + user.getUsername() + "/Files");
	std::filesystem::create_directory("Users/" + user.getUsername() + "/Recycle Bin");
	fileUpdate();
}

void UserDatabase::addUser(const std::string& username, const std::string& password, const std::string& path)
{
	User user;
	user.setUsername(username);
	user.setPassword(password);
	user.setPath(path);
	addUser(user);
}
