#include "../include/Parser.h"

Parser::Parser(){}

vector<string> Parser::ParseFile(const string &configFilePath){
    fstream configFile;
    vector<string> data;
    configFile.open(configFilePath, ios::in);
     if (configFile.is_open()) { 
        string line;
        while (std::getline(configFile, line)) { 
            if(line.compare("") != 0) data.push_back(line);
        }
        configFile.close();
    }
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