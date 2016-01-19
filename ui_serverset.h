/********************************************************************************
** Form generated from reading UI file 'serverset.ui'
**
** Created: Tue Jun 23 09:31:06 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERSET_H
#define UI_SERVERSET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serverSet
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;

    void setupUi(QDialog *serverSet)
    {
        if (serverSet->objectName().isEmpty())
            serverSet->setObjectName(QString::fromUtf8("serverSet"));
        serverSet->resize(380, 318);
        serverSet->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        pushButton = new QPushButton(serverSet);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(240, 220, 75, 23));
        widget = new QWidget(serverSet);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(80, 100, 221, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 75 14pt \"\346\245\267\344\275\223\";"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(lineEdit);


        retranslateUi(serverSet);

        QMetaObject::connectSlotsByName(serverSet);
    } // setupUi

    void retranslateUi(QDialog *serverSet)
    {
        serverSet->setWindowTitle(QApplication::translate("serverSet", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("serverSet", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("serverSet", "\346\234\215\345\212\241\345\231\250IP", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class serverSet: public Ui_serverSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERSET_H
