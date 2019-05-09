/********************************************************************************
** Form generated from reading UI file 'RecordOp.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECORDOP_H
#define UI_RECORDOP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>
#include <optreewidget.h>

QT_BEGIN_NAMESPACE

class Ui_RecordOpClass
{
public:
    QAction *newButton;
    QAction *openButton;
    QAction *saveButton;
    QWidget *centralWidget;
    QPushButton *recordButton;
    QPushButton *operateButton;
    QLineEdit *operationTimesText;
    QLabel *label;
    QTableWidget *opTable;
    OPTreeWidget *opTreeList;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *opDescriptionEdit;
    QLabel *label_4;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *RecordOpClass)
    {
        if (RecordOpClass->objectName().isEmpty())
            RecordOpClass->setObjectName(QStringLiteral("RecordOpClass"));
        RecordOpClass->resize(764, 422);
        newButton = new QAction(RecordOpClass);
        newButton->setObjectName(QStringLiteral("newButton"));
        openButton = new QAction(RecordOpClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        saveButton = new QAction(RecordOpClass);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        centralWidget = new QWidget(RecordOpClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        recordButton = new QPushButton(centralWidget);
        recordButton->setObjectName(QStringLiteral("recordButton"));
        recordButton->setGeometry(QRect(30, 30, 75, 23));
        operateButton = new QPushButton(centralWidget);
        operateButton->setObjectName(QStringLiteral("operateButton"));
        operateButton->setGeometry(QRect(30, 120, 75, 23));
        operationTimesText = new QLineEdit(centralWidget);
        operationTimesText->setObjectName(QStringLiteral("operationTimesText"));
        operationTimesText->setGeometry(QRect(30, 90, 71, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 70, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        label->setFont(font);
        opTable = new QTableWidget(centralWidget);
        opTable->setObjectName(QStringLiteral("opTable"));
        opTable->setGeometry(QRect(310, 40, 441, 211));
        opTreeList = new OPTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        opTreeList->setHeaderItem(__qtreewidgetitem);
        opTreeList->setObjectName(QStringLiteral("opTreeList"));
        opTreeList->setGeometry(QRect(150, 40, 151, 211));
        opTreeList->setDragEnabled(true);
        opTreeList->setDragDropMode(QAbstractItemView::InternalMove);
        opTreeList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        opTreeList->header()->setVisible(false);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 10, 71, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(310, 10, 81, 21));
        label_3->setFont(font1);
        opDescriptionEdit = new QLineEdit(centralWidget);
        opDescriptionEdit->setObjectName(QStringLiteral("opDescriptionEdit"));
        opDescriptionEdit->setGeometry(QRect(150, 299, 601, 71));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        opDescriptionEdit->setFont(font2);
        opDescriptionEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 270, 71, 21));
        label_4->setFont(font1);
        RecordOpClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(RecordOpClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 764, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        RecordOpClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(RecordOpClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        RecordOpClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(newButton);
        menu->addAction(openButton);
        menu->addAction(saveButton);

        retranslateUi(RecordOpClass);

        QMetaObject::connectSlotsByName(RecordOpClass);
    } // setupUi

    void retranslateUi(QMainWindow *RecordOpClass)
    {
        RecordOpClass->setWindowTitle(QApplication::translate("RecordOpClass", "RecordOp", Q_NULLPTR));
        newButton->setText(QApplication::translate("RecordOpClass", "\346\226\260\345\273\272", Q_NULLPTR));
        openButton->setText(QApplication::translate("RecordOpClass", "\346\211\223\345\274\200", Q_NULLPTR));
        saveButton->setText(QApplication::translate("RecordOpClass", "\344\277\235\345\255\230", Q_NULLPTR));
        recordButton->setText(QApplication::translate("RecordOpClass", "\350\256\260\345\275\225", Q_NULLPTR));
        operateButton->setText(QApplication::translate("RecordOpClass", "\346\223\215\344\275\234", Q_NULLPTR));
        label->setText(QApplication::translate("RecordOpClass", "\346\223\215\344\275\234\346\254\241\346\225\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("RecordOpClass", "\346\223\215\344\275\234\346\226\271\346\241\210", Q_NULLPTR));
        label_3->setText(QApplication::translate("RecordOpClass", "\345\205\267\344\275\223\346\223\215\344\275\234\345\210\227\350\241\250", Q_NULLPTR));
        opDescriptionEdit->setText(QString());
        label_4->setText(QApplication::translate("RecordOpClass", "\346\226\271\346\241\210\345\244\207\346\263\250", Q_NULLPTR));
        menu->setTitle(QApplication::translate("RecordOpClass", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RecordOpClass: public Ui_RecordOpClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECORDOP_H
