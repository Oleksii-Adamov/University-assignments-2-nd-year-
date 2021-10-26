#include "todolistwindow.h"
#include "ui_todolistwindow.h"

ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToDoListWindow)
{
    m_parent = parent;
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
        m_string_list.append(((*m_data_list)[i]).ToQString());
    }
    m_list_model = new QStringListModel(this); // get deleted when this destroyed
    m_list_model->setStringList(m_string_list);
    ui->listView->setModel(m_list_model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void ToDoListWindow::on_actionBack_triggered()
{
    this->close();
}


void ToDoListWindow::on_pushButtonAdd_clicked()
{

}


void ToDoListWindow::on_pushButtonStartTimer_clicked()
{

}

