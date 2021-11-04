#ifndef ADDNEWPROJECTDIALOG_H
#define ADDNEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class AddNewProjectDialog;
}

class AddNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewProjectDialog(QWidget *parent = nullptr);
    ~AddNewProjectDialog();

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Create_clicked();

private:
    Ui::AddNewProjectDialog *ui;
};

#endif // ADDNEWPROJECTDIALOG_H
