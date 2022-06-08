#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <serverconnector.h>
#include "recyclebindialog.h"
#include <filesystem>
#include <unordered_map>
#include <QCloseEvent>

namespace Ui {
	class EditWindow;
}

class EditWindow : public QWidget
{
	Q_OBJECT

public:
	explicit EditWindow(QWidget* parent = nullptr);
	~EditWindow();
	void setPath(const QString& path);

	void setUsername(const QString& username);

	void setConnection(ServerConnector& con);

	void setFolderpath(std::string folderpath);

	void sendFileToTrash(QString file);

	void setFinished(std::atomic<bool>& finished);

	void setSubWindowOpen(bool& subWindowOpen);

	void setReadOnly(bool readOnly);

	void setWathcingPaths(std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>& watching_paths);

	virtual void closeEvent(QCloseEvent* event);

	bool open;

private slots:
	void on_pushButton_released();

	void on_pushButton_2_released();

	void on_pushButton_3_released();

private:
	Ui::EditWindow* ui;
	QString m_path;
	QString m_username;
	std::unique_ptr<ServerConnector> m_con;
	recyclebindialog m_dialog;
	std::string m_folderpath;
	std::atomic<bool>* m_finished;
	bool* m_subWindowOpen;
	bool m_readOnly;
	std::unordered_map<std::string, std::pair<std::filesystem::file_time_type, QString>>* m_watching_paths;
};

#endif // EDITWINDOW_H
