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
public:
    vector<bool> result;
    vector<bool> pocessquery(map<string, ItemInfo> index, int docnum);//查询入口
private:
    vector<bool> boolretrieval(map<string, ItemInfo> index, string q, int docnum); //在index中查询一个单词
    string spell_correct(map<string, ItemInfo> index, string w);// 拼写矫正
    unsigned lev_distance(string a, string b);// 计算Levenshtein距离
    unsigned min(unsigned x, unsigned y, unsigned z);//返回最小值
};


#endif //IR_PROJECT_QUERY_H
