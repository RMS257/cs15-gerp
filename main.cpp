

/*
#include <iostream>
#include <sstream>
#include <fstream>

#include "index.h"
#include "File_Storage.h"
#include "DirNode.h"
#include "FSTree.h"
#include "processing.h"

*/


/*
 * main.cpp
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Runs the gerp program by checking command-line arguments,
 * opening the initial output file, building the indexes,
 * and starting the command loop.
 */

#include <fstream>
#include <iostream>
#include <string>

#include "index.h"
#include "File_Storage.h"
#include "gerp.h"

using namespace std;

/*
 * name: main
 * purpose: run gerp
 * arguments: argc is the number of command-line arguments
 *            argv is the command-line argument array
 * returns: EXIT_SUCCESS on success, EXIT_FAILURE on bad usage
 * effects: opens files, builds indexes, and runs the command loop
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        return EXIT_FAILURE;
    }

    string inputDirectory = argv[1];
    string outputFile = argv[2];

    ofstream outFile(outputFile);
    if (not outFile.is_open()) {
        cerr << "Unable to open output file " << outputFile << endl;
        return EXIT_FAILURE;
    }

    FileStorage storage;
    index sensitiveIndex;
    index insensitiveIndex;

    buildIndexes(inputDirectory, storage, sensitiveIndex, insensitiveIndex);
    runQueryLoop(sensitiveIndex, insensitiveIndex, storage, outFile);

    outFile.close();
    return EXIT_SUCCESS;
}
