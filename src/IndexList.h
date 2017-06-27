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
public:
    vector<int> docID;
    map<string, ItemInfo> CreateIndex(int maxDocNum);
    void printIndex();
    map<string, ItemInfo> getIndex(){ return index;};
private:
    map<string, ItemInfo> index;



};


#endif //IR_PROJECT_INDEXLIST_H
