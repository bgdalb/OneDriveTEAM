/********************************************************************************
** Form generated from reading UI file 'registerscreen.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERSCREEN_H
#define UI_REGISTERSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterScreen
{
public:
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;

    void setupUi(QWidget *RegisterScreen)
    {
        if (RegisterScreen->objectName().isEmpty())
            RegisterScreen->setObjectName(QString::fromUtf8("RegisterScreen"));
        RegisterScreen->resize(243, 199);
        lineEdit = new QLineEdit(RegisterScreen);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(30, 40, 131, 24));
        lineEdit_2 = new QLineEdit(RegisterScreen);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(30, 100, 131, 24));
        label = new QLabel(RegisterScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 20, 101, 16));
        label_2 = new QLabel(RegisterScreen);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 80, 121, 16));
        pushButton = new QPushButton(RegisterScreen);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 140, 80, 25));
        label_3 = new QLabel(RegisterScreen);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(120, 140, 61, 16));
        label_4 = new QLabel(RegisterScreen);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(120, 160, 91, 16));
        label_5 = new QLabel(RegisterScreen);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(120, 140, 111, 16));

        retranslateUi(RegisterScreen);

        QMetaObject::connectSlotsByName(RegisterScreen);
    } // setupUi

    void retranslateUi(QWidget *RegisterScreen)
    {
        RegisterScreen->setWindowTitle(QCoreApplication::translate("RegisterScreen", "Form", nullptr));
        label->setText(QCoreApplication::translate("RegisterScreen", "New Username", nullptr));
        label_2->setText(QCoreApplication::translate("RegisterScreen", "Create Password", nullptr));
        pushButton->setText(QCoreApplication::translate("RegisterScreen", "Register", nullptr));
        label_3->setText(QCoreApplication::translate("RegisterScreen", "<html><head/><body><p><span style=\" color:#ff0000;\">Username</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("RegisterScreen", "<html><head/><body><p><span style=\" color:#ff0000;\">already exists</span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("RegisterScreen", "<html><head/><body><p><span style=\" color:#ff0000;\">No spaces allowed</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterScreen: public Ui_RegisterScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERSCREEN_H
