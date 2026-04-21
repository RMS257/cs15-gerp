/*
 * index.h
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Defines the index class, which implements a hash table to store words and 
 * their associated line ids for the gerp program. This class provides methods 
 * for adding words and retrieving line ids based on query words.
 */

#ifndef __INDEX_H
#define __INDEX_H

#include <string>
#include "DirNode.h"
#include "FSTree.h"
#include <vector>
#include <set>
#include "File_Storage.h"
#include <functional>

class index
{
public:
    index();
    ~index();

    void addWord(const std::string &word, int line_id);

    const std::vector<int> &getLines(const std::string &word) const;


private:
    void resize();
    size_t get_hashval(const std::string &word) const;

    // Variables and structs
    struct WordNode 
    {
        std::string word;
        std::vector<int> line_id;
    };

    std::vector<std::vector<WordNode>> table;
    int num_words;
    int table_size;
};


#endif