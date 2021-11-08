#include "filepath.h"
#include <QFile>
QString get_project_path(const QString& file_name) {
    return "./UserProjects/" + file_name + ".bin";
}

QString get_project_list_path() {
    return "./UserData/project_list.bin";
}

QString get_project_dir() {
    return "./UserProjects";
}

QString get_user_data_dir() {
    return "./UserData";
}

bool change_to_file_name_without_extension_bin(QString& file_name) {
    if (file_name.length() > 4 && file_name.right(3) == "bin") {
        file_name.remove(file_name.length() - 4, 4);
        return true;
    }
    return false;
}

bool remove_path_from_project_file_name(QString& file_name) {
    if (file_name.length() > 15 && file_name.left(15) == "./UserProjects/") {
        file_name.remove(0, 15);
        return true;
    }
    return false;
}

QString get_settings_path() {
    return "./UserData/settings.bin";
}

void read_settings(int& pomodoro_duration_in_minutes, int& break_duration_in_minutes) {
    QFile file(get_settings_path());
    if(file.exists()) {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        in >> pomodoro_duration_in_minutes >> break_duration_in_minutes;
        file.close();
    }
    else { // setup default settings
        pomodoro_duration_in_minutes = 20;
        break_duration_in_minutes = 5;
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);
        out << pomodoro_duration_in_minutes  << break_duration_in_minutes;
    }
}
