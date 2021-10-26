/********************************************************************************
** Form generated from reading UI file 'todolistwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TODOLISTWINDOW_H
#define UI_TODOLISTWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToDoListWindow
{
public:
    QAction *actionBack;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QListWidget *listWidget;
    QPushButton *pushButtonAdd;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonStartTimer;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ToDoListWindow)
    {
        if (ToDoListWindow->objectName().isEmpty())
            ToDoListWindow->setObjectName(QString::fromUtf8("ToDoListWindow"));
        ToDoListWindow->resize(708, 363);
        actionBack = new QAction(ToDoListWindow);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        centralwidget = new QWidget(ToDoListWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 2);

        pushButtonAdd = new QPushButton(centralwidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));

        gridLayout->addWidget(pushButtonAdd, 1, 1, 1, 1);

        pushButtonEdit = new QPushButton(centralwidget);
        pushButtonEdit->setObjectName(QString::fromUtf8("pushButtonEdit"));

        gridLayout->addWidget(pushButtonEdit, 1, 0, 1, 1);

        pushButtonStartTimer = new QPushButton(centralwidget);
        pushButtonStartTimer->setObjectName(QString::fromUtf8("pushButtonStartTimer"));

        gridLayout->addWidget(pushButtonStartTimer, 2, 0, 1, 2);

        ToDoListWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ToDoListWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 708, 26));
        ToDoListWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ToDoListWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ToDoListWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(ToDoListWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        ToDoListWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionBack);

        retranslateUi(ToDoListWindow);

        QMetaObject::connectSlotsByName(ToDoListWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ToDoListWindow)
    {
        ToDoListWindow->setWindowTitle(QCoreApplication::translate("ToDoListWindow", "MainWindow", nullptr));
        actionBack->setText(QCoreApplication::translate("ToDoListWindow", "Back", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("ToDoListWindow", "Add", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("ToDoListWindow", "Edit", nullptr));
        pushButtonStartTimer->setText(QCoreApplication::translate("ToDoListWindow", "StartTimer", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("ToDoListWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToDoListWindow: public Ui_ToDoListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLISTWINDOW_H
