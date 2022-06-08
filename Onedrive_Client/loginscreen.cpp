#include "loginscreen.h"
#include "ui_loginscreen.h"
#include "../../Request/Request/Request.h"
#include "iostream"
#include <fstream>
#include <string>
#include <qmessagebox.h>

LoginScreen::LoginScreen(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::LoginScreen), m_readOnly(false)
{
	ui->setupUi(this);
	ui->label_3->setVisible(false);
	ui->label_4->setVisible(false);
}

void LoginScreen::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

LoginScreen::~LoginScreen()
{
	delete ui;
}

void LoginScreen::on_lineEdit_textChanged(const QString& arg1)
{
	this->m_username = arg1;
}

void LoginScreen::on_lineEdit_2_textChanged(const QString& arg1)
{
	this->m_password = arg1;
}

void LoginScreen::on_pushButton_released()
{
	if (validcredentials(m_username) && validcredentials(m_password))
	{
		QString request;
		QString response;
		QString requestIndex;
		requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::LOGINATTEMPT)) + ' ');
		request = requestIndex + m_username + " " + m_password;
		response = m_con->request(request);
		qDebug() << response;
		if (response == "succes")
		{
			static MainWindow w;
			std::ifstream fin("LocalPath.txt");
			std::string path;
			std::getline(fin, path);
			if (m_readOnly)
			{
				QMessageBox::information(0, "Info", "You are entering in read only mode. All changes will be reverted!");
			}
			w.show();
			w.setUsername(m_username);
			w.setReadOnly(m_readOnly);
			w.setConnection(*m_con);
			w.setPath(path);
			fin.close();
			this->close();
		}
		else
		{
			ui->label_4->setVisible(false);
			ui->label_3->setVisible(true);
		}
	}
	else
	{
		ui->label_3->setVisible(false);
		ui->label_4->setVisible(true);
	}
}


void LoginScreen::on_pushButton_2_released()
{
	static RegisterScreen reg;
	reg.setConnection(*m_con);
	reg.show();
	this->close();
}


void LoginScreen::on_radioButton_toggled(bool checked)
{
	m_readOnly = checked;
}

