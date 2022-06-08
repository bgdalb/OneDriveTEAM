#include "serverconnector.h"
#include <ws2tcpip.h>
#include <winsock2.h>
#include <fstream>
#include <winsock.h>
#include <QMessageBox>
#include <QHostAddress>
#include <Winsock2.h>

#pragma comment(lib, "ws2_32.lib")

ServerConnector::ServerConnector()
{

}

ServerConnector::ServerConnector(const std::string& ipAddress, const int& port)
{
	this->m_ipAddress = ipAddress;
	this->m_port = port;
}

void ServerConnector::Socketconnect()
{
	m_socket = new QTcpSocket();
	//m_socket = std::make_unique<QTcpSocket>(new QTcpSocket);
	m_socket->connectToHost("127.0.0.1", 54000);
	if (m_socket->waitForConnected(3000))
	{
		qDebug() << "Connected!";
	}
	else
	{
		qDebug() << "Not Connected!";
	}
}

QString ServerConnector::request(const QString& message)
{
	QByteArray ba = message.toLocal8Bit();
	const char* sendable = ba.data();
	m_socket->write(sendable);
	m_socket->waitForBytesWritten(60000);
	m_socket->waitForReadyRead(60000);
	std::string response = m_socket->readAll().toStdString();
	return QString::fromStdString(response);
}

QString ServerConnector::request(const std::string& message, const bool& type)
{
	const char* sendable = message.data();
	m_socket->write(sendable);
	m_socket->waitForBytesWritten(60000);
	m_socket->waitForReadyRead(60000);
	std::string response = m_socket->readAll().toStdString();
	return QString::fromStdString(response);
}

char* ServerConnector::request(char* message, const int& size)
{
	m_socket->write(message, size);
	m_socket->waitForBytesWritten(60000);
	m_socket->waitForReadyRead(60000);
	char* response = m_socket->readAll().data();
	return response;
}

QByteArray ServerConnector::CountRequest(char* message, int& bytesread)
{
	m_socket->write(message);
	m_socket->waitForBytesWritten(60000);
	m_socket->waitForReadyRead(60000);
	bytesread = m_socket->bytesAvailable();
	QByteArray ba = m_socket->readAll();
	return ba;
}

void ServerConnector::setIP(const std::string& ip)
{
	this->m_ipAddress = ip;
}

void ServerConnector::setPort(const int& port)
{
	this->m_port = port;
}
