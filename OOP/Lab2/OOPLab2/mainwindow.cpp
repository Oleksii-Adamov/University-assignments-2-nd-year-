#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "todolistwindow.h"
#include <QSharedPointer>
#include <QtCore>
#include <vector>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->listWidget->addItem("Today");
   // ui->listWidget->addItem("Tomorrow");
    //ui->listWidget->addItem("All");
   // connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(onListItemDoubleClicked(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*void MainWindow::onListItemDoubleClicked(QListWidgetItem* item) {
    //item->setBackground(Qt::yellow);
}*/
// open todolistwindow
void MainWindow::callToDoList(QString file_name) {
    QSharedPointer<std::vector<ToDoListData>> list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
    QFile file(file_name);
    if (!file.exists()) {
        file.open(QIODevice::NewOnly);
        file.close();
    }
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    while(!in.atEnd()) {
        list->emplace_back(in);
    }
    file.close();
    ToDoListWindow* new_window  = new ToDoListWindow(/*this,*/ file_name, list);
    new_window->show();
}
// open todolistwindow with today list
void MainWindow::on_pushButton_today_clicked()
{
    callToDoList("Today.bin");
}

void MainWindow::on_pushButton_tomorrow_clicked()
{
    callToDoList("Tomorrow.bin");
}

void MainWindow::on_pushButton_someday_clicked()
{
    callToDoList("Someday.bin");
}

