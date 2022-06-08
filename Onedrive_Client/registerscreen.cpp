#include "registerscreen.h"
#include "../../Request/Request/Request.h"
#include "ui_registerscreen.h"

RegisterScreen::RegisterScreen(QWidget* parent) :
	QWidget(parent),
	ui(new Ui::RegisterScreen)
{
	ui->setupUi(this);
	ui->label_3->setVisible(false);
	ui->label_4->setVisible(false);
	ui->label_5->setVisible(false);
}

bool validcredentials(QString string)
{
	if (string == "") return false;
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == ' ')
			return false;
	}
	return true;
}

void RegisterScreen::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

RegisterScreen::~RegisterScreen()
{
	delete ui;
}

void RegisterScreen::on_pushButton_released()
{
	if (!validcredentials(m_newusername) || !validcredentials(m_newpassword))
	{
		ui->label_3->setVisible(false);
		ui->label_4->setVisible(false);
		ui->label_5->setVisible(true);
		return;
	}
	else
	{
		QString request;
		QString response;
		QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::REGISTERATTEMPT)) + ' ');
		request = requestIndex + m_newusername + " " + m_newpassword;
		response = m_con->request(request);

		if (response == "failed")
		{
			ui->label_5->setVisible(false);
			ui->label_3->setVisible(true);
			ui->label_4->setVisible(true);
			return;
		}
		else
		{
			static MainWindow w;
			w.setConnection(*m_con);
			w.setUsername(m_newusername);
			w.show();
			this->close();
		}
	}
}


void RegisterScreen::on_lineEdit_textChanged(const QString& arg1)
{
	this->m_newusername = arg1;
}


void RegisterScreen::on_lineEdit_2_textChanged(const QString& arg1)
{
	this->m_newpassword = arg1;
}

