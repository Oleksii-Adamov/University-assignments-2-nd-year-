#ifndef TODOLISTDATA_H
#define TODOLISTDATA_H

//#include <QObject>
//#include<QVariant>
//#include <QMetaType>
#include<QString>
#include <QDataStream>
class ToDoListData //:public /*QObject*/QVariant
{
    //Q_OBJECT
public:
    //explicit ToDoListData(/*QObject*/QVariant *parent = nullptr);
    ToDoListData();
    ToDoListData(qint8 priority, QString name, qint32 done, qint32 predicted);
    ToDoListData(QDataStream& in);
    ToDoListData(const ToDoListData & other)
        : priority(other.priority), name(other.name), done(other.done), predicted(other.predicted) {}
    /*ToDoListData(ToDoListData&& other) noexcept
        : priority(other.priority), name(other.name), done(other.done), predicted(other.predicted) {}*/
    /*explicit ToDoListData(const ToDoListData & other)
       : done(other.done), predicted(other.predicted)
    {
        for (int i = 0; i < name_size; i++) {
            name[i] = other.name[i];
        }
    };*/
    //ToDoListData(const ToDoListData & other);
    ToDoListData& operator=(const ToDoListData & other);
    /*ToDoListData& operator=(const ToDoListData &other) {
        if (this == &other) {
            return *this;
        }
        name = other.name; done = other.done; predicted = other.predicted;
        return *this;
    }*/
    //char name[60];
public:
    qint8 priority;
    QString name;
    qint32 done;
    qint32 predicted;
    QString ToQString();
    /*void read_from_binary(FILE* fptr);
    void write_to_binary(FILE* fptr);*/
    void read_from_binary(QDataStream in);
    void write_to_binary(QDataStream& out);
    friend bool operator<(const ToDoListData& left, const ToDoListData& right);
private:
    QString time_needed_to_finish();

};
//Q_DECLARE_METATYPE(ToDoListData);
#endif // TODOLISTDATA_H
