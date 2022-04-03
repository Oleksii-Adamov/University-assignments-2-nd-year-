#include "addnewprojectdialog.h"
#include "ui_addnewprojectdialog.h"
#include <QRegularExpressionValidator>
#include <QFile>
#include <QMessageBox>
#include "filepath.h"

AddNewProjectDialog::AddNewProjectDialog(QWidget *parent, project::mode mode) :
    QDialog((QWidget*) parent),
    ui(new Ui::AddNewProjectDialog),
    m_mode(mode)
{
    ui->setupUi(this);
    QRegularExpression rx("^[a-zA-ZА-Яа-я0-9ЁёІЇІЇҐґ_ -]+$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setMaxLength(24);
    if (m_mode == project::mode::Edit) {
        ui->label->setText("New project name:");
        ui->pushButton_Create->setText("Edit");
    }
}

AddNewProjectDialog::~AddNewProjectDialog()
{
    delete ui;
}

void AddNewProjectDialog::on_pushButton_Cancel_clicked()
{
    this->close();
}


void AddNewProjectDialog::on_pushButton_Create_clicked()
{
    QFile file(get_project_path(ui->lineEdit->text()));
    if (file.exists()) {
        QMessageBox::critical(this, "Error", "Project with this name already exists!");
    }
    else {
        // emmit signal, ToDoListWindow catches
        if (m_mode == project::mode::Add) {
            emit create_project(ui->lineEdit->text());
        }
        else { // Edit
            emit edit_project(ui->lineEdit->text());
        }
        this->close();
    }
}

