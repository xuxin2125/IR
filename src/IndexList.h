//
// Created by xuxin on 2017/6/22.
//

#ifndef IR_PROJECT_INDEXLIST_H
#define IR_PROJECT_INDEXLIST_H
#include <string>
#include <map>
#include "ItemInfo.h"
using namespace std;
class IndexList {
private:
    map<string, ItemInfo> index;
    map<string,string> permutermIndex;
public:
    vector<int> docID;
public:
    map<string, ItemInfo> CreateIndex(int maxDocNum);
    map<string,string> CreatePermutermIndex();
    void printIndex();
    map<string, ItemInfo> getIndex(){ return index;};
    map<string, string> getPermutermIndex(){ return permutermIndex;};



};


#endif //IR_PROJECT_INDEXLIST_H
