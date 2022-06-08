#ifndef RECYCLEBINVIEW_H
#define RECYCLEBINVIEW_H

#include <QWidget>
#include <vector>
#include "serverconnector.h"
#include <string>;

namespace Ui {
	class RecycleBinView;
}

class RecycleBinView : public QWidget
{
	Q_OBJECT

public:
	explicit RecycleBinView(QWidget* parent = nullptr);
	~RecycleBinView();
	void setConnection(ServerConnector& con);
	void setUsername(const QString& username);
	void UpdateFiles();
	void ResetFiles();
	void setFolderpath(std::string folderpath);
	void setFinished(std::atomic<bool>& finished);
	void setOpen(bool* open);
	void setSubWindowOpen(bool& subWindowOpen);
	virtual void closeEvent(QCloseEvent* event);
	virtual void paintEvent(QPaintEvent* event);
	virtual void mouseReleaseEvent(QMouseEvent* e);

private slots:
	void on_pushButton_released();

	void on_pushButton_2_released();

private:
	Ui::RecycleBinView* ui;
	std::vector <QString> m_files;
	std::vector <int> m_colors;
	std::unique_ptr<ServerConnector> m_con;
	QString m_username;
	std::string m_eot;
	std::string m_folderpath;
	std::atomic<bool>* m_finished;
	bool* m_subWindowOpen;
};

#endif // RECYCLEBINVIEW_H
