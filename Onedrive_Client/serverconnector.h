#pragma once
#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H
#include <iostream>
#include <string>
#include <QTcpSocket>

class ServerConnector
{
private:
	std::string m_ipAddress;
	int m_port;
	QTcpSocket* m_socket;
public:
	ServerConnector();
	ServerConnector(const std::string& ipAddress, const int& port);
	QString request(const std::string& message, const bool& type);
	void Socketconnect();
	QString request(const QString& message);
	char* request(char* message, const int& size);
	QByteArray CountRequest(char* message, int& bytesread);
	void setIP(const std::string& ip);
	void setPort(const int& port);
};

#endif // SERVERCONNECTOR_H
