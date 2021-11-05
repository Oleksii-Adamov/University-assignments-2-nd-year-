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
    QRegularExpression rx("^[a-zA-Z0-9_ -]+$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setMaxLength(50);
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
    if (m_mode == project::mode::Add) {
        if (file.exists()) {
            QMessageBox::critical(this, "Error", "Project with this name already exists!");
        }
        else {
            emit create_project(ui->lineEdit->text());
            this->close();
        }
    }
    else { // Edit
        // emmit signal to edit
        emit edit_project(ui->lineEdit->text());
        this->close();
    }
}

