/********************************************************************************
** Form generated from reading UI file 'sendfile.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILE_H
#define UI_SENDFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SendFile
{
public:
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *SendFile)
    {
        if (SendFile->objectName().isEmpty())
            SendFile->setObjectName(QString::fromUtf8("SendFile"));
        SendFile->resize(426, 135);
        label = new QLabel(SendFile);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(110, 20, 191, 20));
        pushButton = new QPushButton(SendFile);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 70, 80, 25));
        pushButton_2 = new QPushButton(SendFile);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 70, 80, 25));

        retranslateUi(SendFile);

        QMetaObject::connectSlotsByName(SendFile);
    } // setupUi

    void retranslateUi(QWidget *SendFile)
    {
        SendFile->setWindowTitle(QCoreApplication::translate("SendFile", "Form", nullptr));
        label->setText(QCoreApplication::translate("SendFile", "Do you want to send this file ?", nullptr));
        pushButton->setText(QCoreApplication::translate("SendFile", "Send", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SendFile", "Discard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SendFile: public Ui_SendFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILE_H
