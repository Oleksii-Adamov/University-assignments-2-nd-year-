/********************************************************************************
** Form generated from reading UI file 'addnewprojectdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNEWPROJECTDIALOG_H
#define UI_ADDNEWPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddNewProjectDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton_Create;
    QPushButton *pushButton_Cancel;

    void setupUi(QDialog *AddNewProjectDialog)
    {
        if (AddNewProjectDialog->objectName().isEmpty())
            AddNewProjectDialog->setObjectName(QString::fromUtf8("AddNewProjectDialog"));
        AddNewProjectDialog->resize(400, 300);
        gridLayout = new QGridLayout(AddNewProjectDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(AddNewProjectDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(AddNewProjectDialog);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        pushButton_Create = new QPushButton(AddNewProjectDialog);
        pushButton_Create->setObjectName(QString::fromUtf8("pushButton_Create"));

        gridLayout->addWidget(pushButton_Create, 1, 0, 1, 2);

        pushButton_Cancel = new QPushButton(AddNewProjectDialog);
        pushButton_Cancel->setObjectName(QString::fromUtf8("pushButton_Cancel"));

        gridLayout->addWidget(pushButton_Cancel, 2, 0, 1, 2);


        retranslateUi(AddNewProjectDialog);

        QMetaObject::connectSlotsByName(AddNewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *AddNewProjectDialog)
    {
        AddNewProjectDialog->setWindowTitle(QCoreApplication::translate("AddNewProjectDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddNewProjectDialog", "Project name:", nullptr));
        pushButton_Create->setText(QCoreApplication::translate("AddNewProjectDialog", "Create", nullptr));
        pushButton_Cancel->setText(QCoreApplication::translate("AddNewProjectDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddNewProjectDialog: public Ui_AddNewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNEWPROJECTDIALOG_H
