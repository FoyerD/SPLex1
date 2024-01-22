#include "include/Parser.h"
//constructor
Parser::Parser(){}

/**
 * @param configFilePath - the path to the configuration file, given by the user.
 * @returns - vector of string containing each line of the file where each string is a line.
*/
vector<string> Parser::ParseFile(const string &configFilePath){
    fstream configFile;
    vector<string> data;
    configFile.open(configFilePath, ios::out);
     if (configFile.is_open()) { 
        string line;
        while (std::getline(configFile, line)) { 
            data.push_back(line);
        }
    }
    configFile.close();
    return data;
}

/**
 * @param line - a line that we want to seperate to words.
 * @return vector of strings where each string is a word in the line.
 */
vector<string> Parser::ParseLine(string line){
    string word;
    stringstream ss(line);
    vector<string> line_words;
    while (getline(ss, word, ' ')) {
        line_words.push_back(word);
    }
    return line_words;
}