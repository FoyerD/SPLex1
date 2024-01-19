#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

class Parser{
    public:
        Parser(const string &configFilePath);
        vector<string> ParseFile();
        vector<string> ParseLine(string line);
    private:
        const string &configFilePath;
};