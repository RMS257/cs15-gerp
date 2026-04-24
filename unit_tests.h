#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include <cassert>
#include <iostream>
#include "processing.h"
#include "File_storage.h"
#include "index.h"

// --- processing.cpp tests ---
void test_stripNonAlphaNum_basic() {
    assert(stripNonAlphaNum("!@#hello$$") == "hello");
}

void test_stripNonAlphaNum_no_punct() {
    assert(stripNonAlphaNum("world") == "world");
}

void test_stripNonAlphaNum_only_punct() {
    assert(stripNonAlphaNum("---") == "");
}

void test_stripNonAlphaNum_empty() {
    assert(stripNonAlphaNum("") == "");
}

void test_stripNonAlphaNum_mixed() {
    assert(stripNonAlphaNum(" 123abc!@#2@@ ") == "123abc!@#2");
}

// --- FileStorage tests ---
void test_file_storage_add_get() {
    FileStorage storage;
    storage.addPath("test/path.txt");
    assert(storage.getPath(0) == "test/path.txt");
    
    storage.addLine("This is a test line", 0, 1);
    assert(storage.getLine_info(0).line_txt == "This is a test line");
    assert(storage.getLine_info(0).line_Num == 1);
}

// --- index tests ---
void test_index_add_get() {
    index my_index;
    my_index.addWord("hello", 5);
    assert(my_index.getLines("hello").size() == 1);
    assert(my_index.getLines("hello")[0] == 5);
}

void test_index_not_found() {
    index my_index;
    my_index.addWord("hello", 5);
    
    // Querying a word not in the index should yield an empty vector
    assert(my_index.getLines("world").empty() == true);
}

void test_index_multiple_lines() {
    index my_index;
    my_index.addWord("test", 1);
    my_index.addWord("test", 5);
    my_index.addWord("test", 10);
    
    const std::vector<int> &lines = my_index.getLines("test");
    assert(lines.size() == 3);
    assert(lines[0] == 1);
    assert(lines[1] == 5);
    assert(lines[2] == 10);
}

void test_index_resize() {
    index my_index;
    // Default table size is 100, resizes at load factor 0.75.
    // Adding 150 unique words forces at least one resize.
    for (int i = 0; i < 150; i++) {
        my_index.addWord("word" + std::to_string(i), i);
    }
    
    // Verify that data from before and after the resize is intact
    assert(my_index.getLines("word0")[0] == 0);
    assert(my_index.getLines("word149")[0] == 149);
}

void test_file_storage_multiple() {
    FileStorage storage;
    storage.addPath("dir/file1.txt");
    storage.addPath("dir/file2.txt");
    
    storage.addLine("Line 1 from file 1", 0, 1);
    storage.addLine("Line 1 from file 2", 1, 1);
    
    assert(storage.getPath(1) == "dir/file2.txt");
    assert(storage.getLine_info(1).line_txt == "Line 1 from file 2");
    assert(storage.getLine_info(1).path_idx == 1);
}

#endif