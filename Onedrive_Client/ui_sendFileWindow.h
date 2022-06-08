/********************************************************************************
** Form generated from reading UI file 'sendFileWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENDFILEWINDOW_H
#define UI_SENDFILEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label;
    QPushButton *SendButton;
    QPushButton *discardButton;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(444, 154);
        label = new QLabel(Form);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 20, 211, 16));
        SendButton = new QPushButton(Form);
        SendButton->setObjectName(QString::fromUtf8("SendButton"));
        SendButton->setGeometry(QRect(100, 70, 80, 25));
        discardButton = new QPushButton(Form);
        discardButton->setObjectName(QString::fromUtf8("discardButton"));
        discardButton->setGeometry(QRect(250, 70, 80, 25));

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label->setText(QCoreApplication::translate("Form", "Do you want to send this file ?", nullptr));
        SendButton->setText(QCoreApplication::translate("Form", "Send", nullptr));
        discardButton->setText(QCoreApplication::translate("Form", "Discard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENDFILEWINDOW_H
