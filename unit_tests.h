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

#endif