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
#include <QScrollArea>
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QWidget* w = new QWidget(this);
    //w->setLayout(ui->verticalLayout);
    //ui->scrollArea->setWidget(w);
    //ui->scrollArea->setLayout(ui->verticalLayout);
    //QScrollArea* scroll = new QScrollArea(this);
    //scroll->setWidget(ui->centralwidget);
    //scroll->show();
    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable( true );
    ui->verticalLayout->addWidget( scrollArea );
    m_button_container = new QWidget();
    scrollArea->setWidget( m_button_container );
    m_button_layout = new QVBoxLayout(m_button_container);
    QDir dir;
    dir.mkdir(get_project_dir());
    dir.mkdir(get_user_data_dir());
    dir.cd(get_project_dir());
    // creating buttons with standard projects
    add_button("Today");
    add_button("Tomorrow");
    add_button("Someday");
    // creating projects buttons based on user projects dir
    foreach(QFileInfo file_info, dir.entryInfoList()) {
        QString file_name = file_info.fileName();
        // if file is .bin
        if (/*file_name.length() > 4 && file_name.right(3) == "bin"*/change_to_file_name_without_extension_bin(file_name)) {
            // write into project list
            //file_name.remove(file_name.length() - 4, 4);
            if (file_name != "Today" && file_name != "Tomorrow" && file_name != "Someday" && file_name != "Comleted")
                   add_button(file_name);
        }
    }
    add_button("Comleted");
    /*QFile file(get_project_list_path());
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
    }*/
}

MainWindow::~MainWindow()
{
    // writing to project_list.bin
    /*QDir dir;
    dir.mkdir(get_user_data_dir());
    QFile file(get_project_list_path());
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    for (qsizetype i = 0; i < m_project_list.size(); i++) {
        out << m_project_list[i];
    }
    file.close();*/
    delete ui;
}

void MainWindow::add_button(QString name) {
    //QPushButton* new_button = new QPushButton(name, this);
    //ui->verticalLayout->addWidget(new_button);
    QPushButton* new_button = new QPushButton(name, m_button_container);
    m_button_layout->addWidget(new_button);
    //ui->listWidget->addItem((QListWidgetItem*)(new_button));
    new_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    QFont button_font;
    button_font.setPointSize(40);
    new_button->setFont(button_font);
    connect(new_button, SIGNAL(clicked()), this, SLOT(on_projectButton_clicked()));
}

// open todolistwindow
void MainWindow::callToDoList(QString file_name) {
    /*QSharedPointer<std::vector<ToDoListData>> list = QSharedPointer<std::vector<ToDoListData>>(new std::vector<ToDoListData>);
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
    }*/
    ToDoListWindow* new_window  = new ToDoListWindow(file_name/*, list*/, this);
    connect(new_window, SIGNAL(delete_project_button(const QString&)), this, SLOT(delete_project_button(const QString&)));
    connect(new_window, SIGNAL(edit_project_button(const QString&, const QString&)), this, SLOT(edit_project_button(const QString&, const QString&)));
    new_window->setWindowModality(Qt::WindowModal);
    new_window->show();
}

void MainWindow::on_projectButton_clicked() {
    QPushButton* _sender = (QPushButton*) sender();
    callToDoList(get_project_path(_sender->text()));
}

void MainWindow::create_project(const QString& file_name) {
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
    connect(new_dialog, SIGNAL(create_project(const QString&)), this, SLOT(create_project(const QString&)));
    new_dialog->setModal(true);
    new_dialog->show();
}

void MainWindow::delete_project_button(const QString& name) {
    for(qsizetype i = 0; i < m_button_layout->count(); i++){
        QPushButton *button = qobject_cast<QPushButton*>(m_button_layout->itemAt(i)->widget());
        if(button->text() == name){
            button->hide();
            delete button;
            break;
        }
    }
}

void MainWindow::edit_project_button(const QString& old_name, const QString& new_name) {
    for(qsizetype i = 0; i < m_button_layout->count(); i++){
        QPushButton *button = qobject_cast<QPushButton*>(m_button_layout->itemAt(i)->widget());
        if(button->text() == old_name){
            button->setText(new_name);
            break;
        }
    }
}


void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog* new_dialog = new SettingsDialog(this);
    new_dialog->setModal(true);
    new_dialog->show();
}

