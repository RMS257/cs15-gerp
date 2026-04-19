#ifndef __INDEX_H
#define __INDEX_H

#include <string>
#include "DirNode.h"
#include "FSTree.h"
#include <vector>
#include <set>
#include "File_storage.h"
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