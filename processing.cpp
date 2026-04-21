#include <cctype>
#include <string>

using namespace std;

/*
 * name: splitWords
 * purpose: split a line into space-separated tokens
 * arguments: line is the input string
 * returns: vector of words
 * effects: none
 */
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