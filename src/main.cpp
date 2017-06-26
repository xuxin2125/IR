#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
#include "IndexList.h"
#include "Query.h"
using namespace std;



int main() {
    int docN=9;
    IndexList *indexList=new IndexList();
    map<string, ItemInfo> index=indexList->CreateIndex(docN);
    //indexList->printIndex();
    Query q;
    q.pocessquery(index, docN);
    return 0;
}
