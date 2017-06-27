//
// Created by xuxin on 2017/6/26.
//
#include <stdlib.h>
#include "Query.h"

vector<int> Query::query(string q, IndexList *indexList) {
    q=preprocessor(q);
    if(enumWords(q).empty()){
        vector<int> tmp;
        return tmp;   //返回空列表®
    }
    //-------JUST TRY---------
    vector<string> words;
    Utils *utils = new Utils();
    words=utils->split(q);
    for(int i=0;i<words.size();i++)
        words[i]=utils->toLower(words[i]);
    if(words.size()==3&&isK(words[1]))  //K近领
    {
        int k=0;
        for(int i=1;i<words[1].length();i++)
            k=k*10+words[1][i]-'0';
        return positionalInsersect(indexList->getIndex()[words[0]], indexList->getIndex()[words[2]],k);
    }
    else if(words.size()==1&&words[0].find("*")!=-1) //通配符 TODO
    {
        return wildcardQuery(words[0],indexList);
    }
    //---------END------------
    else
        return processor(q,indexList);
}
//目前只支持单个*通配符
vector<int> Query::wildcardQuery(string q,IndexList *indexList) {
    string newQuery="";
    Utils *utils=new Utils();
    map<string,string> permutermIndex=indexList->getPermutermIndex();
    map<string,string>::iterator it;
    q+='$';
    while(q.back()!='*')
        q=utils->rotateStr(q);
    q.pop_back();
    for(it=permutermIndex.begin();it!=permutermIndex.end();it++)
        if(it->first.find(q)==0) //匹配
        {
            if(newQuery=="")
                newQuery+=it->second;
            else
                newQuery=newQuery+" OR "+it->second;
        }
    //----------------提示------------
    if(newQuery!="")
        cout<<"find following term: "<<newQuery<<endl;
    return query(newQuery, indexList);

}

vector<string> Query::enumWords(string query) { //统计查询向量
    vector<string> tmpWords;
    Utils *utils = new Utils();
    vector<string> tmp= utils->split(query);
    for(int i=0;i<tmp.size();i++)
        if(tmp[i]!="AND" &&tmp[i]!="OR" &&tmp[i]!="NOT" &&!isK(tmp[i])&&tmp[i]!="("&&tmp[i]!=")")
            tmpWords.push_back(utils->toLower(tmp[i]));
    utils->loadStopWords("../src/stopWords.txt");
    mWords=utils->deleteStopWords(tmpWords);
    return mWords;
}

bool Query::isK(string str) {
    if(str.length()<2) return false;
    if(str[0]!='/') return false;
    for(int i=1;i<str.length();i++)
        if(str[i]>'9'||str[i]<'0') return false;
    return true;
}

string Query::preprocessor(string query)
{
    string newQuery="";
    for(int i=0;i<query.length();i++)
    {
        if(query[i]=='('||query[i]==')')
            newQuery=newQuery+' '+query[i]+' ';
        else
            newQuery+=query[i];
    }
    return newQuery;
}

vector<int> Query::processor(string query,IndexList *indexList) {
    vector<string> words;
    Utils *utils = new Utils();
    query=" ( "+query+" ) ";
    words=utils->split(query);

    for(int i=0;i<words.size();i++)
    {
        if(words[i]=="AND"||words[i]=="OR"||words[i]=="NOT")
            continue;
        else
            words[i]=utils->toLower(words[i]);
    }

    utils->loadStopWords("../src/stopWords.txt");
    words=utils->deleteStopWords(words);

    //两个栈，一个为布尔符号栈，一个为词项(组）结果docID列表栈
    vector<string> opStack;
    vector<vector<int>> resStack;

    string opTmp;
    vector<int> docTempList1;
    vector<int> docTempList2;
    vector<string> multiWords;
    bool wordFlag=false;
    for(int i=0;i<words.size();i++)
    {
        if(words[i]=="("||words[i]=="NOT"||words[i]=="AND"||words[i]=="OR"||words[i]==")") //运算符
        {
            if(wordFlag==true)
            {
                wordFlag=false;
                resStack.push_back(biwordProcess(multiWords,indexList->getIndex()));
                multiWords.clear();
                while(!opStack.empty()) {
                    opTmp = opStack.back();
                    if(opTmp=="NOT"||opTmp=="AND") {
                        opStack.pop_back();
                        if (opTmp == "NOT")
                            docTempList1 = indexList->docID;
                        else if (opTmp == "AND") {
                            docTempList1 = resStack.back();
                            resStack.pop_back();
                        }
                        docTempList2 = resStack.back();
                        resStack.pop_back();
                        resStack.push_back(boolCal(opTmp,docTempList1,docTempList2));
                    }
                    else break;

                }
            }

            if(words[i]==")") //全部弹出
            {
                opTmp=opStack.back();
                while(opTmp!="(") {
                    if(opTmp=="NOT")
                        docTempList1 = indexList->docID;
                    else {
                        docTempList1 = resStack.back();
                        resStack.pop_back();
                    }
                    docTempList2 = resStack.back();
                    resStack.pop_back();
                    resStack.push_back(boolCal(opTmp,docTempList1,docTempList2));
                    opStack.pop_back();
                    opTmp=opStack.back();
                }
                opStack.pop_back();
            }
            else {
                if(words[i]=="OR"&&!opStack.empty()&&opStack.back()=="OR")
                {
                    opTmp=opStack.back();
                    opStack.pop_back();
                    docTempList1 = resStack.back();
                    resStack.pop_back();
                    docTempList2 = resStack.back();
                    resStack.pop_back();
                    resStack.push_back(boolCal(opTmp,docTempList1,docTempList2));
                }
                opStack.push_back(words[i]);
            }

        }
        else //词项
        {
            wordFlag=true;
            multiWords.push_back(words[i]);
        }

    }
    return resStack.back();

}


