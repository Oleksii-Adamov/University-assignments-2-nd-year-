#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include "addtotodolist.h"

ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToDoListWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
}

ToDoListWindow::~ToDoListWindow()
{
    delete ui;
}
void ToDoListWindow::setList(QSharedPointer<std::vector<ToDoListData>> list) {
    m_data_list = list;
    for (size_t i = 0; i < m_data_list->size(); i++) {
        ui->listWidget->addItem(((*m_data_list)[i]).ToQString());
    }
}
void ToDoListWindow::on_actionBack_triggered()
{
    this->close();
}


void ToDoListWindow::on_pushButtonAdd_clicked()
{
   AddToToDoList* new_dialog = new AddToToDoList(this, m_data_list, ui->listWidget);
   new_dialog->setModal(true);
   new_dialog->show();
}


void ToDoListWindow::on_pushButtonStartTimer_clicked()
{

}

