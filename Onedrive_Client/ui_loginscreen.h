/********************************************************************************
** Form generated from reading UI file 'loginscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINSCREEN_H
#define UI_LOGINSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginScreen
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QRadioButton *radioButton;

    void setupUi(QWidget *LoginScreen)
    {
        if (LoginScreen->objectName().isEmpty())
            LoginScreen->setObjectName(QString::fromUtf8("LoginScreen"));
        LoginScreen->resize(264, 250);
        lineEdit = new QLineEdit(LoginScreen);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(50, 70, 151, 24));
        lineEdit_2 = new QLineEdit(LoginScreen);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(50, 120, 151, 24));
        label = new QLabel(LoginScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 50, 71, 16));
        label_2 = new QLabel(LoginScreen);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 100, 61, 16));
        pushButton = new QPushButton(LoginScreen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 160, 80, 25));
        label_3 = new QLabel(LoginScreen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 190, 91, 16));
        label_3->setAcceptDrops(false);
        pushButton_2 = new QPushButton(LoginScreen);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(140, 160, 80, 25));
        label_4 = new QLabel(LoginScreen);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(50, 190, 151, 16));
        radioButton = new QRadioButton(LoginScreen);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 220, 97, 22));

        retranslateUi(LoginScreen);

        QMetaObject::connectSlotsByName(LoginScreen);
    } // setupUi

    void retranslateUi(QWidget *LoginScreen)
    {
        LoginScreen->setWindowTitle(QCoreApplication::translate("LoginScreen", "Form", nullptr));
        label->setText(QCoreApplication::translate("LoginScreen", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("LoginScreen", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("LoginScreen", "Enter", nullptr));
        label_3->setText(QCoreApplication::translate("LoginScreen", "<html><head/><body><p><span style=\" color:#da0000;\">Invalid Account</span></p></body></html>", nullptr));
        pushButton_2->setText(QCoreApplication::translate("LoginScreen", "Register", nullptr));
        label_4->setText(QCoreApplication::translate("LoginScreen", "<html><head/><body><p><span style=\" color:#ff0000;\">No white spaces allowed</span></p></body></html>", nullptr));
        radioButton->setText(QCoreApplication::translate("LoginScreen", "ReadOnly", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginScreen: public Ui_LoginScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINSCREEN_H
