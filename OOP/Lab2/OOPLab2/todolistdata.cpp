#include "todolistdata.h"

QString ToDoListData::ToQString() {
    QString ret = name;
    ret += " " + QString::number(done) + "/" + QString::number(predicted) + "pomodoro";
    return ret;
}
ToDoListData::ToDoListData(QString name, int done, int predicted)
    : name(name), done(done), predicted(predicted)
{

}
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
//ToDoListData ToDoListData::&operator=(const ToDoListData &other)
