/*!
\file
\brief This files(.h and .cpp) contain function responsible for file managment (reading, writing) and operations with strings (related to files)
*/
#ifndef FILEPATH_H
#define FILEPATH_H
#include <QString>
#include "todolistdata.h"

void init_paths();

QString get_project_path(const QString& file_name);

QString get_project_list_path();

QString get_project_dir();

QString get_user_data_dir();

/// eg. Today.bin -> Today
bool change_to_file_name_without_extension_bin(QString& file_name);

/// eg. ./project./task.bin -> task.bin
bool remove_path_from_project_file_name(QString& file_name);

QString get_settings_path();

void read_settings(int& pomodoro_duration_in_minutes, int& break_duration_in_minutes);

/// loading tasks from file
std::vector<ToDoListData> load_to_do_list_from_file(const QString& file_name);

/// writing tasks to file
void write_to_do_list_to_file(std::vector<ToDoListData>& to_do_list, const QString& file_name);

void delete_file(const QString& file_name);

void rename_file(const QString& old_file_name, const QString& new_file_name);

std::vector<QString> get_project_names();

/// write task data to file of "Completed" project
void task_to_completed(const ToDoListData& data);

#endif // FILEPATH_H
