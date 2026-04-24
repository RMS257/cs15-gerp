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
        cerr << "Could not open output file " <<  endl;
        return EXIT_FAILURE;
    }

    FileStorage storage;
    index sensitiveIndex;
    index insensitiveIndex;

    try {
        buildIndexes(inputDirectory, storage, sensitiveIndex, insensitiveIndex);
    } catch (const runtime_error &e) {
        cerr << "Could not build index, reason:\n" << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    runQueryLoop(sensitiveIndex, insensitiveIndex, storage, outFile);

    outFile.close();
    return EXIT_SUCCESS;
}
