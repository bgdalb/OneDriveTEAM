#ifndef EDITRECYCLEBIN_H
#define EDITRECYCLEBIN_H

#include <QMainWindow>
#include <serverconnector.h>
#include "QDir"
#include "../../Request/Request/Request.h"
#include "recyclebindialog.h"

namespace Ui {
	class editrecyclebin;
}

class editrecyclebin : public QMainWindow
{
	Q_OBJECT

public:
	explicit editrecyclebin(QWidget* parent = nullptr);
	~editrecyclebin();
	void setPath(QString path);
	void setConnection(ServerConnector& con);
	void setUsername(const QString& username);

private slots:
	void on_pushButton_released();

	void on_pushButton_2_released();

private:
	Ui::editrecyclebin* ui;
	QString m_path;
	std::unique_ptr<ServerConnector> m_con;
	QString m_username;
	recyclebindialog m_dialog;
};

#endif // EDITRECYCLEBIN_H
