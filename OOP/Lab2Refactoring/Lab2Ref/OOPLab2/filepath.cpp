#include "filepath.h"
#include <QFile>
// remove
#include <QDebug>
#include <QDir>
//

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
    //return "C:/Program Files/PomodoroTimeManagmentApp/UserData/settings.bin";
}

void read_settings(int& pomodoro_duration_in_minutes, int& break_duration_in_minutes) {
    QFile file(get_settings_path());
    if(file.exists()) {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        in >> pomodoro_duration_in_minutes >> break_duration_in_minutes;
    }
    else { // setup default settings
        pomodoro_duration_in_minutes = 20;
        break_duration_in_minutes = 5;
        file.open(QIODevice::NewOnly);
        QDataStream out(&file);
        out << pomodoro_duration_in_minutes  << break_duration_in_minutes;
    }
    file.close();
}

void init_paths() {
    QDir dir;
    dir.mkdir(get_project_dir());
    dir.mkdir(get_user_data_dir());
}

std::vector<ToDoListData> load_to_do_list_from_file(const QString& file_name)
{
    std::vector<ToDoListData> result;
    QDir dir;
    dir.mkdir(get_project_dir());
    QFile file(file_name);
    if (!file.exists()) {
        file.open(QIODevice::NewOnly);
        file.close();
    }
    else {
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);
        while(!in.atEnd()) {
            result.emplace_back(in);
        }
        file.close();
    }
    return result;
}

void write_to_do_list_to_file(std::vector<ToDoListData>& to_do_list, const QString& file_name)
{
    QFile file(file_name);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    for (std::size_t i = 0; i < to_do_list.size(); i++) {
        to_do_list[i].write_to_binary(out);
    }
}

void delete_file(const QString& file_name)
{
    QFile file(file_name);
    file.remove();
}

void rename_file(const QString& old_file_name, const QString& new_file_name)
{
    QFile file(old_file_name);

    if (file.exists()) {
        file.rename(new_file_name);
    }
    else {
        file.setFileName(new_file_name);
        file.open(QFile::NewOnly);
        file.close();
    }
}

std::vector<QString> get_project_names()
{
    std::vector<QString> res;
    QDir dir;
    dir.cd(get_project_dir());
    foreach(QFileInfo file_info, dir.entryInfoList()) {
        QString file_name = file_info.fileName();
        // if file is .bin
        if (change_to_file_name_without_extension_bin(file_name)) {
            res.push_back(file_name);
        }
    }
    return res;
}
