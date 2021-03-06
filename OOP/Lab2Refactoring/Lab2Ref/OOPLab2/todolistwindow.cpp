#include "todolistwindow.h"
#include "ui_todolistwindow.h"
#include "addtotodolist.h"
#include "filepath.h"
#include "addnewprojectdialog.h"
#include "timer.h"
#include "settingsdialog.h"

ToDoListWindow::ToDoListWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ToDoListWindow)
{
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
}
ToDoListWindow::ToDoListWindow(QString project_name, QWidget *parent)
    :  QMainWindow(parent), ui(new Ui::ToDoListWindow), m_project_name(project_name)
{
    model.reset(new ToDoListModel());

    model->load_from_file(get_project_path(m_project_name));

    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->listView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    QFont list_view_font;
    list_view_font.setPointSize(30);
    ui->listView->setFont(list_view_font);

    if (model->rowCount() > 0)
        ui->listView->setCurrentIndex(model->index(0));
    ui->listView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    ui->listView->setModel(model.data());
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
        model->write_to_file(get_project_path(m_project_name));
    }

    delete ui;
}
void ToDoListWindow::on_actionBack_triggered()
{
    this->close();
}


void ToDoListWindow::on_pushButtonAdd_clicked()
{
   AddToToDoList* new_dialog = new AddToToDoList(this, model, ToDoList::mode::Add);
   new_dialog->setModal(true);
   new_dialog->show();
}


void ToDoListWindow::on_pushButtonStartTimer_clicked()
{
    if (model->rowCount() > 0) {
        Timer* new_dialog = new Timer(this);
        connect(new_dialog, SIGNAL(pomodoro_finished()), this, SLOT(increment_pomodoros()));
        new_dialog->setModal(true);
        new_dialog->show();
    }
}

void ToDoListWindow::on_pushButtonEdit_clicked()
{
    if (model->rowCount() > 0) {
        AddToToDoList* new_dialog = new AddToToDoList(this, model, ToDoList::mode::Edit, ui->listView->currentIndex().row());
        new_dialog->setModal(true);
        new_dialog->show();
    }
}

void ToDoListWindow::on_pushButtonDelete_clicked()
{
     if (model->rowCount() > 0) {
         model->removeRows(ui->listView->currentIndex().row(), 1);
     }
}


void ToDoListWindow::on_actionDelete_this_project_triggered()
{

    // delete file
    delete_file(get_project_path(m_project_name));
    m_is_deleted = true;

    // emit silgnal to delete button in MainWindow
    emit delete_project_button(m_project_name);
    this->close();
}

void ToDoListWindow::edit_project(const QString& new_name) {

    ui->label->setText(new_name);

    rename_file(get_project_path(m_project_name), get_project_path(new_name));

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
    if (model->rowCount() > 0) {
        QModelIndex index = ui->listView->currentIndex();

        // writing to Comleted prject
        task_to_completed(model->ToDoListItemData(index));

        // deleting from this project
        model->removeRows(index.row(), 1);
    }
}

void ToDoListWindow::increment_pomodoros() {
    model->increment_pomodoros(ui->listView->currentIndex());
}

void ToDoListWindow::on_actionSettings_triggered()
{
    SettingsDialog* new_dialog = new SettingsDialog(this);
    new_dialog->setModal(true);
    new_dialog->show();
}
