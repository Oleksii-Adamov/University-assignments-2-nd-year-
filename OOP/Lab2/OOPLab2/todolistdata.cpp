#include "todolistdata.h"
#include "filepath.h"
QString ToDoListData::ToQString() {
    return "Priority " + QString::number(priority) + ": " + name + " " + QString::number(done) + "/" + QString::number(predicted) + " pomodoro" + time_needed_to_finish();
}

ToDoListData::ToDoListData() {}

ToDoListData::ToDoListData(qint8 priority, QString name, qint32 done, qint32 predicted)
    : priority(priority), name(name), done(done), predicted(predicted)
{

}
ToDoListData::ToDoListData(QDataStream& in) {
    in >> priority >> name >> done >> predicted;
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
    priority = other.priority; name = other.name; done = other.done; predicted = other.predicted;
    return *this;
}

void ToDoListData::write_to_binary(QDataStream& out) {
    out << priority << name << done << predicted;
}

QString ToDoListData::time_needed_to_finish() {
    if (done > predicted) return "Prediction is wrong!";
    int pomodoro_duration_in_minutes, break_duration_in_minutes;
    read_settings(pomodoro_duration_in_minutes, break_duration_in_minutes);
    int minutes = (predicted - done) * pomodoro_duration_in_minutes;
    int hours = minutes / 60;
    minutes = minutes % 60;
    return " " + QString::number(hours) + "h " + QString::number(minutes) + "m";
}

bool operator<(const ToDoListData& left, const ToDoListData& right) {
    if (left.priority == right.priority) {
        if (left.name == right.name) {
            if (left.done == right.done) {
                return left.predicted < right.predicted;
            }
            return left.done < right.done;
        }
        else {
            return left.name < right.name;
        }
    }
    else {
        return left.priority < right.priority;
    }
}
