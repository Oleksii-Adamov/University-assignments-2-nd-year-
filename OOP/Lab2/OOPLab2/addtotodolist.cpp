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

AddToToDoList::AddToToDoList(QWidget *parent, QSharedPointer<std::vector<ToDoListData>> parent_data_list,
                             QListWidget* parent_list_widget, ToDoList::mode mode)
    : QDialog(parent), ui(new Ui::AddToToDoList), m_parent_data_list(parent_data_list), m_parent_list_widget(parent_list_widget),
      m_mode(mode)
{
    ui->setupUi(this);
    ui->spinBox->setMinimum(0);
    ui->spinBox->setMaximum(99);
    ui->spinBox->setSingleStep(1);
    ui->spinBox->setValue(0);
    if (mode == ToDoList::mode::Edit) {
        ui->pushButtonCreate->setText("Apply");
        int index = m_parent_list_widget->indexFromItem(m_parent_list_widget->currentItem()).row();
        ui->spinBox->setValue((*m_parent_data_list)[index].predicted);
    }
}

void AddToToDoList::on_pushButtonCreate_clicked()
{
    if (m_mode == ToDoList::mode::Edit) {
        int index = m_parent_list_widget->indexFromItem(m_parent_list_widget->currentItem()).row();
        (*m_parent_data_list)[index].name = ui->lineEditNameofTask->text();
        (*m_parent_data_list)[index].predicted = ui->spinBox->value();
        m_parent_list_widget->currentItem()->setData(Qt::EditRole, (*m_parent_data_list)[index].ToQString());
    }
    if (m_mode == ToDoList::mode::Add) {
        m_parent_data_list->emplace_back(ui->lineEditNameofTask->text(), 0, ui->spinBox->value());
        m_parent_list_widget->addItem(m_parent_data_list->back().ToQString());
    }
    this->close();
}


void AddToToDoList::on_pushButtonCancel_clicked()
{
    this->close();
}

