#include "DirNode.h"
#include "FSTree.h"
#include <iostream>
#include <string>

void traversal_helper(DirNode *node, std::string path) {
    for (int i = 0; i < node->numSubDirs(); i++) {
        DirNode *next = node->getSubDir(i);
        traversal_helper(next, path + "/" + next->getName());
    }
    for (int j = 0; j < node->numFiles(); j++) {
        std::cout << path << "/" << node->getFile(j) << std::endl;
    }
}

void traverse_dir(FSTree &tree) {
    DirNode *node = tree.getRoot();
    if (node == nullptr) {
        return;
    }
    traversal_helper(node, node->getName());
}
