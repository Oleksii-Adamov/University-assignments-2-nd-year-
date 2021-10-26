#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "todolistwindow.h"
#include <QSharedPointer>
#include <QtCore>
#include "todolistdata.h"
#include <vector>
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


void MainWindow::on_pushButton_today_clicked()
{
    // open todolistwindow with today list
    QSharedPointer<std::vector<ToDoListData>> list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
    list->emplace_back("OOP", 5, 8);
    list->emplace_back("DB", 7, 10);
    ToDoListWindow* new_window  = new ToDoListWindow(this);
    new_window->setList(list);
    new_window->show();
}



void MainWindow::on_pushButton_tomorrow_clicked()
{

}



void MainWindow::on_pushButton_all_tasks_clicked()
{

}

