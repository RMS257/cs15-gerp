#include <cctype>
#include <string>
#include "DirNode.h"
#include "FSTree.h"
#include <iostream>

using namespace std;

string stripNonAlphaNum(string s)
{
    int start = 0;
    // end starts at the last character of the string
    int end = s.length() - 1;

    // move start forward until we hit an alphanumeric character
    while (start <= end and not isalnum(s[start])) {
        start++;
    }

    // move end backward until we hit an alphanumeric character
    while (end >= start and not isalnum(s[end])) {
        end--;
    }

    // if nothing valid remains, return empty string
    if (start > end) {
        return "";
    }

    // return the cleaned substring
    return s.substr(start, end - start + 1);
}

void traversal_helper(DirNode *node, std::string path) {
    // traverse all the subdirectories in the current directory
    for (int i = 0; i < node->numSubDirs(); i++) {
        DirNode *next = node->getSubDir(i);
        traversal_helper(next, path + "/" + next->getName());
    }

    // print all the files in the current directory
    for (int j = 0; j < node->numFiles(); j++) {
        std::cout << path << "/" << node->getFile(j) << std::endl;
    }
}

void traverseDirectory(string directory) {
    //Create tree from directory
    FSTree tree(directory);

    //Check if tree is empty
    if (tree.isEmpty()) {
        return;
    }

    //Get the root of the tree and traverse it
    DirNode *node = tree.getRoot();
    if (node == nullptr) {
        return;
    }

    //traverse using the helper function
    traversal_helper(node, node->getName());
}