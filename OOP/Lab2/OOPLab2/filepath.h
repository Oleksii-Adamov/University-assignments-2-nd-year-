#ifndef FILEPATH_H
#define FILEPATH_H
#include <QString>

QString get_project_path(const QString& file_name);

QString get_project_list_path();

QString get_project_dir();

QString get_user_data_dir();

bool change_to_file_name_without_extension_bin(QString& file_name);

bool remove_path_from_project_file_name(QString& file_name);

#endif // FILEPATH_H
