/*
 * File_storage.h
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Defines the FileStorage class, which stores file paths and lines of text
 * for the gerp program. This class provides methods for adding lines and paths,
 * and retrieving line and path information based on line ids and path ids.
 */

#ifndef __FILE_STORAGE_H
#define __FILE_STORAGE_H



#include <string>
#include <vector>
class FileStorage
{
public:
    struct LineData
    {
        int line_Num;
        int path_idx;

        std::string line_txt;
    };

    FileStorage();
    ~FileStorage();

    void addLine(const std::string &line, int path_idx, int line_num);
    void addPath(const std::string &path);

    const LineData &getLine_info(int line_id) const;
    const std::string &getPath(int path_idx) const;
    


private:


    std::vector<std::string> paths;
    std::vector<LineData> lines;
};

#endif