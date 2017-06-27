//
// Created by xuxin on 2017/6/23.
//

#ifndef IR_PROJECT_UTILS_H
#define IR_PROJECT_UTILS_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
using namespace std;
class Utils {
private:
    vector<string> stopWords;
public:
    void loadStopWords(string filename);
    vector<string> deleteStopWords(vector<string> words);
    bool file_exist(string filename);
    string readfile(string filename);
    string normalize(string doc);
    string toLower(string str);
    vector<string> split(string str);
};


#endif //IR_PROJECT_UTILS_H
