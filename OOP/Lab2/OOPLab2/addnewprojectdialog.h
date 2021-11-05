#ifndef ADDNEWPROJECTDIALOG_H
#define ADDNEWPROJECTDIALOG_H
#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class AddNewProjectDialog;
}

class AddNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewProjectDialog(QWidget *parent);
    ~AddNewProjectDialog();

signals:
   void create_project(QString file_path);


private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Create_clicked();



private:
    Ui::AddNewProjectDialog *ui;
    QStringList* m_parent_project_list;
};

#endif // ADDNEWPROJECTDIALOG_H