vector<int> Query::biwordProcess(vector<string> multiWords,map<string, ItemInfo> index) {
    vector<vector<int>> res;
    if(multiWords.size()==1) return index[multiWords[0]].getDocList();
    for(int i=1;i<multiWords.size();i++)
        res.push_back(positionalInsersect(index[multiWords[i]],index[multiWords[i-1]],1));
    for(int i=0;i<res.size()-1;i++)
    {
        vector<int> tmpList1;
        vector<int> tmpList2;
        tmpList1=res.back();
        res.pop_back();
        tmpList2=res.back();
        res.pop_back();
        res.push_back(boolCal("AND",tmpList1,tmpList2));
    }
    return res.back();
}

vector<int> Query::positionalInsersect(ItemInfo w1,ItemInfo w2,int k)
{
    bool flag=false;
    vector<int> res;
    map<int,vector<int>>::iterator p1,p2;
    p1=w1.DocPos.begin();
    p2=w2.DocPos.begin();
    vector<int>::iterator pp1,pp2;
    while(p1!=w1.DocPos.end()&&p2!=w2.DocPos.end()){
        if(p1->first==p2->first)
        {
            flag=false;
            pp1=p1->second.begin();
            pp2=p2->second.begin();
            while(pp1!=p1->second.end())
            {
                while(pp2!=p2->second.end())
                {
                    if(abs(*pp1-*pp2)<=k) {
                        res.push_back(p1->first);
                        flag=true;
                        break;
                    }
                    else if(*pp2>*pp1)
                        break;
                    pp2++;
                }
                if(flag==true) break;
                pp1++;
            }
            p1++;
            p2++;
        }
        else if(p1->first<p2->first)
            p1++;
        else
            p2++;
    }
    return res;
}

vector<int> Query::boolCal(string op, vector<int> a, vector<int> b)
{
    vector<int> res;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    if(op=="AND")
        set_intersection(a.begin(), a.end(), b.begin(), b.end(),inserter(res,res.begin()));
    else if(op=="OR")
        set_union (a.begin(), a.end(), b.begin(), b.end(),inserter(res,res.begin()));
    else if(op=="NOT")
        set_difference(a.begin(), a.end(), b.begin(), b.end(),inserter(res,res.begin()));
    return res;
}

string Query::spellCorrect(map<string, ItemInfo> index, string w) {
    map<string,ItemInfo>::iterator it;
    int minLevenshteinDistance=999;
    string newWord=w;
    for(it = index.begin();it != index.end();it++)
        if(editDistance(w,it->first)<minLevenshteinDistance) {
            newWord = it->first;
            minLevenshteinDistance=editDistance(w,it->first);
        }
    return newWord;
}

int Query::editDistance(string a, string b) {
    int i,j;
    int s1=a.length()+1; //行数
    int s2=b.length()+1; //列数
    int m[s1][s2];
    for(i=0;i<s1;i++)
        m[i][0]=i;
    for(i=0;i<s2;i++)
        m[0][i]=i;
    for(i=1;i<s1;i++)
        for(j=1;j<s2;j++)
        {
            if(a[i-1]==b[j-1])
                m[i][j]=min(m[i-1][j-1],m[i-1][j]+1,m[i][j-1]+1);
            else
                m[i][j]=min(m[i-1][j-1]+1,m[i-1][j]+1,m[i][j-1]+1);
        }
    return m[s1-1][s2-1];

}

int Query::min(int x, int y, int z)
{
    int tmp = (x<y ? x : y);
    tmp = (tmp<z ? tmp : z);
    return tmp;
}

//-------------测试函数---------------
void Query::test() {
    vector<int> a={2,4,3,1};
    vector<int> b={2,3};
    vector<int> c;
    c=boolCal("AND",a,b);
    for (int i = 0; i < c.size(); i++)
        cout << c[i] << " ";
}