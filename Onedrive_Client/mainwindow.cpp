#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fstream"
#include "iostream"
#include "QInputDialog"
#include "QMessageBox"
#include <chrono>
#include "QCloseEvent"
#include <thread>
#include "../../Request/Request/Request.h"
#include <QTreeWidgetItemIterator>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	QString windowTitle("Onedrive");
	ui->setupUi(this);
	this->setWindowTitle(windowTitle);
	const std::lock_guard<std::mutex> lock(stop_mutex);
	m_stop = false;
	m_finished = false;
	m_threadactive = false;
	if (!trashView)
		ui->pushButton_3->setVisible(false);
	m_subWindowOpen = false;
	m_watching_paths = m_fc.acces_watching_paths();
}

MainWindow::~MainWindow()
{
	delete ui;
	m_stop = true;
	m_finished = true;
}

void MainWindow::CheckingThreadStart()
{
	this->m_stop = false;
	this->m_finished = false;
	this->m_threadactive = false;
	auto CheckingTask = [](std::string path, FolderChecking& m_fc, std::atomic<bool>& stop, std::atomic<bool>& finished, std::atomic<bool>& threadactive, std::vector<std::string>& unsynched, std::vector<std::string>& trashed, bool readOnly) {
		while (!finished)
		{
			//do nothing
		}
		while (!stop)
		{
			threadactive = true;
			m_fc.start_checking(stop, readOnly, unsynched, trashed);
			threadactive = false;
		}
		std::cout << "Terminated!\n";
	};

	std::thread CheckingThread{ CheckingTask, m_path, std::ref(m_fc), std::ref(m_stop), std::ref(m_finished), std::ref(m_threadactive), std::ref(m_unsynched) , std::ref(m_trashed), m_readOnly};
	CheckingThread.detach();
}

void MainWindow::setPath(std::string path)
{
	m_stop = true;
	std::cout << "STOP THREAD1: " << m_stop << '\n';

	while (m_threadactive)
	{
		//do nothing
		std::cout << "Waiting for the thread to be inactive!\n";
	}

	this->m_path = path;
	if (path == "" || !std::filesystem::exists(path)) path = "notset";
	if (path == "notset")
	{
		ui->label->setText("Please insert a path to sync!");
	}
	else
	{
		if (std::filesystem::exists(path))
		{
			ui->label->setText(QString::fromStdString(path));
			m_dirmodel = new OnedriveFileSystemModel;
			m_dirmodel->setUnsynched(m_unsynched);
			m_dirmodel->setTrashed(m_trashed);
			m_dirmodel->setRootPath(QString::fromStdString(path));
			ui->treeView->setModel(m_dirmodel);
			ui->treeView->setColumnHidden(1, true);
			ui->treeView->setColumnWidth(0, 200);
			ui->treeView->setColumnWidth(2, 150);
			ui->treeView->setColumnWidth(3, 200);
			ui->treeView->setRootIndex(m_dirmodel->index(QString::fromStdString(path)));
		}
		else
		{
			ui->label->setText(QString::fromStdString("path not found!"));
		}

		if (std::filesystem::exists(path))
		{
			m_dw.setConnection(*m_con);
			m_dw.setPath(path);
			m_dw.setUsername(m_username);
			m_dw.setFC(m_fc);
			m_dw.setFinished(m_finished);
			m_dw.setSubWindowOpen(m_subWindowOpen);
			if (!m_readOnly)
			{
				m_dw.show();
			}
			else
			{
				m_dw.show();
				m_dw.sendAll();
				m_dw.close();
			}
			m_edit.setUsername(m_username);
			m_edit.setConnection(*m_con);
			m_editRB.setUsername(m_username);
			m_editRB.setConnection(*m_con);
			CheckingThreadStart();
			if (m_readOnly)
			{
				m_finished = true;
			}
		}
	}

}

void MainWindow::setReadOnly(bool readOnly)
{
	this->m_readOnly = readOnly;
}

void MainWindow::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

void MainWindow::on_pushButton_released()
{
	if (!m_subWindowOpen)
	{
		m_subWindowOpen = true;
		bool ok = true;
		QString newpath = QInputDialog::getText(0, "Change Path", "NewPath", QLineEdit::Normal, "", &ok);
		m_subWindowOpen = false;
		if (std::filesystem::exists(newpath.toStdString()))
		{
			setPath(newpath.toStdString());
			std::ofstream fout("LocalPath.txt");
			fout << newpath.toStdString();
			fout.close();
		}
		else
		{
			QMessageBox::information(0, "error", "Path not found!");
		};
	}
}

void MainWindow::setUsername(QString username)
{
	this->m_username = username;
	username = "Hello, " + username + "!";
	ui->label_2->setText(username);
}

