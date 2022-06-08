/********************************************************************************
** Form generated from reading UI file 'recyclebinview.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECYCLEBINVIEW_H
#define UI_RECYCLEBINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecycleBinView
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *RecycleBinView)
    {
        if (RecycleBinView->objectName().isEmpty())
            RecycleBinView->setObjectName(QString::fromUtf8("RecycleBinView"));
        RecycleBinView->resize(534, 143);
        pushButton = new QPushButton(RecycleBinView);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 10, 131, 25));
        pushButton_2 = new QPushButton(RecycleBinView);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(390, 40, 131, 25));
        label = new QLabel(RecycleBinView);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 10, 81, 16));

        retranslateUi(RecycleBinView);

        QMetaObject::connectSlotsByName(RecycleBinView);
    } // setupUi

    void retranslateUi(QWidget *RecycleBinView)
    {
        RecycleBinView->setWindowTitle(QCoreApplication::translate("RecycleBinView", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("RecycleBinView", "Restore Selected", nullptr));
        pushButton_2->setText(QCoreApplication::translate("RecycleBinView", "Permanently Remove", nullptr));
        label->setText(QCoreApplication::translate("RecycleBinView", "Deleted files:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecycleBinView: public Ui_RecycleBinView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECYCLEBINVIEW_H
