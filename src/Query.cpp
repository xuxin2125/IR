//
// Created by xuxin on 2017/6/26.
//

#include "Query.h"

vector<bool> Query::pocessquery(map<string, ItemInfo> index, int docnum)//查询入口
{
    vector<bool> result(docnum + 1, false),temp(docnum+1,false);
    cout << "Please enter you query" << endl;
    vector<string> querys;
    int i;
    for (string t; cin >> t;) {
        if (t == "AND") {
            cin >> t;
            temp = boolretrieval(index, t, docnum);
            for (i = 1; i < docnum; i++)
                result[i] = result[i] && temp[i];
        }
        else if (t == "OR") {
            cin >> t;
            temp = boolretrieval(index, t, docnum);
            for (i = 1; i < docnum; i++)
                result[i] = result[i] || temp[i];
        }
        else if (t == "NOT") {
            cin >> t;
            temp = boolretrieval(index, t, docnum);
            for (i = 1; i < docnum; i++)
                result[i] = result[i] &&(!temp[i]);
        }
        else {
            temp = boolretrieval(index, t, docnum);
            for (i = 1; i < docnum; i++)
                result[i] = result[i] && temp[i];
        }
    };

    return result;
}

vector<bool> Query::boolretrieval(map<string, ItemInfo> index,string q, int docnum) //在index中查询一个单词
{
    vector<bool> result(docnum+1,false);
    map<string, ItemInfo>::iterator it;
    ItemInfo q_f;
    it = index.find(q);
    if (it == index.end()) {
        cout << "can't find" << q << " ";
        q = spell_correct(index, q);
        cout << "use " << q << " instead"<<endl;
    }

    it = index.find(q);
    q_f = it->second;
    map<int, vector<int>>::iterator p;
    p = q_f.DocPos.begin();
    while (p != q_f.DocPos.end()) {
        result[p->first] = true;
        p++;
    }
    return result;
}

string Query::spell_correct(map<string, ItemInfo> index, string w)// 拼写矫正
{
    vector<string> tmp;
    unsigned min_lev, tmp_lev;
    map<string, ItemInfo>::iterator it;
    string item, corstr;
    it = index.begin();
    item = it->first;
    tmp_lev = lev_distance(item, w);
    min_lev = tmp_lev;
    tmp.push_back(item);
    it++;
    while (it != index.end()) {// 寻找lev_distace最小的词
        item = it->first;
        tmp_lev = lev_distance(item, w);
        if (tmp_lev == min_lev) {
            tmp.push_back(item);
        }
        else if (tmp_lev < min_lev) {
            tmp.clear();
            tmp.push_back(item);
            min_lev = tmp_lev;
        }
        it++;
    }
    //相同lev_distance比较tf
    vector<string>::iterator p;
    p = tmp.begin();
    int maxtf = 0,i = 0;
    corstr = tmp[i];
    ItemInfo itemInfo;
    while (p != tmp.end()) {
        item = tmp[i];
        itemInfo = index[item];
        if (itemInfo.cf > maxtf) {
            maxtf = itemInfo.cf;
            corstr = item;
        }
        i++;

    }
    return corstr;
}

unsigned Query::lev_distance(string a, string b)// 计算Levenshtein距离
{
    const char * s = a.c_str();
    const char *t = b.c_str();
    //n:目标单词t的长度   m:源单词s的长度
    unsigned m_tmp = 0, n_tmp = 0;
    int i = 0;
    //计算源单词长度
    while (s[i])
    {
        i++;
        m_tmp++;
    }
    //计算目标单词长度
    i = 0;
    while (t[i])
    {
        i++;
        n_tmp++;
    }
    if (m_tmp == 0)
        return n_tmp;
    if (n_tmp == 0)
        return m_tmp;

    const unsigned m = m_tmp + 1;
    const unsigned n = n_tmp + 1;
    unsigned matrix[100][100];
    //给矩阵的第0行和第0列赋值
    for (i = 0; i<m; i++)
        matrix[i][0] = i;
    for (i = 0; i<n; i++)
        matrix[0][i] = i;
    //填充矩阵的其他元素，逐行填充
    int j;
    for (i = 1; i<m; i++)
        for (j = 1; j<n; j++)
        {
            unsigned cost = 1;
            if (s[i - 1] == t[j - 1])
                cost = 0;
            matrix[i][j] = min(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1, matrix[i - 1][j - 1] + cost);
        }
    //返回matrix[m-1][n-1],即两个字符串之间的距离
    return matrix[m - 1][n - 1];
}

unsigned Query::min(unsigned x, unsigned y, unsigned z)//返回最小值
{
    unsigned tmp = (x<y ? x : y);
    tmp = (tmp<z ? tmp : z);
    return tmp;
}