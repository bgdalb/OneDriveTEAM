#include "recyclebindialog.h"
#include "ui_recyclebindialog.h"

recyclebindialog::recyclebindialog(QWidget* parent) :
	QDialog(parent),
	ui(new Ui::recyclebindialog)
{
	ui->setupUi(this);
}

recyclebindialog::~recyclebindialog()
{
	delete ui;
}

void recyclebindialog::on_okButton_clicked()
{
	m_option = 1;
	accept();
}

void recyclebindialog::on_cancelButton_clicked()
{
	m_option = 0;
	reject();
	close();
}

bool recyclebindialog::getOption()
{
	return m_option;
}
