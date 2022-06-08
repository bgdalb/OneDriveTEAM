#include "DownloadWindow.h"
#include "../../Request/Request/Request.h"
#include <QMessageBox>

DownloadWindow::DownloadWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	m_eof.push_back('1');
	m_eof.push_back(EOF);
	m_eot.push_back('2');
	m_eot.push_back(EOF);
}

DownloadWindow::~DownloadWindow()
{
	*m_finished = true;
}

void DownloadWindow::setSubWindowOpen(bool& subWindowOpen)
{
	this->m_subWindowOpen = &subWindowOpen;
}

void DownloadWindow::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

void DownloadWindow::setPath(const std::string& path)
{
	this->m_path = path;
}

void DownloadWindow::setUsername(const QString& username)
{
	this->m_username = username;
}

void DownloadWindow::setFC(FolderChecking& fc)
{
	this->m_fc = &fc;
}

void DownloadWindow::setFinished(std::atomic<bool>& finished)
{
	this->m_finished = &finished;
}

void DownloadWindow::sendAll()
{
	std::filesystem::create_directory(m_path);
	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::DOWNLOADFILES)) + ' ');
	QString message = requestIndex + m_username;
	QString receive = m_con->request(message);
	while (receive != QString::fromStdString(m_eot))
	{
		std::string folders = removelast(receive.toStdString());
		folders = m_path + "/" + folders;
		std::cout << "am facut folderele " << folders << '\n';

		std::filesystem::create_directories(folders);
		std::string createpath = m_path + "/" + receive.toStdString();
		std::fstream file(createpath, std::ios::out | std::ios::binary);
		int size = 0;
		QByteArray bytes = m_con->CountRequest((char*)"go on1", size);
		char* temp = bytes.data();
		temp[size] = '\0';
		std::string sbytes(temp);
		if (sbytes == m_eot) break;
		else
			while (sbytes != m_eof)
			{
				file.write(bytes, size);
				bytes = m_con->CountRequest((char*)"go on1", size);
				char* temp = bytes.data();
				temp[size] = '\0';
				sbytes = std::string(temp);
			}
		receive = m_con->request("go on2");
		file.close();
	}
	m_fc->setConnection(*m_con);
	m_fc->setWatchingPath(m_path);
	m_fc->setUsername(m_username);
	*m_finished = true;
	*m_subWindowOpen = false;
}

void DownloadWindow::on_pushButton_released()
{
	sendAll();
	this->close();
}

void DownloadWindow::on_pushButton_2_released()
{
	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::RESETUSER)) + ' ');
	QString message = requestIndex + m_username;
	QString response = m_con->request(message);
	m_fc->setConnection(*m_con);
	m_fc->setWatchingPath(m_path);
	m_fc->setUsername(m_username);
	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}
