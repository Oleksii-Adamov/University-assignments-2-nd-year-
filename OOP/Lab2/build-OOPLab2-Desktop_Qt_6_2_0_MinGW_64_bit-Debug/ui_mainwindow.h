/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_today;
    QPushButton *pushButton_tomorrow;
    QPushButton *pushButton_someday;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(860, 540);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        centralwidget->setMaximumSize(QSize(16777215, 16777215));
        centralwidget->setSizeIncrement(QSize(0, 0));
        centralwidget->setBaseSize(QSize(6, 0));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_today = new QPushButton(centralwidget);
        pushButton_today->setObjectName(QString::fromUtf8("pushButton_today"));
        sizePolicy.setHeightForWidth(pushButton_today->sizePolicy().hasHeightForWidth());
        pushButton_today->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_today);

        pushButton_tomorrow = new QPushButton(centralwidget);
        pushButton_tomorrow->setObjectName(QString::fromUtf8("pushButton_tomorrow"));
        sizePolicy.setHeightForWidth(pushButton_tomorrow->sizePolicy().hasHeightForWidth());
        pushButton_tomorrow->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_tomorrow);

        pushButton_someday = new QPushButton(centralwidget);
        pushButton_someday->setObjectName(QString::fromUtf8("pushButton_someday"));
        sizePolicy.setHeightForWidth(pushButton_someday->sizePolicy().hasHeightForWidth());
        pushButton_someday->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_someday);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 860, 26));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_today->setText(QCoreApplication::translate("MainWindow", "Today tasks", nullptr));
        pushButton_tomorrow->setText(QCoreApplication::translate("MainWindow", "Tomorrow tasks", nullptr));
        pushButton_someday->setText(QCoreApplication::translate("MainWindow", "Someday", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
