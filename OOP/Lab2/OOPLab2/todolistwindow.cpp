#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include "addtotodolist.h"
#include "filepath.h"

ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToDoListWindow)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
}
ToDoListWindow::ToDoListWindow(QString file_name, QSharedPointer<std::vector<ToDoListData>> list, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::ToDoListWindow), m_file_name(file_name)
{
    ui->setupUi(this);
    this->setWindowModality(Qt::WindowModal);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
    QFont list_item_font;
    list_item_font.setPointSize(30);
    m_data_list = list;
    ui->listWidget->setFont(list_item_font);
    for (size_t i = 0; i < m_data_list->size(); i++) {
        ui->listWidget->addItem(((*m_data_list)[i]).ToQString());
    }
    if (ui->listWidget->count() > 0)
        ui->listWidget->setCurrentRow(0);
    ui->listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
}
ToDoListWindow::~ToDoListWindow()
{
    // write to file
    if (!m_is_deleted) {
        QFile file(m_file_name);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        for (size_t i = 0; i < m_data_list->size(); i++) {
            ((*m_data_list)[i]).write_to_binary(out);
        }
    }
    delete ui;
}
void ToDoListWindow::on_actionBack_triggered()
{
    this->close();
}


void ToDoListWindow::on_pushButtonAdd_clicked()
{
   AddToToDoList* new_dialog = new AddToToDoList(this, m_data_list, ui->listWidget, ToDoList::mode::Add);
   new_dialog->setModal(true);
   new_dialog->show();
}


void ToDoListWindow::on_pushButtonStartTimer_clicked()
{

}

void ToDoListWindow::on_pushButtonEdit_clicked()
{
    if (ui->listWidget->count() > 0) {
        AddToToDoList* new_dialog = new AddToToDoList(this, m_data_list, ui->listWidget, ToDoList::mode::Edit);
        new_dialog->setModal(true);
        new_dialog->show();
    }
}

void ToDoListWindow::on_pushButtonDelete_clicked()
{
     if (ui->listWidget->count() > 0) {
         int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();
         ui->listWidget->takeItem(index);
         std::vector<ToDoListData>::iterator iter = m_data_list->begin();
         m_data_list->erase(iter + index);
     }
}


void ToDoListWindow::on_actionDelete_this_project_triggered()
{
    // delete file
    QFile file(m_file_name);
    file.remove();
    m_is_deleted = true;
    // get button name
    if (change_to_file_name_without_extension_bin(m_file_name) && remove_path_from_project_file_name(m_file_name)) {
        // emit silgnal to delete button in MainWindow
        emit delete_project_button(m_file_name);
    }
    this->close();
}

