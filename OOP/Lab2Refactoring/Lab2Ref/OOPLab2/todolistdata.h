#ifndef TODOLISTDATA_H
#define TODOLISTDATA_H

#include<QString>
#include <QDataStream>
class ToDoListData
{
    //Q_OBJECT
public:
    ToDoListData();
    ToDoListData(qint8 priority, QString name, qint32 done, qint32 predicted);
    ToDoListData(QDataStream& in);
    ToDoListData(const ToDoListData & other)
        : priority(other.priority), name(other.name), done(other.done), predicted(other.predicted) {}
    ToDoListData& operator=(const ToDoListData & other);
public:
    qint8 priority;
    QString name;
    qint32 done;
    qint32 predicted;
    QString ToQString();
    //void read_from_binary(QDataStream in);
    void write_to_binary(QDataStream& out);
    friend bool operator<(const ToDoListData& left, const ToDoListData& right);
    friend bool operator==(const ToDoListData& left, const ToDoListData& right);
private:
    QString time_needed_to_finish();

};
#endif // TODOLISTDATA_H
