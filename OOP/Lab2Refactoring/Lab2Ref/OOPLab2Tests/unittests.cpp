#include <QtTest>
#include <QtWidgets>
#include "../OOPLab2/addtotodolist.h"
#include "ui_addtotodolist.h"
#include "../OOPLab2/filepath.h"
#include "../OOPLab2/settingsdialog.h"
#include "ui_settingsdialog.h"
#include "../OOPLab2/mainwindow.h"
#include "../OOPLab2/todolistwindow.h"
#include "ui_todolistwindow.h"

class UnitTests : public QObject
{
    Q_OBJECT

public:
    UnitTests();
    ~UnitTests();

private slots:
    void initTestCase();
    void cleanupTestCase();
    // Unit testing of Use Cases
    void AddTaskTestCase();
    void EditTaskTestCase();
    void DeleteTaskTestCase();
    void SettingChangeTestCase();
    void AddNewProjectTestCase();
    void EditProjectTestCase();
    void DeleteProjectTestCase();
private:
    QApplication* a;
    void delete_project_manually_if_exists(MainWindow& main_window, const QString& project_name);
    bool project_button_exists(MainWindow& main_window, const QString& project_name);
    void add_or_edit_task(std::vector<ToDoListData>& parent_data_list, QListWidget& parent_list_widget, ToDoList::mode mode,
                  const QString& name_of_the_task, int number_of_pomodoros, int priority);
};

UnitTests::UnitTests()
{
    qRegisterMetaType<ToDoListData>();
    init_paths();
    int argc = 0;
    char **argv = NULL;
    a = new QApplication(argc, argv);
}

UnitTests::~UnitTests()
{
    delete a;
}

void UnitTests::initTestCase()
{

}

void UnitTests::cleanupTestCase()
{

}

void UnitTests::add_or_edit_task(std::vector<ToDoListData>& parent_data_list, QListWidget& parent_list_widget, ToDoList::mode mode,
                         const QString& name_of_the_task, int number_of_pomodoros, int priority)
{
    AddToToDoList add_task_dialog(nullptr, &parent_data_list, &parent_list_widget, mode);
    add_task_dialog.ui->lineEditNameofTask->setText(name_of_the_task);
    add_task_dialog.ui->spinBox->setValue(number_of_pomodoros);
    add_task_dialog.ui->spinBox_priority->setValue(priority);
    add_task_dialog.on_pushButtonCreate_clicked();
}

void UnitTests::AddTaskTestCase()
{
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    parent_list_widget.setSortingEnabled(true);
    std::vector<QString> name_of_the_task {"Test task1", "Test task2", "Test task3"};
    std::vector<qint32> number_of_pomodoros {50, 29, 23};
    std::vector<qint32> priority {3, 2, 7};

    // 0 - to empty list, 1,2 - to non-empty list
    for (int i = 0; i < 3; i++) {
        add_or_edit_task(parent_data_list, parent_list_widget, ToDoList::mode::Add,
                 name_of_the_task[i], number_of_pomodoros[i], priority[i]);
        qint32 index = 0;
        if (i > 1) index = 2;
        QCOMPARE(parent_data_list[index], ToDoListData(priority[i], name_of_the_task[i], 0, number_of_pomodoros[i]));
        QCOMPARE(parent_list_widget.item(index)->data(Qt::EditRole), parent_data_list[index].ToQString());
    }
}

void UnitTests::EditTaskTestCase()
{
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    parent_list_widget.setSortingEnabled(true);
    std::vector<QString> name_of_the_task {"Test task1", "Test task2"};
    std::vector<qint32> number_of_pomodoros {50, 29};
    std::vector<qint32> priority {2, 3};

    // insert
    for (int i = 0; i < 2; i++) {
        add_or_edit_task(parent_data_list, parent_list_widget, ToDoList::mode::Add,
                         name_of_the_task[i], number_of_pomodoros[i], priority[i]);
    }

    std::vector<QString> new_name_of_the_task {"Test task1new", "Test task2new"};
    std::vector<qint32> new_number_of_pomodoros {12, 32};
    std::vector<qint32> new_priority {1, 0};

    // edit test
    for (int i = 0; i < 2; i++) {
        parent_list_widget.setCurrentRow(i);
        add_or_edit_task(parent_data_list, parent_list_widget, ToDoList::mode::Edit,
                         new_name_of_the_task[i], new_number_of_pomodoros[i], new_priority[i]);
        qint32 index = 0;
        QCOMPARE(parent_data_list[index], ToDoListData(new_priority[i], new_name_of_the_task[i], 0,
                                                       new_number_of_pomodoros[i]));
        QCOMPARE(parent_list_widget.item(index)->data(Qt::EditRole), parent_data_list[index].ToQString());
    }
}

