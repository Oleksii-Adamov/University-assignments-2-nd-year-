/********************************************************************************
** Form generated from reading UI file 'addtotodolist.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTOTODOLIST_H
#define UI_ADDTOTODOLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddToToDoList
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEditNameofTask;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpinBox *spinBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSpinBox *spinBox_priority;
    QPushButton *pushButtonCreate;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *AddToToDoList)
    {
        if (AddToToDoList->objectName().isEmpty())
            AddToToDoList->setObjectName(QString::fromUtf8("AddToToDoList"));
        AddToToDoList->resize(338, 221);
        verticalLayout = new QVBoxLayout(AddToToDoList);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(AddToToDoList);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEditNameofTask = new QLineEdit(AddToToDoList);
        lineEditNameofTask->setObjectName(QString::fromUtf8("lineEditNameofTask"));
        lineEditNameofTask->setMaxLength(40);

        horizontalLayout->addWidget(lineEditNameofTask);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(AddToToDoList);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox = new QSpinBox(AddToToDoList);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_2->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(AddToToDoList);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_3);

        spinBox_priority = new QSpinBox(AddToToDoList);
        spinBox_priority->setObjectName(QString::fromUtf8("spinBox_priority"));
        spinBox_priority->setMinimum(0);
        spinBox_priority->setMaximum(9);

        horizontalLayout_3->addWidget(spinBox_priority);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButtonCreate = new QPushButton(AddToToDoList);
        pushButtonCreate->setObjectName(QString::fromUtf8("pushButtonCreate"));

        verticalLayout->addWidget(pushButtonCreate);

        pushButtonCancel = new QPushButton(AddToToDoList);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        verticalLayout->addWidget(pushButtonCancel);


        retranslateUi(AddToToDoList);

        QMetaObject::connectSlotsByName(AddToToDoList);
    } // setupUi

    void retranslateUi(QDialog *AddToToDoList)
    {
        AddToToDoList->setWindowTitle(QCoreApplication::translate("AddToToDoList", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AddToToDoList", "Name of the task:", nullptr));
        label_2->setText(QCoreApplication::translate("AddToToDoList", "Your prediction on number of pomodoros:", nullptr));
        label_3->setText(QCoreApplication::translate("AddToToDoList", "Priority:", nullptr));
        pushButtonCreate->setText(QCoreApplication::translate("AddToToDoList", "Create", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("AddToToDoList", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddToToDoList: public Ui_AddToToDoList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTOTODOLIST_H