void MainWindow::on_pushButton_2_released()
{
	if (!m_readOnly)
	{
		if (!m_subWindowOpen)
		{
			this->m_subWindowOpen = true;
			this->m_stop = true;
			while (m_threadactive)
			{
				//do nothing
				std::cout << "Waiting for the thread to be inactive!\n";
			}
			m_recycleview.setConnection(*m_con);
			m_recycleview.setUsername(m_username);
			m_recycleview.setFinished(m_finished);
			m_recycleview.setFolderpath(m_path);
			m_recycleview.setSubWindowOpen(m_subWindowOpen);
			m_recycleview.show();
			m_recycleview.ResetFiles();
			m_recycleview.UpdateFiles();
			CheckingThreadStart();
		}
	}
	else
	{
		QMessageBox::information(0, "Warning", "Accesing Recycle Bin in read only mode is not allowed!");
	}
}

void MainWindow::on_treeView_doubleClicked(const QModelIndex& index)
{
	if (!m_readOnly)
	{
		if (!m_subWindowOpen)
		{
			this->m_stop = true;
			while (m_threadactive)
			{
				//do nothing
				std::cout << "Waiting for the thread to be inactive!\n";
			}

			QString sPath = m_dirmodel->fileInfo(index).absoluteFilePath();
			QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::ASKIFSYNCED)) + ' ');
			QString filename = QString::fromStdString(sPath.toStdString().substr(sPath.toStdString().find(m_path) + m_path.size() + 1));
			QString message = requestIndex + m_username + ' ' + filename;
			QString response = m_con->request(message);

			if (response == QString("Synched"))
			{
				std::cout << "Synched";
				m_subWindowOpen = true;
				m_edit.setFolderpath(m_path);
				m_edit.setPath(sPath);
				m_edit.setReadOnly(m_readOnly);
				m_edit.setFinished(m_finished);
				m_edit.setWathcingPaths(*m_watching_paths);
				m_edit.setSubWindowOpen(m_subWindowOpen);
				m_edit.show();

				CheckingThreadStart();
			}
			else
				if (response.toStdString() == "Trashed")
				{
					std::cout << "Trashed";
					QMessageBox msgBox;
					msgBox.setWindowTitle("Choose an action");
					msgBox.setText("Selected item found in trash bin. Do you want to restore it?");
					msgBox.setStandardButtons(QMessageBox::Yes);
					msgBox.addButton(QMessageBox::No);
					msgBox.setDefaultButton(QMessageBox::No);
					if (msgBox.exec() == QMessageBox::Yes) {

						if (!std::filesystem::is_directory(sPath.toStdString()))
						{
							QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::RESTOREFILE)) + ' ');
							QString filename = QString::fromStdString(sPath.toStdString().substr(sPath.toStdString().find(m_path) + m_path.size() + 1));
							QString message = requestIndex + m_username + ' ' + filename;
							m_con->request(message);
						}
						else
						{
							for (auto& file : std::filesystem::recursive_directory_iterator(sPath.toStdString()))
							{
								if (!std::filesystem::is_directory(file.path().string()))
								{
									QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::RESTOREFILE)) + ' ');
									QString filename = QString::fromStdString(file.path().string().substr(file.path().string().find(m_path) + m_path.size() + 1));
									QString message = requestIndex + m_username + ' ' + filename;
									m_con->request(message);
								}
							}
						}

					}
					else {
						//nothing to do
					}
					CheckingThreadStart();
					m_finished = true;
				}
				else
					if (response.toStdString() == "Not Synched")
					{
						std::cout << "Not Synched";
						QMessageBox msgBox;
						msgBox.setWindowTitle("Choose an action");
						msgBox.setText("Selected item is not synched! Do you want to sync it now?");
						msgBox.setStandardButtons(QMessageBox::Yes);
						msgBox.addButton(QMessageBox::No);
						msgBox.setDefaultButton(QMessageBox::No);
						if (msgBox.exec() == QMessageBox::Yes) {

							std::filesystem::path fspath(sPath.toStdString());
							std::ofstream temp("tempfile");
							temp << "temptext";
							temp.close();
							auto currenttime = std::filesystem::last_write_time("tempfile");

							if (!std::filesystem::is_directory(sPath.toStdString()))
							{

								std::filesystem::last_write_time(fspath, currenttime);
							}
							else
							{
								if (std::filesystem::is_empty(sPath.toStdString()))
								{
									QMessageBox msgBox;
									msgBox.setWindowTitle("Choose an action");
									msgBox.setText("Cannot sync empty directories! Do you want to remove selected item?");
									msgBox.setStandardButtons(QMessageBox::Yes);
									msgBox.addButton(QMessageBox::No);
									msgBox.setDefaultButton(QMessageBox::No);
									if (msgBox.exec() == QMessageBox::Yes) {
										std::filesystem::remove(sPath.toStdString());
									}
									else
									{
										//nothing to do
									}

								}
								else
								{
									for (auto& file : std::filesystem::recursive_directory_iterator(sPath.toStdString()))
									{
										if (!std::filesystem::is_directory(file.path().string()))
										{
											std::filesystem::last_write_time(file.path().string(), currenttime);
										}
									}
								}
							}

						}
						else {
							//nothing to do
						}
						CheckingThreadStart();
						m_finished = true;
					}
		}
	}
}