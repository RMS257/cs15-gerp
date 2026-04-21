/*
 * File_Storage.cpp
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Implements the FileStorage class, which stores file paths and lines of text
 * for the gerp program. This class provides methods for adding lines and paths,
 * and retrieving line and path information based on line ids and path ids.
 */

#include "File_Storage.h"

/*
 * name: FileStorage (Constructor)
 * purpose: none (nothing to initialize)
 * arguments: none
 * returns: none
 * effects: none
 */
FileStorage::FileStorage() {
    // Constructor
}

/*
 * name: FileStorage (Destructor)
 * purpose: none (nothing to free)
 * arguments: none
 * returns: none
 * effects: none
 */
FileStorage::~FileStorage() {
    // Destructor
}

/*
 * name: ddLine
 * purpose: add a line with it's given data to the storage
 * arguments: the line text, path index, and line number
 * returns: none
 * effects: updates the line storage
 */
void FileStorage::addLine(const std::string &line, int path_idx, int line_num) {
    LineData data;
    data.line_Num = line_num;
    data.path_idx = path_idx;
    data.line_txt = line;
    lines.push_back(data);
}

/*
 * name: addPath
 * purpose: adds a path to the storage
 * arguments: the path to add
 * returns: none
 * effects: updates the path storage
 */
void FileStorage::addPath(const std::string &path) {
    paths.push_back(path);
}

/*
 * name: getLine_info
 * purpose: returns the line data associated woth the line id
 * arguments: line id to search
 * returns: the line data associated with the line id
 * effects: none
 */
const FileStorage::LineData &FileStorage::getLine_info(int line_id) const {
    return lines[line_id];
}

/*
 * name: getPath
 * purpose: returns the path associated with the path index
 * arguments: path index to search
 * returns: the path associated with the path index
 * effects: none
 */
const std::string &FileStorage::getPath(int path_idx) const {
    return paths[path_idx];
}