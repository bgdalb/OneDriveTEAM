#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include "editwindow.h"
#include "editrecyclebin.h"
#include <fstream>
#include "serverconnector.h"
#include "DownloadWindow.h"
#include <unordered_map>
#include <filesystem>
#include "folderchecking.h"
#include "recyclebinview.h"
#include "OnedriveFileSystemModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void setUsername(QString username);
	void setPath(std::string path);
	void setConnection(ServerConnector& con);
	void setReadOnly(bool readOnly);
	bool trashView = 0;

private slots:
	void on_pushButton_released();

	void on_pushButton_2_released();

	void on_treeView_doubleClicked(const QModelIndex& index);

	void CheckingThreadStart();

private:
	std::unique_ptr<ServerConnector> m_con;
	Ui::MainWindow* ui;
	std::string m_path;
	QString m_username;
	EditWindow m_edit;
	RecycleBinView m_recycleview;
	editrecyclebin m_editRB;
	OnedriveFileSystemModel* m_dirmodel;
	//std::unique_ptr<QFileSystemModel> m_filemodel;
	QString m_name;
	FolderChecking m_fc;
	DownloadWindow m_dw;
	std::atomic<bool> m_stop;
	std::atomic<bool> m_finished;
	std::atomic<bool> m_threadactive;
	std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>* m_watching_paths;
	std::vector <std::string> m_unsynched;
	std::vector <std::string> m_trashed;
	bool m_subWindowOpen;
	bool m_readOnly;
};
#endif // MAINWINDOW_H
