#include "File_Storage.h"

FileStorage::FileStorage() {
    // Constructor
}

FileStorage::~FileStorage() {
    // Destructor
}

void FileStorage::addLine(const std::string &line, int path_idx, int line_num) {
    LineData data;
    data.line_Num = line_num;
    data.path_idx = path_idx;
    data.line_txt = line;
    lines.push_back(data);
}

void FileStorage::addPath(const std::string &path) {
    paths.push_back(path);
}

const FileStorage::LineData &FileStorage::getLine_info(int line_id) const {
    return lines[line_id];
}

const std::string &FileStorage::getPath(int path_idx) const {
    return paths[path_idx];
}