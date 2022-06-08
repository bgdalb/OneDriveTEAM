#include "editwindow.h"
#include "ui_editwindow.h"
#include "QDir"
#include <filesystem>
#include "QInputDialog"
#include "QMessageBox"
#include "Utilites.h"
#include "../../Request/Request/Request.h"

EditWindow::EditWindow(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::EditWindow)
{
	ui->setupUi(this);
}

EditWindow::~EditWindow()
{
	delete ui;
}

void EditWindow::setPath(const QString& path)
{
	this->m_path = path;
	ui->label->setText("Choose an action for " + path);
}

void EditWindow::on_pushButton_released()
{
	std::filesystem::path filepath(m_path.toStdString());
	if (std::filesystem::exists(filepath))
	{
		if (std::filesystem::is_directory(filepath))
		{
			std::filesystem::remove_all(filepath);
		}
		else
		{
			std::filesystem::remove(filepath);
		}
	}
	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}

QString changename(QString path, QString name)
{
	int poz = 0;
	for (int i = 0; i < path.size() - 1; i++)
	{
		if (path[i] == '/')
		{
			poz = i;
		}
	}
	std::string stdpath;
	stdpath = path.toStdString();
	stdpath = stdpath.substr(0, poz);
	stdpath += "/" + name.toStdString();
	path = QString::fromStdString(stdpath);
	return path;
}

void EditWindow::on_pushButton_2_released()
{
	bool ok = true;
	QString value = QInputDialog::getText(this, "New Name", "Introduce new file name", QLineEdit::Normal, "", &ok);
	QFile::rename(m_path, changename(m_path, value));
	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}

void EditWindow::sendFileToTrash(QString filepath)
{
	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::MOVETOTRASH)) + ' ');
	QString filename = QString::fromStdString(filepath.toStdString().substr(filepath.toStdString().find(m_folderpath) + m_folderpath.size() + 1));
	QString message = requestIndex + m_username + ' ' + filename;
	QString response = m_con->request(message);
	if (response == "ok")
	{
		auto it = m_watching_paths->find(correctslashes(filepath.toStdString()));
		if (it != m_watching_paths->end())
		{
			m_watching_paths->erase(it);
		}
	}
}

void EditWindow::setFinished(std::atomic<bool>& finished)
{
	this->m_finished = &finished;
}

void EditWindow::setReadOnly(bool readOnly)
{
	this->m_readOnly = readOnly;
}

void EditWindow::setSubWindowOpen(bool& subWindowOpen)
{
	this->m_subWindowOpen = &subWindowOpen;
}

void EditWindow::setWathcingPaths(std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>& watching_paths)
{
	this->m_watching_paths = &watching_paths;
	/*std::make_unique
		 <std::unordered_map
			 <std::string, std::pair<std::filesystem::file_time_type, QString>>> (watching_paths);*/
}

void EditWindow::closeEvent(QCloseEvent* event)
{
	*m_finished = true;
	*m_subWindowOpen = false;
}

void EditWindow::on_pushButton_3_released()
{
		std::filesystem::path filepath(m_path.toStdString());
		if (std::filesystem::exists(filepath))
		{
			if (std::filesystem::is_directory(filepath))
			{
				for (auto& file : std::filesystem::recursive_directory_iterator(filepath))
				{
					if (!file.is_directory())
					{
						sendFileToTrash(QString::fromStdString(file.path().string()));
					}
				}
				std::filesystem::remove_all(filepath);
			}
			else
			{
				sendFileToTrash(m_path);
				std::filesystem::remove(filepath);
			}
		}

	*m_finished = true;
	*m_subWindowOpen = false;
	this->close();
}

void EditWindow::setUsername(const QString& username)
{
	this->m_username = username;
}

void EditWindow::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

void EditWindow::setFolderpath(std::string folderpath)
{
	this->m_folderpath = folderpath;
}
