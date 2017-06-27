//
// Created by xuxin on 2017/6/27.
//

#ifndef IR_PROJECT_VSM_H
#define IR_PROJECT_VSM_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "IndexList.h"
using namespace std;
class VSM {
private:
    map<string,int> queryTf;
    map<string,double> Wtq;
    map<string,double> Wtd;
    map<int,double> mDocScore;
    map<string,int> parseQueryWords(vector<string> words);
    map<string,double>calWtq(IndexList *indexList);
    map<string, double>calWtd(IndexList *indexList,int docId);
    vector<int> sortScore(map<int,double>docScore);
public:
    vector<int> calScore(vector<string> q, vector<int> docId, IndexList* indexList);
    void test();


};


#endif //IR_PROJECT_VSM_H
