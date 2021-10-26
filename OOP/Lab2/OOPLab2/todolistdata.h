#ifndef TODOLISTDATA_H
#define TODOLISTDATA_H

//#include <QObject>
//#include<QVariant>
//#include <QMetaType>
#include<QString>
class ToDoListData //:public /*QObject*/QVariant
{
    //Q_OBJECT
public:
    //explicit ToDoListData(/*QObject*/QVariant *parent = nullptr);
    ToDoListData(QString name, int done, int predicted);
    explicit ToDoListData(const ToDoListData & other)
       : name(other.name), done(other.done), predicted(other.predicted) {};
    //ToDoListData(const ToDoListData & other);
    ToDoListData& operator=(const ToDoListData & other);
    /*ToDoListData& operator=(const ToDoListData &other) {
        if (this == &other) {
            return *this;
        }
        name = other.name; done = other.done; predicted = other.predicted;
        return *this;
    }*/
    QString name;
    int done;
    int predicted;
    QString ToQString();
signals:

};
//Q_DECLARE_METATYPE(ToDoListData);
#endif // TODOLISTDATA_H
