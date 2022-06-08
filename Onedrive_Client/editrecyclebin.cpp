#include "editrecyclebin.h"
#include "ui_editrecyclebin.h"

editrecyclebin::editrecyclebin(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::editrecyclebin)
{
	ui->setupUi(this);
}

editrecyclebin::~editrecyclebin()
{
	delete ui;
}

void editrecyclebin::setPath(QString path)
{
	this->m_path = path;
}

void editrecyclebin::setConnection(ServerConnector& con)
{
	this->m_con = std::make_unique<ServerConnector>(con);
}

void editrecyclebin::setUsername(const QString& username)
{
	this->m_username = username;
}

void editrecyclebin::on_pushButton_released() // delete
{
	m_dialog.setModal(true);
	int result = m_dialog.exec();
	if (result == QDialog::Accepted)
	{
		QFile file;
		file.remove(m_path);
		this->close();
	}
}

void editrecyclebin::on_pushButton_2_released() // restore
{
	this->close();
	QString requestIndex = QString::fromStdString(std::to_string(static_cast<int> (Requests::RESTOREFILE)) + ' ');
	QStringList list = m_path.split(QLatin1Char('/'));
	QString filename = list.last();
	QString message = requestIndex + m_username + ' ' + filename;
	m_con->request(message);
}
