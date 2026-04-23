/*
 * gerp.h
 * Romil Shah & Belema Roberts
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Defines the main functions for the gerp program, including building the 
 * indexes, running the query loop, and processing files.
 */

#ifndef GERP_H
#define GERP_H

#include <fstream>
#include <string>

#include "index.h"
#include "File_Storage.h"


void buildIndexes(const std::string &inputDirectory, FileStorage &storage,
                  index &sensitiveIndex, index &insensitiveIndex);

void runQueryLoop(index &sensitiveIndex, index &insensitiveIndex,
                  FileStorage &storage, std::ofstream &outFile);



#endif