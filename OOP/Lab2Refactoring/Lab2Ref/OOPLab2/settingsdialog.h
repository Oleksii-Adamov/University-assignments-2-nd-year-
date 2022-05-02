#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    friend class UnitTests;
public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

private slots:
    void on_pushButton_cancel_clicked();

    void on_pushButton_apply_clicked();

    void on_pushButton_default_clicked();

private:
    Ui::SettingsDialog *ui;
    int m_prev_pomodoro_duration;
};

#endif // SETTINGSDIALOG_H
