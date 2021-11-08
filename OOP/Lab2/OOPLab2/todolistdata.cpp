#include "todolistdata.h"
#include "filepath.h"

QString ToDoListData::ToQString() {
    return name + " " + QString::number(done) + "/" + QString::number(predicted) + " pomodoro" + time_needed_to_finish();
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

QString ToDoListData::time_needed_to_finish() {
    if (done > predicted) return "Prediction is wrong!";
    int pomodoro_duration_in_minutes, break_duration_in_minutes;
    read_settings(pomodoro_duration_in_minutes, break_duration_in_minutes);
    int minutes = (predicted - done) * pomodoro_duration_in_minutes;
    int hours = minutes / 60;
    minutes = minutes % 60;
    return " " + QString::number(hours) + "h " + QString::number(minutes) + "m";
}
