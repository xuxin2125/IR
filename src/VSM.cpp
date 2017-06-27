//
// Created by xuxin on 2017/6/27.
//

#include "VSM.h"
#include <cmath>

map<string,int> VSM::parseQueryWords(vector<string> words) {
    queryTf.clear();
    for(int i=0;i<words.size();i++)
        if(queryTf.find(words[i])==queryTf.end())
            queryTf[words[i]]=1;
        else
            queryTf[words[i]]++;
    return queryTf;
}

map<string,double> VSM::calWtq(IndexList *indexList) {
    Wtq.clear();
    map<string,int> ::iterator p;
    double df,idf,tf;
    string word;
    for(p=queryTf.begin();p!=queryTf.end();p++)
    {
        word=p->first;
        tf=p->second;
        df=indexList->getIndex()[word].df;
        idf=log(indexList->docID.size()/df);
        Wtq[word]=tf*idf;
    }
    return Wtq;
}

map<string, double> VSM::calWtd(IndexList *indexList, int docId) {
    Wtd.clear();
    map<string,int> ::iterator p;
    vector<string> words;
    string word;
    int tf;
    double c=0;
    words=indexList->docBoW[docId];
    for(int i=0;i<words.size();i++){
        tf=indexList->getIndex()[words[i]].getTf(docId);
        c+=tf*tf;
    }
    c=sqrt(c);
    for(p=queryTf.begin();p!=queryTf.end();p++)
    {
        word=p->first;
        tf=indexList->getIndex()[word].getTf(docId);
        Wtd[word]=tf/c;
    }
    return Wtd;
}

vector<int> VSM::calScore(vector<string> q, vector<int> resIdList, IndexList *indexList) {
    mDocScore.clear();

    parseQueryWords(q);
    calWtq(indexList);

    int docId;
    string word;
    map<string,int> ::iterator p;
    for(int i=0;i<resIdList.size();i++) {
        docId=resIdList[i];
        calWtd(indexList,docId);
        mDocScore[docId]=0;
        for(p=queryTf.begin();p!=queryTf.end();p++)
        {
            word=p->first;
            mDocScore[docId]+=Wtq[word]*Wtd[word];
        }
    }
    return sortScore(mDocScore);


}

vector<int> VSM::sortScore(map<int,double>docScore)
{
    vector<int> res;
    vector<pair<int, double>> tmpMap;
    for (map<int,double> ::iterator it = docScore.begin(); it!=docScore.end(); it++)
        tmpMap.push_back(make_pair(it->first, it->second));

    sort(tmpMap.begin(), tmpMap.end(),
         [](const pair<int, double> &x, const pair<int, double> &y) -> double {
             return x.second > y.second;
         });

    vector<pair<int, double>>::iterator it;
    for(it=tmpMap.begin();it!=tmpMap.end();it++)
        res.push_back(it->first);
    return res;
}

//-------------测试--------
void VSM::test() {
    map<int,double> ds;
//    vector<int> res;
//    ds[1]=8.1;
//    ds[2]=9.3;
//    ds[3]=7.2;
//    ds[4]=10.2;
//    res=sortScore(ds);
//    for (int i = 0; i < res.size(); i++)
//        cout << res[i] << " ";
//    cout<<endl;
    cout<<ds[5]<<"aaa";
}

