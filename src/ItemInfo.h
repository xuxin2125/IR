//
// Created by xuxin on 2017/6/23.
//

#ifndef IR_PROJECT_ITEMINFO_H
#define IR_PROJECT_ITEMINFO_H
#include <list>
#include <vector>
using namespace std;
class ItemInfo {
public:
    string itemName;
    int cf;
    int df;
    map<int,vector<int>> DocPos;
    void initial(){
        itemName="";
        cf=0;
        df=0;
        DocPos.clear();
    }
    int getTf(int docID){
        return DocPos[docID].size();
    }
};
#endif //IR_PROJECT_ITEMINFO_H
