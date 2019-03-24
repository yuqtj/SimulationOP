/********************************************************************************
** Form generated from reading UI file 'RecordOp.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDOP_H
#define UI_RECORDOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RecordOpClass
{
public:
    QWidget *centralWidget;
    QPushButton *recordButton;
    QPushButton *operateButton;
    QPushButton *clearButton;
    QLineEdit *operationTimesText;
    QLabel *label;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RecordOpClass)
    {
        if (RecordOpClass->objectName().isEmpty())
            RecordOpClass->setObjectName(QString::fromUtf8("RecordOpClass"));
        RecordOpClass->resize(600, 400);
        centralWidget = new QWidget(RecordOpClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        recordButton = new QPushButton(centralWidget);
        recordButton->setObjectName(QString::fromUtf8("recordButton"));
        recordButton->setGeometry(QRect(30, 30, 75, 23));
        operateButton = new QPushButton(centralWidget);
        operateButton->setObjectName(QString::fromUtf8("operateButton"));
        operateButton->setGeometry(QRect(30, 190, 75, 23));
        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(30, 240, 75, 23));
        operationTimesText = new QLineEdit(centralWidget);
        operationTimesText->setObjectName(QString::fromUtf8("operationTimesText"));
        operationTimesText->setGeometry(QRect(30, 90, 71, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 70, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        label->setFont(font);
        RecordOpClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RecordOpClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        RecordOpClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(RecordOpClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        RecordOpClass->setStatusBar(statusBar);

        retranslateUi(RecordOpClass);

        QMetaObject::connectSlotsByName(RecordOpClass);
    } // setupUi

    void retranslateUi(QMainWindow *RecordOpClass)
    {
        RecordOpClass->setWindowTitle(QApplication::translate("RecordOpClass", "RecordOp", nullptr));
        recordButton->setText(QApplication::translate("RecordOpClass", "\350\256\260\345\275\225", nullptr));
        operateButton->setText(QApplication::translate("RecordOpClass", "\346\223\215\344\275\234", nullptr));
        clearButton->setText(QApplication::translate("RecordOpClass", "\346\270\205\347\251\272", nullptr));
        label->setText(QApplication::translate("RecordOpClass", "\346\223\215\344\275\234\346\254\241\346\225\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RecordOpClass: public Ui_RecordOpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDOP_H
