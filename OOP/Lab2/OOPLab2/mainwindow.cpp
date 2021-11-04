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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir dir;
    QFile file("./UserData/project_list.bin");
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out << QString("Today") << QString("Tomorrow") << QString("Someday") << QString("Comleted");
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
        QPushButton* new_button = new QPushButton(m_project_list[i], this);
        ui->verticalLayout->addWidget(new_button);
        new_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        connect(new_button, SIGNAL(clicked()), this, SLOT(on_projectButton_clicked()));
    }
}

MainWindow::~MainWindow()
{
    // writing to project_list.bin
    QFile file("./UserData/project_list.bin");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    for (qsizetype i = 0; i < m_project_list.size(); i++) {
        out << m_project_list[i];
    }
    file.close();
    delete ui;
}

// open todolistwindow
void MainWindow::callToDoList(QString file_name) {
    QSharedPointer<std::vector<ToDoListData>> list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
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
    callToDoList("./UserProjects/" + _sender->text() + ".bin");
}



void MainWindow::on_actionNew_triggered()
{
    AddNewProjectDialog* new_dialog  = new AddNewProjectDialog(this);
    new_dialog->setModal(true);
    new_dialog->show();
}


void MainWindow::on_actionDelete_triggered()
{

}

