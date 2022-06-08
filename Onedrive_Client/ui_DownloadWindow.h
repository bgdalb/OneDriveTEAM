/********************************************************************************
** Form generated from reading UI file 'DownloadWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADWINDOW_H
#define UI_DOWNLOADWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownloadWindow
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *DownloadWindow)
    {
        if (DownloadWindow->objectName().isEmpty())
            DownloadWindow->setObjectName(QString::fromUtf8("DownloadWindow"));
        DownloadWindow->resize(400, 99);
        pushButton = new QPushButton(DownloadWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 60, 93, 28));
        pushButton_2 = new QPushButton(DownloadWindow);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 60, 93, 28));
        label = new QLabel(DownloadWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 30, 341, 16));

        retranslateUi(DownloadWindow);

        QMetaObject::connectSlotsByName(DownloadWindow);
    } // setupUi

    void retranslateUi(QWidget *DownloadWindow)
    {
        DownloadWindow->setWindowTitle(QCoreApplication::translate("DownloadWindow", "DownloadWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("DownloadWindow", "Download", nullptr));
        pushButton_2->setText(QCoreApplication::translate("DownloadWindow", "Continue", nullptr));
        label->setText(QCoreApplication::translate("DownloadWindow", "You have a folder uploaded. Do you want to download it?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DownloadWindow: public Ui_DownloadWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADWINDOW_H
