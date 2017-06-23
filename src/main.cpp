#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
#include "IndexList.h"
using namespace std;



int main() {
    int docN=9;
    IndexList *indexList=new IndexList();
    map<string, ItemInfo> index=indexList->CreateIndex(docN);
    indexList->printIndex();
    return 0;
}
