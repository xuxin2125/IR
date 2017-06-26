//
// Created by xuxin on 2017/6/23.
//

#include "Utils.h"

bool Utils::file_exist(string filename)
{
    ifstream fin( filename.c_str());
    if( !fin )
        return false;
    return true;
}

string Utils::readfile(string filename) {
    ifstream fin( filename.c_str());
    if( !fin )
    {
        cout << "Error opening " << filename << " for input" << endl;
        exit(-1);
    }
    string s, doc="";
    while( getline(fin,s) )
    {
        doc=doc+s+'\n';
    }
    return doc;
}

string Utils::normalize(string doc) {
    string str="";
    for(int i=0;i<doc.length();i++)
    {
        switch(doc[i])
        {
            case ',':
            case '!':
            case '?':
            case ':':
            case '(':
            case ')':
            case '<':
            case '>':
            case '[':
            case ']':
            case '\'':
            case '\"':
                break;
            case ';':
            case '-':
            case '/':
            case '\\':
            case '\n':
            case '\t':
            case ' ':
                if(str.length()>0&&str.back()!=' ')
                    str+=' ';
                break;
            case '.':
                if(i<doc.length()-1&&(doc[i+1]!=' '&&doc[i+1]!='\n'))
                    str+=doc[i];
                break;
            default: str+=doc[i];
        }

    }
    return str;
}

string Utils::toLower(string str){
    string out="";
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>='A'&&str[i]<='Z')
            out=out+(char)(str[i]+32);
        else
            out+=str[i];
    }
    return out;
}

vector<string> Utils::split(string str) {
    vector<string> itemList;
    string word="";
    bool flag=false;
    for(int i=0;i<str.length();i++)
    {
        if(str[i]!=' ') //不为空格
        {
            word += str[i];
            flag=true;
        }
        else //为空格
        {
            if(flag==true) {
                itemList.push_back(word);
                word = "";
            }
            flag=false;
        }
        if(str.back()!=' ')
            itemList.push_back(word);
    }
    return itemList;

}