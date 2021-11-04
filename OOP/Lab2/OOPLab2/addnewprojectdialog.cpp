#include "addnewprojectdialog.h"
#include "ui_addnewprojectdialog.h"
#include <QRegularExpressionValidator>
//#include "QRegularExpression"
AddNewProjectDialog::AddNewProjectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddNewProjectDialog)
{
    ui->setupUi(this);
    QRegularExpression rx("^[a-zA-Z0-9_ -]+$");
    QValidator* validator = new QRegularExpressionValidator(rx, this);
    ui->lineEdit->setValidator(validator);
    ui->lineEdit->setMaxLength(50);
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

}

