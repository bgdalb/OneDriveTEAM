/********************************************************************************
** Form generated from reading UI file 'recyclebindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECYCLEBINDIALOG_H
#define UI_RECYCLEBINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_recyclebindialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;

    void setupUi(QDialog *recyclebindialog)
    {
        if (recyclebindialog->objectName().isEmpty())
            recyclebindialog->setObjectName(QString::fromUtf8("recyclebindialog"));
        recyclebindialog->resize(324, 105);
        buttonBox = new QDialogButtonBox(recyclebindialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-100, 50, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(recyclebindialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 0, 461, 61));

        retranslateUi(recyclebindialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), recyclebindialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), recyclebindialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(recyclebindialog);
    } // setupUi

    void retranslateUi(QDialog *recyclebindialog)
    {
        recyclebindialog->setWindowTitle(QCoreApplication::translate("recyclebindialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("recyclebindialog", "The file will be permanently deleted. Are you sure?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class recyclebindialog: public Ui_recyclebindialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECYCLEBINDIALOG_H
