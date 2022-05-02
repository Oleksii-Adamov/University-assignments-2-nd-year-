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
    auto * scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable( true );
    ui->verticalLayout->addWidget( scrollArea );
    m_button_container = new QWidget();
    scrollArea->setWidget( m_button_container );
    m_button_layout = new QVBoxLayout(m_button_container);

    init_paths();

    // creating buttons with standard projects
    add_button("Today");
    add_button("Tomorrow");
    add_button("Someday");
    // creating projects buttons
    std::vector<QString> button_names = get_project_names();
    for (std::size_t i = 0; i < button_names.size(); i++) {
        if (button_names[i] != "Today" && button_names[i] != "Tomorrow" && button_names[i] != "Someday" &&
                button_names[i] != "Comleted") {
               add_button(button_names[i]);
        }
    }
    add_button("Comleted");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::add_button(QString name) {
    QPushButton* new_button = new QPushButton(name, m_button_container);
    m_button_layout->addWidget(new_button);
    new_button->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    QFont button_font;
    button_font.setPointSize(40);
    new_button->setFont(button_font);
    connect(new_button, SIGNAL(clicked()), this, SLOT(on_projectButton_clicked()));
}

// open todolistwindow
void MainWindow::callToDoList(QString file_name) {
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

    create_file(get_project_path(file_name));

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

