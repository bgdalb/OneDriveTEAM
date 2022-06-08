#pragma once
#ifndef REGISTERSCREEN_H
#define REGISTERSCREEN_H

#include <QWidget>
#include "mainwindow.h"

bool validcredentials(QString string);

namespace Ui {
	class RegisterScreen;
}

class RegisterScreen : public QWidget
{
	Q_OBJECT

public:
	explicit RegisterScreen(QWidget* parent = nullptr);
	void setConnection(ServerConnector& con);
	~RegisterScreen();

private slots:
	void on_pushButton_released();

	void on_lineEdit_textChanged(const QString& arg1);

	void on_lineEdit_2_textChanged(const QString& arg1);

private:
	std::unique_ptr<ServerConnector> m_con;
	Ui::RegisterScreen* ui;
	QString m_newusername;
	QString m_newpassword;
};

#endif // REGISTERSCREEN_H
