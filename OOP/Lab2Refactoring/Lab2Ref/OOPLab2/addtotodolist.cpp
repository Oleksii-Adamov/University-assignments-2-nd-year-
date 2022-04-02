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

AddToToDoList::AddToToDoList(QWidget *parent, std::vector<ToDoListData>* parent_data_list,
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
        ui->spinBox_priority->setValue((*m_parent_data_list)[index].priority);
        ui->lineEditNameofTask->setText((*m_parent_data_list)[index].name);
    }
}

void AddToToDoList::on_pushButtonCreate_clicked()
{
    if (m_mode == ToDoList::mode::Edit) {
        int index = m_parent_list_widget->indexFromItem(m_parent_list_widget->currentItem()).row();
        (*m_parent_data_list)[index].name = ui->lineEditNameofTask->text();
        (*m_parent_data_list)[index].predicted = ui->spinBox->value();
        (*m_parent_data_list)[index].priority = ui->spinBox_priority->value();
        m_parent_list_widget->currentItem()->setData(Qt::EditRole, (*m_parent_data_list)[index].ToQString());
    }
    if (m_mode == ToDoList::mode::Add) {
        m_parent_data_list->emplace_back(ui->spinBox_priority->value(), ui->lineEditNameofTask->text(), 0, ui->spinBox->value());
        QListWidgetItem* new_item = new QListWidgetItem;
        new_item->setData(Qt::EditRole, m_parent_data_list->back().ToQString());
        m_parent_list_widget->addItem(new_item);
        m_parent_list_widget->setCurrentItem(new_item);
    }
    std::sort(m_parent_data_list->begin(), m_parent_data_list->begin() + m_parent_data_list->size());
    this->close();
}


void AddToToDoList::on_pushButtonCancel_clicked()
{
    this->close();
}

