/********************************************************************************
** Form generated from reading UI file 'timer.ui'
**
** Created by: Qt User Interface Compiler version 6.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMER_H
#define UI_TIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Timer
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_state;
    QLabel *label_time;
    QPushButton *pushButton_stop_skip_start;

    void setupUi(QDialog *Timer)
    {
        if (Timer->objectName().isEmpty())
            Timer->setObjectName(QString::fromUtf8("Timer"));
        Timer->resize(400, 300);
        verticalLayout = new QVBoxLayout(Timer);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_state = new QLabel(Timer);
        label_state->setObjectName(QString::fromUtf8("label_state"));
        QFont font;
        font.setPointSize(20);
        label_state->setFont(font);
        label_state->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_state);

        label_time = new QLabel(Timer);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setFont(font);
        label_time->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_time);

        pushButton_stop_skip_start = new QPushButton(Timer);
        pushButton_stop_skip_start->setObjectName(QString::fromUtf8("pushButton_stop_skip_start"));

        verticalLayout->addWidget(pushButton_stop_skip_start);


        retranslateUi(Timer);

        QMetaObject::connectSlotsByName(Timer);
    } // setupUi

    void retranslateUi(QDialog *Timer)
    {
        Timer->setWindowTitle(QCoreApplication::translate("Timer", "Dialog", nullptr));
        label_state->setText(QCoreApplication::translate("Timer", "State", nullptr));
        label_time->setText(QCoreApplication::translate("Timer", "Time left", nullptr));
        pushButton_stop_skip_start->setText(QCoreApplication::translate("Timer", "Stop/Skip/Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Timer: public Ui_Timer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMER_H
