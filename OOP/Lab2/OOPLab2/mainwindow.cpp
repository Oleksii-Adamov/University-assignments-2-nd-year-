#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "todolistwindow.h"
#include <QSharedPointer>
#include <QtCore>
#include <vector>
#include <QMessageBox>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList project_list;
    project_list.append("Today");
    project_list.append("Tomorrow");
    project_list.append("Someday");
    project_list.append("Comleted");
    for (qsizetype i = 0; i < project_list.size(); i++) {
        QPushButton* new_button = new QPushButton(project_list[i], this);
        ui->verticalLayout->addWidget(new_button);
        new_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
        connect(new_button, SIGNAL(clicked()), this, SLOT(on_projectButton_clicked()));
    }
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

void MainWindow::on_projectButton_clicked() {
    QPushButton* _sender = (QPushButton*) sender();
    callToDoList(_sender->text() + ".bin");
}


// open todolistwindow with today list
/*void MainWindow::on_pushButton_today_clicked()
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
}*/

