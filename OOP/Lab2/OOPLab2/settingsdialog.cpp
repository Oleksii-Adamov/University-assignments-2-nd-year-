#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFile>
#include "filepath.h"
SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QFile file(get_settings_path());
    if(file.exists()) {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        int prev_pomodoro_duration, prev_break_duration;
        in >> prev_pomodoro_duration >> prev_break_duration;
        ui->spinBox_pomodoro->setValue(prev_pomodoro_duration);
        ui->spinBox_break->setValue(prev_break_duration);
        file.close();
    }
    else { // setup default settings
        ui->spinBox_pomodoro->setValue(20);
        ui->spinBox_break->setValue(5);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out << 20  << 5;
    }
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_pushButton_cancel_clicked()
{
    this->close();
}


void SettingsDialog::on_pushButton_apply_clicked()
{
    QFile file(get_settings_path());
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << ui->spinBox_pomodoro->value() << ui->spinBox_break->value();
    file.close();
    this->close();
}


void SettingsDialog::on_pushButton_default_clicked()
{
    ui->spinBox_pomodoro->setValue(20);
    ui->spinBox_break->setValue(5);
}

