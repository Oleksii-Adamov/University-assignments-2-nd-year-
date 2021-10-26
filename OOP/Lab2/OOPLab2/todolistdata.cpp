#include "todolistdata.h"

QString ToDoListData::ToQString() {
    QString ret = name;
    ret += " " + QString::number(done) + "/" + QString::number(predicted) + " pomodoro";
    return ret;
}

ToDoListData::ToDoListData() {}

ToDoListData::ToDoListData(QString name, qint32 done, qint32 predicted)
    : name(name), done(done), predicted(predicted)
{

}
ToDoListData::ToDoListData(QDataStream& in) {
    in >> name >> done >> predicted;
}
/*ToDoListData::ToDoListData(QString q_name, int done, int predicted)
    : done(done), predicted(predicted)
{
    for(int i = 0; i < name_size; i++) {
        q_name[i] = name[i];
    }
}*/
/*ToDoListData::ToDoListData(const ToDoListData & other) {
    name = other.name;
    done = other.done;
    predicted = other.predicted;
}*/
/*ToDoListData::ToDoListData(const ToDoListData & other)
        : name(other.name), done(other.done), predicted(other.predicted) {}*/
/*noexcept ToDoListData::ToDoListData(const ToDoListData & other) {
    name = other.name;
    done = other.done;
    predicted = other.predicted;
}*/
ToDoListData& ToDoListData::operator=(const ToDoListData &other) {
    if (this == &other) {
        return *this;
    }
    name = other.name; done = other.done; predicted = other.predicted;
    return *this;
}

void ToDoListData::write_to_binary(QDataStream& out) {
    out << name << done << predicted;
}
//ToDoListData ToDoListData::&operator=(const ToDoListData &other)
