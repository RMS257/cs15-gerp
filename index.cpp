/*
 * index.cpp
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Implements the index class, which implements a hash table to store words and 
 * their associated line ids for the gerp program. This class provides methods
 * for adding words and retrieving line ids based on query words.
 */

#include "index.h"
#include <iostream>

/*
 * name: index (Constructor)
 * purpose: initialize the index with an initial table size and zero words
 * arguments: none
 * returns: none
 * effects: initializes the hash table and variables
 */
index::index()
{
    table_size = 100;
    num_words = 0;
    table.resize(table_size);
}

/*
 * name: index (Destructor)
 * purpose: none (nothing to free)
 * arguments: none
 * returns: none
 * effects: none
 */
index::~index(){
    // Nothing to free
}

/*
 * name: addWord
 * purpose: adds or updates a word in the index with the given line id, 
 *          and resizes the table if the load factor becomes too high
 * arguments: the word to add and the line id where it appears
 * returns: none
 * effects: modifies the index by adding the word and line id, and resizes if
 *          needed
 */
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

/*
 * name: getLines
 * purpose: retrieves the line ids asociated with the word, or empty vector if 
 *          the word isn't present
 * arguments: word to look up
 * returns: vector of line ids where the word appears
 * effects: none
 */
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

/*
 * name: resize
 * purpose: doubles the table size and rehashes all present words
 * arguments: none
 * returns: none
 * effects: modifies the index by resizing the hash table and rehashing all 
 *          words
 */
void index::resize()
{
    // Double the table size
    table_size *= 2;
    std::vector<std::vector<WordNode>> new_table(table_size);

    // Rehash all the existing words into the new table
    for (const std::vector<WordNode> &chain : table) {
        for (const WordNode &node : chain) {
            size_t hashval = get_hashval(node.word);
            new_table[hashval].push_back(node);
        }
    }

    table = std::move(new_table);
}

/*
 * name: get_hashval
 * purpose: gets the hash value for a word with respect to the table size
 * arguments: word to hash
 * returns: hash value for the word
 * effects: none
 */
size_t index::get_hashval(const std::string &word) const
{
    std::hash<std::string> hasher;
    return hasher(word) % table_size;
}