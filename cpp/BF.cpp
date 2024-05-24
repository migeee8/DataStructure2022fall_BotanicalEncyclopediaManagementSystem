#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string>
#define SSIZE 6000
#define TSIZE 1000
using namespace std;
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
{//读取文件，将数据存入链表L
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


int Is_EngChar(char c)
{//判断是否为英文字符，若是，则返回1，不是则返回0
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z')) || c == '=' || c == '!' || c == '?' || c == '_' || c == '{' || c == '}' || c == ',' || c == ';' || c == '-' || c == '/' || c == '(' || c == ')' || c == ':' || c == '×' || c == '[' || c == ']' || c == '.' || c == 'I')
		return 1;

	else
		return 0;
}

int Index_BF(string S, string T, int pos)
{//返回模式T在主串S中第pos个字符开始第一次出现的位置。若不存在，则返回值为0
 //其中，T非空，1≤pos≤S.length
 //为判断是否为汉字，需调用Is_EngChar函数
	string TS[SSIZE], TT[TSIZE];
	int slen = 1, tlen = 1;
	for (int i = 0; i < S.length(); i++) {
		if (Is_EngChar(S[i])) TS[slen++] = S[i];
		else {
			string a;
			TS[slen++].append(S, i, 2);
			i++;
		}
	}
	for (int i = 0; i < T.length(); i++) {
		if (Is_EngChar(T[i])) TT[tlen++] = T[i];
		else {
			TT[tlen++].append(T, i, 2);
			i++;
		}
	}
	slen--; tlen--;
	int i = pos, j = 1;
	while (i <= slen && j <= tlen) {
		if (TS[i] == TT[j]) { i++; j++; }
		else { i = i - j + 2; j = 1; }
		if (j > tlen)return i - tlen;
	}
	return 0;
}

void SearchInfo(LinkList L, string keyWord)
{//调用Index_BF算法进行关键信息查询
	LinkList p = L->next;
	while (p) {
		if (Index_BF(p->data.detail, keyWord, 1)) {
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
	string keyWord;
	cin >> keyWord;
	LinkList L;
	InitList(L);
	//读plant.txt文件
	string filename = "plant.txt";
	ReadFile(L, filename);
	SearchInfo(L, keyWord);
	return 0;
}

