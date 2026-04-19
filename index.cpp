#include "index.h"
#include <iostream>



index::index()
{
    table_size = 100;
    num_words = 0;
    table.resize(table_size);
}


index::~index(){
    // Nothing to free
}


void index::addWord(const std::string &word, int line_id)
{
    size_t hashval = get_hashval(word);
    std::vector<WordNode> &chain = table[hashval];

    for (WordNode &node : chain) {
        if (node.word == word) {
            node.line_id.push_back(line_id);
            return;
        }
    }

    WordNode new_node;
    new_node.word = word;
    new_node.line_id.push_back(line_id);
    chain.push_back(new_node);
    num_words++;

    // Only resize when the load factor becomes high (e.g. > 0.75)
    if (num_words > table_size * 0.75) {
        resize();
    }
}


const std::vector<int> &index::getLines(const std::string &word) const
{
    size_t hashval = get_hashval(word);
    const std::vector<WordNode> &chain = table[hashval];

    for (const WordNode &node : chain) {
        if (node.word == word) {
            return node.line_id;
        }
    }

    static const std::vector<int> empty;
    return empty;
}


void index::resize()
{
    table_size *= 2;
    std::vector<std::vector<WordNode>> new_table(table_size);

    for (const std::vector<WordNode> &chain : table) {
        for (const WordNode &node : chain) {
            size_t hashval = get_hashval(node.word);
            new_table[hashval].push_back(node);
        }
    }

    table = std::move(new_table);
}

size_t index::get_hashval(const std::string &word) const
{
    std::hash<std::string> hasher;
    return hasher(word) % table_size;
}