#include <QtTest>
#include <QtWidgets>
#include "../OOPLab2/addtotodolist.h"
#include "ui_addtotodolist.h"
#include "../OOPLab2/filepath.h"

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

};

UnitTests::UnitTests()
{
    qRegisterMetaType<ToDoListData>();
    init_paths();
}

UnitTests::~UnitTests()
{

}

void UnitTests::initTestCase()
{

}

void UnitTests::cleanupTestCase()
{

}

void UnitTests::AddToToDoListTestCase()
{
    int argc = 0;
    char **argv = NULL;
    QApplication a(argc, argv);

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
    int argc = 0;
    char **argv = NULL;
    QApplication a(argc, argv);

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

QTEST_APPLESS_MAIN(UnitTests)

#include "unittests.moc"
