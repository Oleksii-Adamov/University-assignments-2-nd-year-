#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include "addtotodolist.h"
#include "filepath.h"
#include "addnewprojectdialog.h"
#include "timer.h"
#include "settingsdialog.h"
ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QMainWindow/*QDialog*/(/*(QWidget*)*/ parent),
    ui(new Ui::ToDoListWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
}
ToDoListWindow::ToDoListWindow(QString file_name, /*QSharedPointer<std::vector<ToDoListData>> list,*/ QWidget *parent)
    :  QMainWindow/*QDialog*/(/*(QWidget*)*/ parent), ui(new Ui::ToDoListWindow), m_file_name(file_name)
{
    // loading from file
    m_data_list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
    QDir dir;
    dir.mkdir(get_project_dir());
    QFile file(m_file_name);
    if (!file.exists()) {
        file.open(QIODevice::NewOnly);
        file.close();
    }
    else {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        while(!in.atEnd()) {
            m_data_list->emplace_back(in);
        }
        file.close();
    }
    // getting project name out of file name
    m_project_name = m_file_name;
    if (!(change_to_file_name_without_extension_bin(m_project_name) && remove_path_from_project_file_name(m_project_name))) {
        this->close();
    }
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
    QFont list_item_font;
    list_item_font.setPointSize(30);
   // m_data_list = list;
    ui->listWidget->setFont(list_item_font);
    ui->listWidget->setSortingEnabled(true);
    for (size_t i = 0; i < m_data_list->size(); i++) {
        ui->listWidget->addItem(((*m_data_list)[i]).ToQString());
    }
    if (ui->listWidget->count() > 0)
        ui->listWidget->setCurrentRow(0);
    ui->listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    QFont title_font;
    title_font.setPointSize(50);
    title_font.setBold(true);
    ui->label->setText(m_project_name);
    ui->label->setFont(title_font);
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
    if (ui->listWidget->count() > 0) {
        Timer* new_dialog = new Timer(this);
        connect(new_dialog, SIGNAL(pomodoro_finished()), this, SLOT(increment_pomodoros()));
        new_dialog->setModal(true);
        new_dialog->show();
    }
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
    // emit silgnal to delete button in MainWindow
    emit delete_project_button(m_project_name);
    this->close();
}

void ToDoListWindow::edit_project(const QString& new_name) {
    ui->label->setText(new_name);
    QFile file(m_file_name);
    m_file_name = get_project_path(new_name);
    if (file.exists()) {
        file.rename(m_file_name);
    }
    else {
        file.setFileName(m_file_name);
        file.open(QFile::NewOnly);
        file.close();
    }
    emit edit_project_button(m_project_name, new_name);
    m_project_name = new_name;
}

void ToDoListWindow::on_actionEditProject_triggered()
{
    AddNewProjectDialog* new_dialog  = new AddNewProjectDialog(this, project::mode::Edit);
    connect(new_dialog, SIGNAL(edit_project(const QString&)), this, SLOT(edit_project(const QString&)));
    new_dialog->setModal(true);
    new_dialog->show();
}


void ToDoListWindow::on_pushButton_task_completed_clicked()
{
    if (ui->listWidget->count() > 0) {
        int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();
        // writing to Comleted prject
        QFile file(get_project_path("Comleted"));
        if (!file.exists()) {
            file.open(QIODevice::NewOnly);
            file.close();
        }
        file.open(QIODevice::Append);
        QDataStream out(&file);
        ((*m_data_list)[index]).write_to_binary(out);
        // deleting from this project
        ui->listWidget->takeItem(index);
        std::vector<ToDoListData>::iterator iter = m_data_list->begin();
        m_data_list->erase(iter + index);
    }
}

void ToDoListWindow::increment_pomodoros() {
    int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();
    (*m_data_list)[index].done += 1;
    ui->listWidget->currentItem()->setData(Qt::EditRole, (*m_data_list)[index].ToQString());
}

void ToDoListWindow::update_list() {
    for (size_t i = 0; i < m_data_list->size(); i++) {
        ui->listWidget->item(i)->setData(Qt::EditRole, ((*m_data_list)[i]).ToQString());
    }
}

void ToDoListWindow::on_actionSettings_triggered()
{
    SettingsDialog* new_dialog = new SettingsDialog(this);
    connect(new_dialog, SIGNAL(pomodoro_duration_changed()), this, SLOT(update_list()));
    new_dialog->setModal(true);
    new_dialog->show();
}
