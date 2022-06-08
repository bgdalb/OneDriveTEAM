#ifndef LOGINSCREEN_H
#pragma once
#define LOGINSCREEN_H

#include <QWidget>
#include "mainwindow.h"
#include "registerscreen.h"

namespace Ui {
	class LoginScreen;
}

class LoginScreen : public QWidget
{
	Q_OBJECT

public:
	explicit LoginScreen(QWidget* parent = nullptr);
	void setConnection(ServerConnector& con);
	~LoginScreen();

private slots:
	void on_lineEdit_textChanged(const QString& arg1);

	void on_lineEdit_2_textChanged(const QString& arg1);

	void on_pushButton_released();

	void on_pushButton_2_released();

    void on_radioButton_toggled(bool checked);

private:
	std::unique_ptr<ServerConnector> m_con;
	Ui::LoginScreen* ui;
	QString m_username;
	QString m_password;
	bool m_readOnly;
};

#endif // LOGINSCREEN_H
