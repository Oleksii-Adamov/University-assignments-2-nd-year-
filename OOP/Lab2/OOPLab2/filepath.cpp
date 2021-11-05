#include "filepath.h"

QString get_project_path(QString file_name) {
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
