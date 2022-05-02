#ifndef ADDNEWPROJECTDIALOG_H
#define ADDNEWPROJECTDIALOG_H
#include <QDialog>
#include "mainwindow.h"
namespace project {
    enum mode {
        Add,
        Edit
    };
}
namespace Ui {
class AddNewProjectDialog;
}

/// Adds new project or edits current project based on project::mode mode
class AddNewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddNewProjectDialog(QWidget *parent, project::mode mode = project::mode::Add);
    ~AddNewProjectDialog();

signals:
   void create_project(const QString& file_path);
   void edit_project(const QString& new_name);

private slots:
    void on_pushButton_Cancel_clicked();

    void on_pushButton_Create_clicked();

private:
    Ui::AddNewProjectDialog *ui;
    project::mode m_mode;
};

#endif // ADDNEWPROJECTDIALOG_H