void UnitTests::DeleteTaskTestCase()
{

}

void UnitTests::SettingChangeTestCase()
{
    int new_pomodoro = 2, new_break = 7;
    // test twice, also test that signal pomodoro_duration_changed() emited
    for (int i = 0; i < 2; i++) {
        SettingsDialog settings;
        QSignalSpy spy(&settings, SIGNAL(pomodoro_duration_changed()));
        settings.ui->spinBox_pomodoro->setValue(new_pomodoro);
        settings.ui->spinBox_break->setValue(new_break);
        settings.on_pushButton_apply_clicked();
        int pomodoro_settings, break_settings;
        read_settings(pomodoro_settings, break_settings);
        QCOMPARE(pomodoro_settings, new_pomodoro);
        QCOMPARE(break_settings, new_break);
        QCOMPARE(spy.count(), 1);
        new_pomodoro = 51;
        new_break = 1;
    }
}

void UnitTests::delete_project_manually_if_exists(MainWindow& main_window, const QString& project_name)
{
    // from file system
    QFile file(get_project_path(project_name));
    if (file.exists()) {
        file.remove();
    }
    // delete button
    for(qsizetype i = 0; i < main_window.m_button_layout->count(); i++){
        QPushButton *button = qobject_cast<QPushButton*>(main_window.m_button_layout->itemAt(i)->widget());
        if(button->text() == project_name){
            button->hide();
            delete button;
            break;
        }
    }
}

bool UnitTests::project_button_exists(MainWindow& main_window, const QString& project_name)
{
    bool return_value = false;
    for(qsizetype i = 0; i < main_window.m_button_layout->count(); i++){
        QPushButton *button = qobject_cast<QPushButton*>(main_window.m_button_layout->itemAt(i)->widget());
        if(button->text() == project_name){
            return_value = true;
            break;
        }
    }
    return return_value;
}

void UnitTests::AddNewProjectTestCase()
{
    MainWindow main_window;
    QString project_name = "New project";
    // deleting project manually if existed
    delete_project_manually_if_exists(main_window, project_name);
    // test
    main_window.create_project(project_name);
    // checking file
    QFile file(get_project_path(project_name));
    QCOMPARE(file.exists(), true);
    // checking button
    QCOMPARE(project_button_exists(main_window, project_name), true);

    delete_project_manually_if_exists(main_window, project_name);
}

void UnitTests::EditProjectTestCase()
{
    MainWindow main_window;
    QString old_project_name = "Old project", new_project_name = "New project";
    // deleting projects manually if existed
    delete_project_manually_if_exists(main_window, old_project_name);
    delete_project_manually_if_exists(main_window, new_project_name);
    // creating project
    main_window.create_project(old_project_name);
    // testing edit
    ToDoListWindow to_do_list_window(get_project_path(old_project_name), &main_window);
    connect(&to_do_list_window, SIGNAL(edit_project_button(const QString&, const QString&)), &main_window, SLOT(edit_project_button(const QString&, const QString&)));
    to_do_list_window.edit_project(new_project_name);
    // checking files
    QFile old_file(get_project_path(old_project_name));
    QCOMPARE(old_file.exists(), false);
    QFile new_file(get_project_path(new_project_name));
    QCOMPARE(new_file.exists(), true);
    //checking label
    QCOMPARE(to_do_list_window.ui->label->text(), new_project_name);
    // checking buttons
    QCOMPARE(project_button_exists(main_window, old_project_name), false);
    QCOMPARE(project_button_exists(main_window, new_project_name), true);

    delete_project_manually_if_exists(main_window, new_project_name);
}

void UnitTests::DeleteProjectTestCase()
{
    MainWindow main_window;
    QString project_name = "New project";
    // deleting project manually if existed
    delete_project_manually_if_exists(main_window, project_name);
    // creating project
    main_window.create_project(project_name);
    // testing deletion
    ToDoListWindow to_do_list_window(get_project_path(project_name), &main_window);
    connect(&to_do_list_window, SIGNAL(delete_project_button(const QString&)), &main_window, SLOT(delete_project_button(const QString&)));
    to_do_list_window.on_actionDelete_this_project_triggered();
    // checking file
    QFile file(get_project_path(project_name));
    QCOMPARE(file.exists(), false);
    // checking button
    QCOMPARE(project_button_exists(main_window, project_name), false);
}

QTEST_APPLESS_MAIN(UnitTests)

#include "unittests.moc"
