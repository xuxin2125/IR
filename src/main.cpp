#include <iostream>
#include <string>
#include <fstream>
#include "Utils.h"
#include "IndexList.h"
#include "Query.h"
using namespace std;



int main() {
    int docN=20;
    char str[100];
    string query;

    IndexList *indexList=new IndexList();
    map<string, ItemInfo> index=indexList->CreateIndex(docN);
    //indexList->printIndex();

    while(1) {
        cout << "please input your words" << endl;
        cin.getline(str,100);
        query=string(str);
        if(query=="###") break;
        Query *q=new Query();
        vector<int> res;
        res = q->query(query, indexList);
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";
        //if(res.size()<5)

        cout<<endl;
    }


//    Query *q;
//    q->test();
    return 0;
}
