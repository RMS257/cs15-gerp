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