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
    void AddToToDoListTestCase();
    void EditToDoListTestCase();
    void SettingChangeTestCase();
    void AddNewProjectTestCase();
    void EditProjectTestCase();
private:
    QApplication* a;
    void delete_project_manually_if_exists(MainWindow& main_window, const QString& project_name);
    bool project_button_exists(MainWindow& main_window, const QString& project_name);
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

void UnitTests::AddToToDoListTestCase()
{
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    parent_list_widget.setSortingEnabled(true);
    ToDoList::mode mode = ToDoList::mode::Add;
    std::vector<QString> name_of_the_task {"Test task1", "Test task2", "Test task3"};
    std::vector<qint32> number_of_pomodoros {50, 29, 23};
    std::vector<qint32> priority {3, 2, 7};

    // 0 - to empty list, 1,2 - to non-empty list
    for (int i = 0; i < 3; i++) {
        AddToToDoList test_dialog(nullptr, &parent_data_list, &parent_list_widget, mode);
        test_dialog.ui->lineEditNameofTask->setText(name_of_the_task[i]);
        test_dialog.ui->spinBox->setValue(number_of_pomodoros[i]);
        test_dialog.ui->spinBox_priority->setValue(priority[i]);
        test_dialog.on_pushButtonCreate_clicked();
        qint32 index = 0;
        if (i > 1) index = 2;
        QCOMPARE(parent_data_list[index].name, name_of_the_task[i]);
        QCOMPARE(parent_data_list[index].predicted, number_of_pomodoros[i]);
        QCOMPARE(parent_data_list[index].priority, priority[i]);
        QCOMPARE(parent_data_list[index].done, 0);
        QCOMPARE(parent_list_widget.item(index)->data(Qt::EditRole), parent_data_list[index].ToQString());
    }
}

void UnitTests::EditToDoListTestCase()
{
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    parent_list_widget.setSortingEnabled(true);
    std::vector<QString> name_of_the_task {"Test task1", "Test task2"};
    std::vector<qint32> number_of_pomodoros {50, 29};
    std::vector<qint32> priority {2, 3};

    // insert
    for (int i = 0; i < 2; i++) {
        AddToToDoList test_dialog(nullptr, &parent_data_list, &parent_list_widget, ToDoList::mode::Add);
        test_dialog.ui->lineEditNameofTask->setText(name_of_the_task[i]);
        test_dialog.ui->spinBox->setValue(number_of_pomodoros[i]);
        test_dialog.ui->spinBox_priority->setValue(priority[i]);
        test_dialog.on_pushButtonCreate_clicked();
    }

    std::vector<QString> new_name_of_the_task {"Test task1new", "Test task2new"};
    std::vector<qint32> new_number_of_pomodoros {12, 32};
    std::vector<qint32> new_priority {1, 0};

    // edit test
    for (int i = 0; i < 2; i++) {
        parent_list_widget.setCurrentRow(i);
        AddToToDoList test_dialog(nullptr, &parent_data_list, &parent_list_widget, ToDoList::mode::Edit);
        test_dialog.ui->lineEditNameofTask->setText(new_name_of_the_task[i]);
        test_dialog.ui->spinBox->setValue(new_number_of_pomodoros[i]);
        test_dialog.ui->spinBox_priority->setValue(new_priority[i]);
        test_dialog.on_pushButtonCreate_clicked();
        qint32 index = 0;
        QCOMPARE(parent_data_list[index].name, new_name_of_the_task[i]);
        QCOMPARE(parent_data_list[index].predicted, new_number_of_pomodoros[i]);
        QCOMPARE(parent_data_list[index].priority, new_priority[i]);
        QCOMPARE(parent_data_list[index].done, 0);
        QCOMPARE(parent_list_widget.item(index)->data(Qt::EditRole), parent_data_list[index].ToQString());
    }
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

QTEST_APPLESS_MAIN(UnitTests)

#include "unittests.moc"
