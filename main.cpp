


#include <iostream>
#include <sstream>
#include <fstream>

#include "index.h"
#include "File_storage.h"
#include "DirNode.h"
#include "FSTree.h"
#include "processing.h"


int main(int argc, char *argv[])
{
    if (argc != 3) {
        std::cerr << "Usage: " << "./gerp inputDirectory outputFile" << std::endl;
        return EXIT_FAILURE;
    }
}

