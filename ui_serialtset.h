/********************************************************************************
** Form generated from reading UI file 'serialtset.ui'
**
** Created: Tue Jun 23 09:01:22 2015
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALTSET_H
#define UI_SERIALTSET_H

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

class Ui_SerialTSet
{
public:
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *BotePoint_edit;

    void setupUi(QDialog *SerialTSet)
    {
        if (SerialTSet->objectName().isEmpty())
            SerialTSet->setObjectName(QString::fromUtf8("SerialTSet"));
        SerialTSet->resize(405, 326);
        SerialTSet->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        pushButton = new QPushButton(SerialTSet);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 230, 75, 23));
        layoutWidget = new QWidget(SerialTSet);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 120, 231, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: 70 19pt \"\346\245\267\344\275\223\";"));

        horizontalLayout->addWidget(label);

        BotePoint_edit = new QLineEdit(layoutWidget);
        BotePoint_edit->setObjectName(QString::fromUtf8("BotePoint_edit"));
        BotePoint_edit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        horizontalLayout->addWidget(BotePoint_edit);


        retranslateUi(SerialTSet);

        QMetaObject::connectSlotsByName(SerialTSet);
    } // setupUi

    void retranslateUi(QDialog *SerialTSet)
    {
        SerialTSet->setWindowTitle(QApplication::translate("SerialTSet", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("SerialTSet", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SerialTSet", "\346\263\242\347\211\271\347\216\207", 0, QApplication::UnicodeUTF8));
        BotePoint_edit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SerialTSet: public Ui_SerialTSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALTSET_H
