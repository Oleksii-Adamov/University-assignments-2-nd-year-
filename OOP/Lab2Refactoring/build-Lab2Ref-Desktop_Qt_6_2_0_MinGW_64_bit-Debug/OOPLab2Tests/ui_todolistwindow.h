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
#include <QtWidgets/QLabel>
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
    QAction *actionDelete_this_project;
    QAction *actionEditProject;
    QAction *actionSettings;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonStartTimer;
    QListWidget *listWidget;
    QLabel *label;
    QPushButton *pushButtonEdit;
    QPushButton *pushButtonDelete;
    QPushButton *pushButtonAdd;
    QPushButton *pushButton_task_completed;
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
        QFont font;
        font.setPointSize(20);
        actionBack->setFont(font);
        actionDelete_this_project = new QAction(ToDoListWindow);
        actionDelete_this_project->setObjectName(QString::fromUtf8("actionDelete_this_project"));
        actionDelete_this_project->setFont(font);
        actionEditProject = new QAction(ToDoListWindow);
        actionEditProject->setObjectName(QString::fromUtf8("actionEditProject"));
        actionEditProject->setFont(font);
        actionSettings = new QAction(ToDoListWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionSettings->setFont(font);
        centralwidget = new QWidget(ToDoListWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButtonStartTimer = new QPushButton(centralwidget);
        pushButtonStartTimer->setObjectName(QString::fromUtf8("pushButtonStartTimer"));

        gridLayout->addWidget(pushButtonStartTimer, 3, 0, 1, 3);

        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setResizeMode(QListView::Adjust);

        gridLayout->addWidget(listWidget, 1, 0, 1, 3);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 3);

        pushButtonEdit = new QPushButton(centralwidget);
        pushButtonEdit->setObjectName(QString::fromUtf8("pushButtonEdit"));

        gridLayout->addWidget(pushButtonEdit, 2, 1, 1, 1);

        pushButtonDelete = new QPushButton(centralwidget);
        pushButtonDelete->setObjectName(QString::fromUtf8("pushButtonDelete"));

        gridLayout->addWidget(pushButtonDelete, 2, 0, 1, 1);

        pushButtonAdd = new QPushButton(centralwidget);
        pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));

        gridLayout->addWidget(pushButtonAdd, 2, 2, 1, 1);

        pushButton_task_completed = new QPushButton(centralwidget);
        pushButton_task_completed->setObjectName(QString::fromUtf8("pushButton_task_completed"));

        gridLayout->addWidget(pushButton_task_completed, 4, 0, 1, 3);

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
        toolBar->addAction(actionDelete_this_project);
        toolBar->addAction(actionEditProject);
        toolBar->addAction(actionSettings);

        retranslateUi(ToDoListWindow);

        QMetaObject::connectSlotsByName(ToDoListWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ToDoListWindow)
    {
        ToDoListWindow->setWindowTitle(QCoreApplication::translate("ToDoListWindow", "MainWindow", nullptr));
        actionBack->setText(QCoreApplication::translate("ToDoListWindow", "Back", nullptr));
        actionDelete_this_project->setText(QCoreApplication::translate("ToDoListWindow", "Delete project", nullptr));
        actionEditProject->setText(QCoreApplication::translate("ToDoListWindow", "Edit Project", nullptr));
        actionSettings->setText(QCoreApplication::translate("ToDoListWindow", "Settings", nullptr));
        pushButtonStartTimer->setText(QCoreApplication::translate("ToDoListWindow", "StartTimer", nullptr));
        label->setText(QCoreApplication::translate("ToDoListWindow", "TextLabel", nullptr));
        pushButtonEdit->setText(QCoreApplication::translate("ToDoListWindow", "Edit", nullptr));
        pushButtonDelete->setText(QCoreApplication::translate("ToDoListWindow", "Delete", nullptr));
        pushButtonAdd->setText(QCoreApplication::translate("ToDoListWindow", "Add", nullptr));
        pushButton_task_completed->setText(QCoreApplication::translate("ToDoListWindow", "Task Comleted", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("ToDoListWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToDoListWindow: public Ui_ToDoListWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TODOLISTWINDOW_H
