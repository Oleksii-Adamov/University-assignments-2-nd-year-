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
    this->setCentralWidget(ui->listView);
}

ToDoListWindow::~ToDoListWindow()
{
    delete ui;
}
void ToDoListWindow::setList(QSharedPointer<QStringList> list) {
    m_list = list;
    m_list_model = new QStringListModel(this); // get deleted when this destroyed
    m_list_model->setStringList(*list);
    ui->listView->setModel(m_list_model);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


void ToDoListWindow::on_actionBack_triggered()
{
    this->close();
}

