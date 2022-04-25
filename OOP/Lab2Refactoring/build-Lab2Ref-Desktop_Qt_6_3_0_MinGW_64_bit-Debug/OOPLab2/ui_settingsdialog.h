/********************************************************************************
** Form generated from reading UI file 'settingsdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_apply;
    QSpinBox *spinBox_pomodoro;
    QSpinBox *spinBox_break;
    QPushButton *pushButton_default;
    QLabel *label_2;
    QLabel *label;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(315, 168);
        gridLayout = new QGridLayout(SettingsDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_cancel = new QPushButton(SettingsDialog);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));

        gridLayout->addWidget(pushButton_cancel, 4, 0, 1, 1);

        pushButton_apply = new QPushButton(SettingsDialog);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

        gridLayout->addWidget(pushButton_apply, 4, 2, 1, 1);

        spinBox_pomodoro = new QSpinBox(SettingsDialog);
        spinBox_pomodoro->setObjectName(QString::fromUtf8("spinBox_pomodoro"));
        spinBox_pomodoro->setMaximum(999);

        gridLayout->addWidget(spinBox_pomodoro, 0, 2, 1, 1);

        spinBox_break = new QSpinBox(SettingsDialog);
        spinBox_break->setObjectName(QString::fromUtf8("spinBox_break"));
        spinBox_break->setMaximum(999);

        gridLayout->addWidget(spinBox_break, 3, 2, 1, 1);

        pushButton_default = new QPushButton(SettingsDialog);
        pushButton_default->setObjectName(QString::fromUtf8("pushButton_default"));

        gridLayout->addWidget(pushButton_default, 4, 1, 1, 1);

        label_2 = new QLabel(SettingsDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 3, 0, 1, 2);

        label = new QLabel(SettingsDialog);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QCoreApplication::translate("SettingsDialog", "Dialog", nullptr));
        pushButton_cancel->setText(QCoreApplication::translate("SettingsDialog", "Cancel", nullptr));
        pushButton_apply->setText(QCoreApplication::translate("SettingsDialog", "Apply", nullptr));
        pushButton_default->setText(QCoreApplication::translate("SettingsDialog", "Default", nullptr));
        label_2->setText(QCoreApplication::translate("SettingsDialog", "Duration of break in minutes:", nullptr));
        label->setText(QCoreApplication::translate("SettingsDialog", "Duration of pomodoro in minutes:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H
