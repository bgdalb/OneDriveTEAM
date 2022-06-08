#ifndef FOLDERCHECKING_H
#define FOLDERCHECKING_H

#pragma once
#include <ws2tcpip.h>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <functional>
#include <future>
#include <unordered_map>
#include <map>
#include <vector>
#include <serverconnector.h>
#include <mutex>
#include "Utilites.h"

static std::mutex stop_mutex;

enum class FileStatus {
	created,
	modified,
	erased
};

class FolderChecking {
public:
	FolderChecking();
	void start_checking(std::atomic<bool>& stop, bool readOnly, std::vector<std::string>& unsynched, std::vector<std::string>& trashed);
	void setWatchingPath(const std::string watching_path);
	void setConnection(ServerConnector& con);
	void setUsername(const QString& username);
	void sendFile(const std::string& filePath);
	std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>* acces_watching_paths();

private:
	std::string m_eof;
	std::string m_eot;
	void receiveFile(const std::string& filename);
	const std::chrono::duration<int, std::milli> delay = std::chrono::milliseconds(1000);
	std::unique_ptr<ServerConnector> m_con;
	std::string m_watching_path;
	std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>> m_watching_paths;
	bool m_run = true;
	QString m_username;
	bool containInWatchingPath(const std::string& key);
	std::string relativePath(std::string path);
	std::chrono::milliseconds m_waitingTime;
};

#endif // FOLDERCHECKING_H
