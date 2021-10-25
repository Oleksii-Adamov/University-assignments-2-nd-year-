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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToDoListWindow
{
public:
    QAction *actionBack;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QListView *listView;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *ToDoListWindow)
    {
        if (ToDoListWindow->objectName().isEmpty())
            ToDoListWindow->setObjectName(QString::fromUtf8("ToDoListWindow"));
        ToDoListWindow->resize(813, 459);
        actionBack = new QAction(ToDoListWindow);
        actionBack->setObjectName(QString::fromUtf8("actionBack"));
        centralwidget = new QWidget(ToDoListWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        listView = new QListView(centralwidget);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        ToDoListWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ToDoListWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 813, 26));
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
        toolBar->setWindowTitle(QCoreApplication::translate("ToDoListWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToDoListWindow: public Ui_ToDoListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLISTWINDOW_H
