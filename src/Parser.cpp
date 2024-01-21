#include "include/Parser.h"

Parser::Parser(const string &FilePath): configFilePath(FilePath){}

vector<string> Parser::ParseFile(){
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

vector<string> Parser::ParseLine(string line){
    string word;
    stringstream ss(line);
    vector<string> line_words;
    while (getline(ss, word, ' ')) {
        line_words.push_back(word);
    }
    return line_words;
}

Parser::Parser(const Parser& parser): configFilePath(parser.configFilePath){}