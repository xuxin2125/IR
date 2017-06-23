//
// Created by xuxin on 2017/6/22.
//

#include "IndexList.h"
#include "Utils.h"
map<string, ItemInfo> IndexList::CreateIndex(int docN)
{
    for(int i=1;i<=docN;i++) {
        string filename = "../Reuters/";
        filename+=char('0'+i);
        filename+=".html";
        Utils *utils = new Utils();
        string str;
        if(!utils->file_exist(filename)) continue;
        str = utils->readfile(filename);
        str = utils->toLower(str);
        str = utils->normalize(str);
        vector <string> itemList = utils->split(str);
        for (int j = 0; j < itemList.size(); j++){
            if(index.find(itemList[j])==index.end()) //倒排索引中没有该词条
            {
                ItemInfo itemInfo;
                itemInfo.initial();
                itemInfo.itemName=itemList[j];
                itemInfo.df++;
                itemInfo.tf++;
                vector<int> pos;
                pos.push_back(j+1);
                itemInfo.DocPos[i]=pos;
                index[itemList[j]]=itemInfo;
            }
            else{
                index[itemList[j]].tf++;
                if(index[itemList[j]].DocPos.find(i)==index[itemList[j]].DocPos.end()) //位置索引中没有该文档ID
                {
                    index[itemList[j]].df++;
                    vector<int> pos;
                    pos.push_back(j+1);
                    index[itemList[j]].DocPos[i]=pos;
                }
                else //已经有该文档ID
                    index[itemList[j]].DocPos[i].push_back(j+1);

            }
        }
    }
    return index;
};

void IndexList::printIndex() {
    map<string,ItemInfo>::iterator it;

    it = index.begin();

    while(it != index.end())
    {
        string item=it->first;
        ItemInfo itemInfo=it->second;
        cout<<item<<','<<itemInfo.tf<<':'<<endl;
        map<int,vector<int>>::iterator p;
        p=itemInfo.DocPos.begin();
        while(p!=itemInfo.DocPos.end())
        {
            cout<<"      "<<p->first<<','<<p->second.size()<<":<";
            int i;
            for(i=0;i<(p->second.size()-1);i++)
                cout<<p->second[i]<<',';
            cout<<p->second[i]<<">;"<<endl;
            p++;
        }
        it++;
    }
}
