#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "todolistwindow.h"
#include <QSharedPointer>
#include <QtCore>
#include <vector>
#include <QMessageBox>
#include <QPushButton>
#include <QDebug>
#include "addnewprojectdialog.h"
#include "filepath.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir;
    dir.mkdir(get_project_dir());
    dir.mkdir(get_user_data_dir());
    QFile file(get_project_list_path());
    if (!file.exists()) {
        // recovering data / creating new
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        dir.cd(get_project_dir());
        bool is_today_project_exists = false, is_tomorrow_project_exists = false, is_someday_project_exists = false,
                is_comleted_project_exists = false;
        // recovering data from user projects dir
        foreach(QFileInfo file_info, dir.entryInfoList()) {
            QString file_name = file_info.fileName();
            // if file is .bin
            if (file_name.length() > 4 && file_name.right(3) == "bin") {
                // write into project list
                file_name.remove(file_name.length() - 4, 4);
                out << file_name;
                if (file_name == "Today") is_today_project_exists = true;
                if (file_name == "Tomorrow") is_tomorrow_project_exists = true;
                if (file_name == "Someday") is_someday_project_exists = true;
                if (file_name == "Comleted") is_comleted_project_exists = true;
            }
        }
        if (!is_today_project_exists) out << QString("Today");
        if (!is_tomorrow_project_exists) out << QString("Tomorrow");
        if (!is_someday_project_exists) out << QString("Someday");
        if (!is_comleted_project_exists) out << QString("Comleted");
        //out << QString("Today") << QString("Tomorrow") << QString("Someday") << QString("Comleted");
        file.close();
    }
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    while(!in.atEnd()) {
        QString input;
        in >> input;
        m_project_list.append(input);
    }
    file.close();
    for (qsizetype i = 0; i < m_project_list.size(); i++) {
        add_button(m_project_list[i]);
    }
}

MainWindow::~MainWindow()
{
    // writing to project_list.bin
    QDir dir;
    dir.mkdir(get_user_data_dir());
    QFile file(get_project_list_path());
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    for (qsizetype i = 0; i < m_project_list.size(); i++) {
        out << m_project_list[i];
    }
    file.close();
    delete ui;
}

void MainWindow::add_button(QString name) {
    QPushButton* new_button = new QPushButton(name, this);
    ui->verticalLayout->addWidget(new_button);
    new_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    connect(new_button, SIGNAL(clicked()), this, SLOT(on_projectButton_clicked()));
}

// open todolistwindow
void MainWindow::callToDoList(QString file_name) {
    QSharedPointer<std::vector<ToDoListData>> list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
    QDir dir;
    dir.mkdir(get_project_dir());
    QFile file(file_name);
    if (!file.exists()) {
        file.open(QIODevice::NewOnly);
        file.close();
    }
    else {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        while(!in.atEnd()) {
            list->emplace_back(in);
        }
        file.close();
    }
    ToDoListWindow* new_window  = new ToDoListWindow(file_name, list);
    new_window->show();
}

void MainWindow::on_projectButton_clicked() {
    QPushButton* _sender = (QPushButton*) sender();
    callToDoList(/*"./UserProjects/" + _sender->text() + ".bin"*/get_project_path(_sender->text()));
}

void MainWindow::create_project(QString file_name) {
    // adding to m_project_list
    m_project_list.append(file_name);
    // creating new file in user projects directory
    QFile file(get_project_path(file_name));
    file.open(QIODevice::NewOnly);
    file.close();
    // creating new button
    add_button(file_name);
}

void MainWindow::on_actionNew_triggered()
{
    AddNewProjectDialog* new_dialog  = new AddNewProjectDialog(this);
    connect(new_dialog, SIGNAL(create_project(QString)), this, SLOT(create_project(QString)));
    new_dialog->setModal(true);
    new_dialog->show();
}


void MainWindow::on_actionDelete_triggered()
{

}

