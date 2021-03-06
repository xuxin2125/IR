//
// Created by xuxin on 2017/6/26.
//

#ifndef IR_PROJECT_QUERY_H
#define IR_PROJECT_QUERY_H


#include <string>
#include <map>
#include <vector>
#include "ItemInfo.h"
#include "IndexList.h"
#include "Utils.h"
using namespace std;

class	Query {
private:
    vector<string> mWords;
public:
    vector<int> query(string q,IndexList *indexList);
    vector<string> getWords(){ return mWords; };
    string spellCorrect(map<string, ItemInfo> index, string w);
    void test();
private:
    string preprocessor(string query);
    bool isK(string str);
    vector<string> enumWords(string query);
    vector<int> processor(string query,IndexList *indexList);
    vector<int> biwordProcess(vector<string>multiWords,map<string, ItemInfo> indexN);
    vector<int> positionalInsersect(ItemInfo p1,ItemInfo p2,int k);
    vector<int> wildcardQuery(string wildcard,IndexList *indexList);
    vector<int> boolCal(string op, vector<int> a, vector<int> b);

    int editDistance(string a, string b);
    int min(int x, int y, int z);

};


#endif //IR_PROJECT_QUERY_H
