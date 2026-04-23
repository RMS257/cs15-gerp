/*
 * gerp.cpp
 * Romil Shah
 * CS 15 Project 4 - gerp
 *
 * Purpose:
 * Contains the main gerp logic for building the indexes,
 * processing files, handling user queries, and printing results.
 */

#include "gerp.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "DirNode.h"
#include "FSTree.h"
#include "processing.h"

using namespace std;

/*
 * name: toLower
 * purpose: convert a string to lowercase
 * arguments: word is the input string
 * returns: lowercase version of word
 * effects: none
 */
string toLower(string word)
{
    for (int i = 0; i < (int)word.length(); i++) {
        word[i] = tolower((unsigned char)word[i]);
    }
    return word;
}

/*
 * name: splitWords
 * purpose: split a line into space-separated tokens
 * arguments: line is the input string
 * returns: vector of words
 * effects: none
 */
vector<string> splitWords(const string &line)
{
    vector<string> words;
    stringstream ss(line);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

/*
 * name: processFile
 * purpose: read one file, store its lines, and add each unique word
 *          on that line to both indexes
 * arguments: filePath is the full path of the file
 *            pathIdx is the file path id in FileStorage
 *            nextLineId is the next available line id
 *            storage stores file paths and lines
 *            sensitiveIndex stores exact-case words
 *            insensitiveIndex stores lowercase words
 * returns: none
 * effects: updates storage, both indexes, and nextLineId
 */
void processFile(const string &filePath, int pathIdx, int &nextLineId,
                 FileStorage &storage, index &sensitiveIndex,
                 index &insensitiveIndex)
{
    ifstream infile(filePath);

    if (not infile.is_open()) {
        return;
    }

    string line;
    int lineNum = 1;

    while (getline(infile, line)) {
        int currLineId = nextLineId;

        storage.addLine(line, pathIdx, lineNum);
        nextLineId++;

        // These sets make sure the same line is only added once
        // for each unique word.
        set<string> seenSensitive;
        set<string> seenInsensitive;

        vector<string> tokens = splitWords(line);

        for (int i = 0; i < (int)tokens.size(); i++) {
            string cleaned = stripNonAlphaNum(tokens[i]);

            if (cleaned == "") {
                continue;
            }

            seenSensitive.insert(cleaned);
            seenInsensitive.insert(toLower(cleaned));
        }

        for (set<string>::iterator it = seenSensitive.begin();
             it != seenSensitive.end(); ++it) {
            sensitiveIndex.addWord(*it, currLineId);
        }

        for (set<string>::iterator it = seenInsensitive.begin();
             it != seenInsensitive.end(); ++it) {
            insensitiveIndex.addWord(*it, currLineId);
        }

        lineNum++;
    }
}

/*
 * name: buildIndexesHelper
 * purpose: recursively traverse the directory tree and index all files
 * arguments: node is the current directory node
 *            currPath is the full path to the current directory
 *            nextPathIdx is the next available path id
 *            nextLineId is the next available line id
 *            storage stores file paths and lines
 *            sensitiveIndex stores exact-case words
 *            insensitiveIndex stores lowercase words
 * returns: none
 * effects: updates storage, indexes, nextPathIdx, and nextLineId
 */
void buildIndexesHelper(DirNode *node, const string &currPath,
                        int &nextPathIdx, int &nextLineId,
                        FileStorage &storage, index &sensitiveIndex,
                        index &insensitiveIndex)
{
    for (int i = 0; i < node->numFiles(); i++) {
        string filePath = currPath + "/" + node->getFile(i);

        storage.addPath(filePath);
        int currPathIdx = nextPathIdx;
        nextPathIdx++;

        processFile(filePath, currPathIdx, nextLineId, storage,
                    sensitiveIndex, insensitiveIndex);
    }

    for (int i = 0; i < node->numSubDirs(); i++) {
        DirNode *subDir = node->getSubDir(i);
        string nextPath = currPath + "/" + subDir->getName();

        buildIndexesHelper(subDir, nextPath, nextPathIdx, nextLineId,
                           storage, sensitiveIndex, insensitiveIndex);
    }
}

/*
 * name: buildIndexes
 * purpose: build both indexes and store all lines/files
 * arguments: inputDirectory is the root directory to index
 *            storage stores file paths and lines
 *            sensitiveIndex stores exact-case words
 *            insensitiveIndex stores lowercase words
 * returns: none
 * effects: fills storage and both indexes
 */
void buildIndexes(const string &inputDirectory, FileStorage &storage,
                  index &sensitiveIndex, index &insensitiveIndex)
{
    FSTree tree(inputDirectory);

    if (tree.isEmpty()) {
        return;
    }

    DirNode *root = tree.getRoot();

    if (root == nullptr) {
        return;
    }

    int nextPathIdx = 0;
    int nextLineId = 0;

    buildIndexesHelper(root, root->getName(), nextPathIdx, nextLineId,
                       storage, sensitiveIndex, insensitiveIndex);
}

/*
 * name: printMatches
 * purpose: print all matching lines in the required format
 * arguments: matches is the vector of matching line ids
 *            storage stores file paths and line data
 *            outFile is the current output stream
 * returns: none
 * effects: writes results to the output file
 */
void printMatches(const vector<int> &matches, FileStorage &storage,
                  ofstream &outFile)
{
    for (int i = 0; i < (int)matches.size(); i++) {
        const FileStorage::LineData &line = storage.getLine_info(matches[i]);
        string path = storage.getPath(line.path_idx);

        outFile << path << ":" << line.line_Num << ": "
                << line.line_txt << endl;
    }
}

/*
 * name: handleQuery
 * purpose: run one query and print either results or a not-found message
 * arguments: word is the query word
 *            insensitive is true if the query is case-insensitive
 *            sensitiveIndex stores exact-case words
 *            insensitiveIndex stores lowercase words
 *            storage stores file paths and line data
 *            outFile is the current output stream
 * returns: none
 * effects: writes results to the output file
 */
void handleQuery(string word, bool insensitive, index &sensitiveIndex,
                 index &insensitiveIndex, FileStorage &storage,
                 ofstream &outFile)
{
    word = stripNonAlphaNum(word);

    const vector<int> *matches;

    if (insensitive) {
        string lowered = toLower(word);
        matches = &insensitiveIndex.getLines(lowered);

        if (matches->empty()) {
            outFile << word << " Not Found." << endl;
            return;
        }
    } else {
        matches = &sensitiveIndex.getLines(word);

        if (matches->empty()) {
            outFile << word
                    << " Not Found. Try with @insensitive or @i."
                    << endl;
            return;
        }
    }

    printMatches(*matches, storage, outFile);
}

/*
 * name: runQueryLoop
 * purpose: repeatedly process user commands until quit or EOF
 * arguments: sensitiveIndex stores exact-case words
 *            insensitiveIndex stores lowercase words
 *            storage stores file paths and line data
 *            outFile is the current output stream
 * returns: none
 * effects: reads commands from cin, prints prompts to cout,
 *          and writes results to the output file
 */
void runQueryLoop(index &sensitiveIndex, index &insensitiveIndex,
                  FileStorage &storage, ofstream &outFile)
{
    string inputLine;
    char curr_act = 'n'; // 'n' = normal, 'f' = file, 'i' = insensitive

    cout << "Query? "; // initial prompt before any input is processed
    while (true) {
        if (not getline(cin, inputLine)) {
            cout << "Goodbye! Thank you and have a nice day." << endl;
            return;
        }

        vector<string> words = splitWords(inputLine);
        for (int i = 0; i < (int)words.size(); i++) {
            if (curr_act == 'f') {
                // Process argument for @f
                outFile.close();
                outFile.open(words[i]);
                curr_act = 'n';
                cout << "Query? ";
            } else if (curr_act == 'i') {
                // Process argument for @i or @insensitive
                handleQuery(words[i], true, sensitiveIndex,
                            insensitiveIndex, storage, outFile);
                curr_act = 'n';
                cout << "Query? ";
            } else if (words[i] == "@f") { 
                curr_act = 'f'; // Expect an output file next
            } else if (words[i] == "@i" or words[i] == "@insensitive") {
                curr_act = 'i'; // Expect a case-insensitive query next
            } else if (words[i] == "@q" or words[i] == "@quit") {
                cout << "Goodbye! Thank you and have a nice day." << endl;
                return;
            } else { //Case-sensitive query
                handleQuery(words[i], false, sensitiveIndex,
                            insensitiveIndex, storage, outFile);
                cout << "Query? ";
            }
        }
    }
}