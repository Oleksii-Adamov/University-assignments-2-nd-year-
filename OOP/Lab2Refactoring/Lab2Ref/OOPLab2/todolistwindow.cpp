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
ToDoListWindow::ToDoListWindow(QString file_name, QWidget *parent)
    :  QMainWindow(parent), ui(new Ui::ToDoListWindow), m_file_name(file_name)
{
    model.reset(new ToDoListModel());
    // not ui {
    //ToDoListModel* model = &model_obj;
    //ToDoListModel model_obj;
   // model = /*new ToDoListModel()*/&model_obj;
    //model = new ToDoListModel2();
    /*(oDoListModel* model = new ToDoListModel();*/
    // loading from file
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
            //m_data_list.emplace_back(in);
            model->insertRows(model->rowCount(), 1);
            model->setData(model->index(model->rowCount() - 1), QVariant::fromValue(ToDoListData(in)));
        }
        file.close();
    }

    // }

    // getting project name out of file name
    m_project_name = m_file_name;
    if (!(change_to_file_name_without_extension_bin(m_project_name) && remove_path_from_project_file_name(m_project_name))) {
        this->close();
    }
    ui->setupUi(this);
    this->setWindowState(Qt::WindowMaximized);
    this->setBackgroundRole(QPalette::Window);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->listView->setEditTriggers(QListView::EditTrigger::NoEditTriggers);
    QFont list_view_font;
    list_view_font.setPointSize(30);
    //ui->listWidget->setFont(list_item_font);
    ui->listView->setFont(list_view_font);
    //ui->listWidget->setSortingEnabled(true);

    // consider Model-View(Control) (without it there will be a lot of not ui logic in listWidget)
/*
    for (size_t i = 0; i < m_data_list.size(); i++) {
        ui->listWidget->addItem((m_data_list[i]).ToQString());
    }
    if (ui->listWidget->count() > 0)
        ui->listWidget->setCurrentRow(0);
    ui->listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);*/
    ui->listView->setModel(model.data());
    QFont title_font;
    title_font.setPointSize(50);
    title_font.setBold(true);
    ui->label->setText(m_project_name);
    ui->label->setFont(title_font);
}
ToDoListWindow::~ToDoListWindow()
{
    // not ui {

    // write to file
    if (!m_is_deleted) {
        QFile file(m_file_name);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        std::size_t size = model->rowCount();
        for (std::size_t i = 0; i < size; i++) {
            // kind of Law of Demeter violation, but because model is data storage, I think that's OK.
            model->ToDoListItemData(model->index(i)).write_to_binary(out);
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
         /*int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();
         ui->listWidget->takeItem(index);
         std::vector<ToDoListData>::iterator iter = m_data_list.begin();
         m_data_list.erase(iter + index);*/
         model->removeRows(ui->listView->currentIndex().row(), 1);
     }
}


void ToDoListWindow::on_actionDelete_this_project_triggered()
{

    // not ui (files) {

    // delete file
    QFile file(m_file_name);
    file.remove();
    m_is_deleted = true;

    // }

    // emit silgnal to delete button in MainWindow
    emit delete_project_button(m_project_name);
    this->close();
}

void ToDoListWindow::edit_project(const QString& new_name) {

    // not ui (files) {
    ui->label->setText(new_name);
    QFile file(m_file_name);

    if (file.exists()) {
        file.rename(get_project_path(new_name));
    }
    else {
        file.setFileName(get_project_path(new_name));
        file.open(QFile::NewOnly);
        file.close();
    }

    // }

    emit edit_project_button(m_project_name, new_name);
    m_file_name = get_project_path(new_name);
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
    /*if (ui->listWidget->count() > 0) {
        int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();

        // not ui (files) {

        // writing to Comleted prject
        QFile file(get_project_path("Comleted"));
        if (!file.exists()) {
            file.open(QIODevice::NewOnly);
            file.close();
        }
        file.open(QIODevice::Append);
        QDataStream out(&file);
        (m_data_list[index]).write_to_binary(out);

        // }

        // deleting from this project
        ui->listWidget->takeItem(index);
        std::vector<ToDoListData>::iterator iter = m_data_list.begin();
        m_data_list.erase(iter + index);
    }*/
}

void ToDoListWindow::increment_pomodoros() {
    /*int index = ui->listWidget->indexFromItem(ui->listWidget->currentItem()).row();
    m_data_list[index].done += 1;
    ui->listWidget->currentItem()->setData(Qt::EditRole, m_data_list[index].ToQString());
    sort(m_data_list.begin(), m_data_list.end());*/
}

void ToDoListWindow::update_list() {
    /*for (size_t i = 0; i < m_data_list.size(); i++) {
        ui->listWidget->item(i)->setData(Qt::EditRole, (m_data_list[i]).ToQString());
    }
    sort(m_data_list.begin(), m_data_list.end());*/
}

void ToDoListWindow::on_actionSettings_triggered()
{
    SettingsDialog* new_dialog = new SettingsDialog(this);
    connect(new_dialog, SIGNAL(pomodoro_duration_changed()), this, SLOT(update_list()));
    new_dialog->setModal(true);
    new_dialog->show();
}
