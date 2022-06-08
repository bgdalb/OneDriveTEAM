#ifndef RECYCLEBINDIALOG_H
#define RECYCLEBINDIALOG_H

#include <QDialog>

namespace Ui {
	class recyclebindialog;
}

class recyclebindialog : public QDialog
{
	Q_OBJECT

public:
	explicit recyclebindialog(QWidget* parent = nullptr);
	~recyclebindialog();

	void on_okButton_clicked();

	void on_cancelButton_clicked();

	bool getOption();

private:
	Ui::recyclebindialog* ui;
	bool m_option;
};

#endif // RECYCLEBINDIALOG_H
