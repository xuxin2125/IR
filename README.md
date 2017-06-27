# 信息检索
## 环境配置
语言：C++ <br>
平台：CLion 2016.3.2 <br>
文件：src为代码源文件，Reuters为语料库
## 模块说明
### 索引模块
IndexList.h 和indexList.cpp  <br>
建立倒排索引、轮排索引和文档词袋
```C++
IndexList *indexList=new IndexList();
map<string, ItemInfo> index=indexList->CreateIndex(docN);
map<string,string> permutermIndex=indexList->CreatePermutermIndex();
map<int,vector<string>> docBoW=indexList->createBoW();
```
### 词条模块
ItemInfo.h  <br>
存储一个词条的cf、df、和文档位置信息，并且提供获得文档tf接口。
### 查询模块
Query.h 和 Query.cpp <br>
实现了布尔查询、短语查询、通配符查询、K近临查询和拼写校正
### 向量空间模块
VSM.h  和 VSM.cpp <br>
实现Wtq和Wtd的计算，在此基础上实现评分和排序。
### 工具模块
Utils.h 和 Utils.cpp <br>
实现了词条化、去除停用词以及其他一些类似字符串分割、大小写转换、旋转字符串、读取文件的基本功能。
## 功能演示
为方便理解，在非排序演示功能块，关闭了排序功能。<br>
非排序功能演示测试文档大小 docN=20 <br>
排序功能演示测试文档大小 docN=100
### 显示倒排记录表
```
about,cf=2,df=2:
	  45,tf=1:<196>;
	  56,tf=1:<52>;
abroad,cf=1,df=1:
	  47,tf=1:<12>;
acceptances,cf=2,df=1:
	  80,tf=2:<19,37>;
accepted,cf=1,df=1:
	  19,tf=1:<11>;
accompanied,cf=1,df=1:
	  47,tf=1:<74>;
………………………………
………………………………
```
### 布尔表达式查询
本查询内容已经包含布尔查询和短语查询。短语查询采用二元词和位置信息索引。布尔查询采用双栈结构进行表达式解析运算。
```
please input your words
NOT CHAMPION
1 5 6 10 11 12 13 14 18 19 
please input your words
bahia COCOA AND NOT CHAMPION
1 
please input your words
BAHIA COCOA AND (NOT CHAMPION OR BAHIA)
1 
please input your words
normal humidity levels have not OR Argentine grain board
1 6 
```
### K近邻查询
```
please input your words
bahia /2 review
1 
```
### 通配符查询
本次通配符查询暂时只支持一个通配符，采用轮排索引实现。
```
please input your words
ba*a
find following term: bahia
1 
please input your words
c*s
find following term: carryforwards OR certificates OR circumstances OR commodities OR completes OR conditions OR considerations OR costs OR covers OR credits OR cruzados OR cts
1 5 10 11 12 13 14 18 19 
```
### 拼写校正
```
please input your words
bahic
No result find
Maybe you want to search the bahia
1 
```
### 排序
排序给定一个topK值，若结果个数小于这个值全部显示结果，否则只显示这个值对应个数的结果。
```
please input your words
feburary
No result find
Maybe you want to search the february
1 5 6 12 47 80 81 89 
After sort: 89 80 1 81 6 12 47 5 
please input your words
ba*
find following term: backlog OR bags OR bahia OR balance OR ball OR balt OR baltimore OR bank OR bankruptcy OR banks OR barge OR barges OR barley OR base OR based OR basis
1 5 42 44 45 46 47 48 49 56 59 68 74 78 80 81 94 95 97 100 
After sort, just show Top 15: 81 1 42 56 49 78 94 95 59 68 100 80 5 44 97 
```
