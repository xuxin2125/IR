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
    int tf;
    int df;
    map<int,vector<int>> DocPos;
    void initial(){
        itemName="";
        tf=0;
        df=0;
        DocPos.empty();
    }
};
#endif //IR_PROJECT_ITEMINFO_H
