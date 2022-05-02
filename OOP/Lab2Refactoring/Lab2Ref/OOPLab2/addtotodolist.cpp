#include "addtotodolist.h"
#include "ui_addtotodolist.h"
#include <QIntValidator>
AddToToDoList::AddToToDoList(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddToToDoList)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(99);
    ui->spinBox->setSingleStep(1);
    ui->spinBox->setValue(0);
}

AddToToDoList::~AddToToDoList()
{
    delete ui;
}

Ui::AddToToDoList** AddToToDoList::get_ui() {
    return &ui;
}

AddToToDoList::AddToToDoList(QWidget *parent, QSharedPointer<ToDoListModel> parent_model, ToDoList::mode mode, int current_index)
    : QDialog(parent), ui(new Ui::AddToToDoList), m_parent_model(parent_model), m_mode(mode), m_current_index(current_index)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(99);
    ui->spinBox->setSingleStep(1);
    ui->spinBox->setValue(0);
    if (mode == ToDoList::mode::Edit) {
        ui->pushButtonCreate->setText("Apply");
        ToDoListData data = m_parent_model->ToDoListItemData(m_parent_model->index(m_current_index));
        ui->spinBox->setValue(data.predicted);
        ui->spinBox_priority->setValue(data.priority);
        ui->lineEditNameofTask->setText(data.name);
    }
}

void AddToToDoList::on_pushButtonCreate_clicked()
{
    ToDoListData new_data(ui->spinBox_priority->value(), ui->lineEditNameofTask->text(), 0, ui->spinBox->value());
    if (m_mode == ToDoList::mode::Edit) {
        m_parent_model->setData(m_parent_model->index(m_current_index), QVariant::fromValue(new_data));
    }
    if (m_mode == ToDoList::mode::Add) {
        m_parent_model->insertRows(m_parent_model->rowCount(), 1);
        m_parent_model->setData(m_parent_model->index(m_parent_model->rowCount() - 1), QVariant::fromValue(new_data));
    }
    this->close();
}


void AddToToDoList::on_pushButtonCancel_clicked()
{
    this->close();
}

