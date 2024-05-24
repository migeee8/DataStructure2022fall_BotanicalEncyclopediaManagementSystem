#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string>
using namespace std;

#define MAXLEN 5000			//串的最大长度

struct Plant
{
	//植物信息定义 
	string name;										//植物名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};


typedef struct LNode
{
	Plant data;    	   //结点的数据域   
	struct LNode* next; //指针域
}LNode, * LinkList;

void ReadFile(LinkList& L, string filename)
{//读取文件，将数据存入链表
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	LinkList cur = L;
	while (getline(infile, single)) {
		LinkList p = new LNode;
		//输入新节点的data
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p->data.name = element;//输入名字
			else if (flag == 2) p->data.sname = element;//输入英文名
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p->data.place[i++] = place;
				}
			}//输入分布地
			else p->data.detail = element;//flag==4 输入植物详情
			if (flag == 4) flag = 0;//所有element输入完成，flag归零
			else flag++;//要继续输入下一个element的时候flag++
		}
		//将新节点加入链表
		p->next = NULL;
		cur->next = p;
		cur = p;
	}
}


void GetNext(string pattern[], int next[], int newlength)
{//求模式串pattern的next函数值并存入数组next
	int i, j;
	i = 1; j = 0;
	next[1] = 0;
	while (i < newlength)
	{
		if (j == 0 || pattern[i]==pattern[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else j = next[j];
	}
}

int Is_EngChar(char c)
{//判断是否为英文字符，若是，则返回1，不是则返回0
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z')) || c == '=' || c == '!' || c == '?' || c == '_' || c == '{' || c == '}' || c == ',' || c == ';' || c == '-' || c == '/' || c == '(' || c == ')' || c == ':' || c == '×' || c == '[' || c == ']' || c == '.' || c == 'I')
		return 1;

	else
		return 0;
}
void GetChinese(string target, string ChiKey[], int* len)
{//将汉字存储在数组里,包括了汉字输入法下的标点
	for (int i = 0; i < target.length(); i++) {
		if (Is_EngChar(target[i])) ChiKey[(*len)++].append(target, i, 1);
		else {
			ChiKey[(*len)++].append(target, i, 2);
			i++;
		}
	}
}

int Index_KMP(string target[], string pattern[], int next[], int len1, int len2)
{//KMP匹配算法,target为主串，pattern为子串
	//匹配成功返回主串中所含子串第一次出现的位置，否则返回-1
	//调用GetNext函数获取模式串的next数组
	int i = 1, j = 1;
	while (i <= len1 && j <= len2)
	{
		if (j == 0 || target[i] == pattern[j]){
			++i;
			++j;
		}
		else j = next[j];
		if (j > len2) return i - len2;
	}
	return -1;
}

void SearchInfo(LinkList L, string keyword)
{//调用调用Index_KMP函数进行关键信息查询
	string  TT[MAXLEN];
	int *tlen,len2=1;
	tlen = &len2;
	int next[MAXLEN];
	GetChinese(keyword, TT, tlen);
	GetNext(TT, next, *tlen-1);
	LinkList p = L->next;
	while (p) {
		string TS[MAXLEN];
		int *slen,len1=1;
		slen = &len1;
		GetChinese(p->data.detail, TS, slen);
		if (Index_KMP(TS,TT,next,*slen-1,*tlen-1)!=-1) {
			cout << p->data.name << endl;
		}
		p = p->next;
	}
}



void InitList(LinkList& L)
{//构造一个空的单链表L
	L = new LNode;
	L->next = NULL;
}

int main()
{
	string keyword;
	cin >> keyword;
	LinkList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	int num = keyword.length();
	SearchInfo(L, keyword);
	return 0;
}
