#include <QtTest>
#include "../../addtotodolist.h"

class Test_AddToToDoList : public QObject
{
    Q_OBJECT

public:
    Test_AddToToDoList();
    ~Test_AddToToDoList();

private slots:
    void initTestCase();
    void cleanupTestCase();
    //void test_case_on_pushButtonCreate_clicked();

};
//#include "../../addtotodolist.h"
//#include "ui_addtotodolist.h"

Test_AddToToDoList::Test_AddToToDoList()
{

}

Test_AddToToDoList::~Test_AddToToDoList()
{

}

void Test_AddToToDoList::initTestCase()
{
    QString name_of_the_task = "Test task";
    qint32 number_of_pomodoros = 50, priority = 3;
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    ToDoList::mode mode = ToDoList::mode::Add;
    AddToToDoList test_dialog(nullptr, &parent_data_list, &parent_list_widget, mode);
    QCOMPARE(1,1);
}

void Test_AddToToDoList::cleanupTestCase()
{

}

/*void Test_AddToToDoList::test_case_on_pushButtonCreate_clicked()
{
    QString name_of_the_task = "Test task";
    qint32 number_of_pomodoros = 50, priority = 3;
    std::vector<ToDoListData> parent_data_list;
    QListWidget parent_list_widget;
    ToDoList::mode mode = ToDoList::mode::Add;
    AddToToDoList test_dialog(nullptr, &parent_data_list, &parent_list_widget, mode);
    /*test_dialog.ui->spinBox->setValue(number_of_pomodoros);
    test_dialog.ui->lineEditNameofTask->setText(name_of_the_task);
    test_dialog.ui->spinBox_priority->setValue(priority);
    test_dialog.on_pushButtonCreate_clicked();
    QTest::mouseClick(test_dialog.ui, Qt::LeftButton);
    QCOMPARE(parent_data_list[0].name, name_of_the_task);
    QCOMPARE(parent_data_list[0].predicted, number_of_pomodoros);
    QCOMPARE(parent_data_list[0].priority, priority);
    QCOMPARE(parent_data_list[0].done, 0);
    QCOMPARE(parent_list_widget.item(0)->data(Qt::EditRole), parent_data_list[0].ToQString());
}*/

QTEST_APPLESS_MAIN(Test_AddToToDoList)

#include "tst_test_addtotodolist.moc"
