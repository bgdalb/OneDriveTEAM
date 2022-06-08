/********************************************************************************
** Form generated from reading UI file 'editrecyclebin.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITRECYCLEBIN_H
#define UI_EDITRECYCLEBIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editrecyclebin
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *editrecyclebin)
    {
        if (editrecyclebin->objectName().isEmpty())
            editrecyclebin->setObjectName(QString::fromUtf8("editrecyclebin"));
        editrecyclebin->resize(332, 110);
        centralwidget = new QWidget(editrecyclebin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 30, 121, 31));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(180, 30, 121, 31));
        editrecyclebin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(editrecyclebin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 332, 21));
        editrecyclebin->setMenuBar(menubar);
        statusbar = new QStatusBar(editrecyclebin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        editrecyclebin->setStatusBar(statusbar);

        retranslateUi(editrecyclebin);

        QMetaObject::connectSlotsByName(editrecyclebin);
    } // setupUi

    void retranslateUi(QMainWindow *editrecyclebin)
    {
        editrecyclebin->setWindowTitle(QCoreApplication::translate("editrecyclebin", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("editrecyclebin", "Delete Permanently", nullptr));
        pushButton_2->setText(QCoreApplication::translate("editrecyclebin", "Restore", nullptr));
    } // retranslateUi

};

namespace Ui {
    class editrecyclebin: public Ui_editrecyclebin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITRECYCLEBIN_H
