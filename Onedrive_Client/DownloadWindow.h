#pragma once

#include <QWidget>
#include "ui_DownloadWindow.h"
#include "ServerConnector.h"
#include <filesystem>
#include <folderchecking.h>
#include "Utilites.h"

class DownloadWindow : public QWidget
{
	Q_OBJECT

public:
	DownloadWindow(QWidget* parent = Q_NULLPTR);
	~DownloadWindow();
	void setConnection(ServerConnector& con);
	void setPath(const std::string& path);
	void setUsername(const QString& username);
	void setFC(FolderChecking& fc);
	void setFinished(std::atomic<bool>& finished);
	void setSubWindowOpen(bool& subWindowOpen);
	void sendAll();

private slots:
	void on_pushButton_released();

	void on_pushButton_2_released();

private:
	std::string m_eof;
	std::string m_eot;
	std::string m_path;
	QString m_username;
	Ui::DownloadWindow ui;
	std::unique_ptr<ServerConnector> m_con;
	//QString *m_instruction;
	FolderChecking* m_fc;
	std::atomic<bool>* m_finished;
	bool* m_subWindowOpen;
};
