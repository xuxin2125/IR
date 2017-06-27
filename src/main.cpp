#include <iostream>
#include "Utils.h"
#include "IndexList.h"
#include "Query.h"
#include "VSM.h"
using namespace std;



int main() {
    int docN=100, topK=15;
    char str[100];
    string query;
    vector<int> res;
    //ToDO 索引模块 倒排记录表+轮排索引+文档词袋  词条化+去除停用词
    IndexList *indexList=new IndexList();
    map<string, ItemInfo> index=indexList->CreateIndex(docN);
    map<string,string> permutermIndex=indexList->CreatePermutermIndex();
    map<int,vector<string>> docBoW=indexList->createBoW();
    VSM *vsm=new VSM();

    Query *q=new Query();
    vector<string> words;

//    indexList->printIndex();
    while(1) {
        cout << "please input your words" << endl;
        cin.getline(str,100);
        query=string(str);
        if(query=="###")
            break;
        //ToDO 查询模块 布尔+K近领+通配符+短语
        res = q->query(query, indexList);
        if(res.empty()) {
            //ToDO 拼写校正
            query=q->spellCorrect(index, query);
            cout << "No result find" << endl;
            cout << "Maybe you want to search the " << query<<endl;
            res = q->query(query, indexList);
        }
        for (int i = 0; i < res.size(); i++)
            cout << res[i] << " ";
        cout<<endl;

        words=q->getWords();
        //ToDO 排序和TOP K
        res=vsm->calScore(words,res,indexList);
        if(res.size()<=topK) {
            cout << "After sort: ";
            for (int i = 0; i < res.size(); i++)
                cout << res[i] << " ";
            cout << endl;
        }
        else{
            cout << "After sort, just show Top "<<topK<<": ";
            for (int i = 0; i < topK; i++)
                cout << res[i] << " ";
            cout << endl;
        }

    }
    cout<<"Thanks for using!"<<endl;
    return 0;
}
