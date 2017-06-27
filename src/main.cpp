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
    vector<int> res;

    IndexList *indexList=new IndexList();
    map<string, ItemInfo> index=indexList->CreateIndex(docN);
    map<string,string> permutermIndex=indexList->CreatePermutermIndex();

    //indexList->printIndex();

    Query *q=new Query();
    vector<string> words;

    while(1) {
        cout << "please input your words" << endl;
        cin.getline(str,100);
        query=string(str);
        if(query=="###")
            break;
        res = q->query(query, indexList);
        if(res.empty()) {
            query=q->spellCorrect(index, query);
            cout << "No result find" << endl;
            cout << "Maybe you want to search the " << query<<endl;
            res = q->query(query, indexList);
        }
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";
        cout<<endl;

        words=q->getWords();
        //ToDO 排序和TOP K 根据words和res排序
    }
    cout<<"Thanks for using!"<<endl;
    return 0;
}
