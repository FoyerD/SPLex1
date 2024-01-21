#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Parser{
    public:
        Parser();
        vector<string> ParseFile(const string &configFilePath);
        vector<string> Parser::ParseLine(string line);
    private:
};