#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    // open today_window
}



void MainWindow::on_pushButton_tomorrow_clicked()
{

}



void MainWindow::on_pushButton_all_tasks_clicked()
{

}

