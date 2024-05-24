#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include <sstream>
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
{
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
				p->data.place[i] = "#";
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

bool Changep(LinkList& L, string name, string details, string filename)
{//修改植物信息
 //若该植物名称存在于plant.txt中，返回true，否则,返回false
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out);
	LinkList p = L->next;
	int flag=0;
	while (p) {
		if (p->data.name == name) {
			p->data.detail = details;
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0) return false;
	p = L->next;
	while (p) {
		ofile << p->data.name << '#' << p->data.sname << '#';
		int i = 0;
		while (p->data.place[i] != "#")ofile << p->data.place[i++] << '@';
		ofile << p->data.place[i] << '#' << p->data.detail << endl;
		p = p->next;
	}
	return true;
}

void InitList(LinkList& L)
{//构造一个空的单链表L
	L = new LNode;
	L->next = NULL;
}

void check(string name, string filename)
{//读取文件，输出修改后植物信息 
	ifstream infile;
	infile.open(filename);    						//打开文件
	string line;
	while (getline(infile, line))
	{						//读取一行植物数据 
		Plant temp;										//暂存每一行植物数据 
		stringstream ss(line);							//分割每一行植物数据的4个数据项	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp.name = s;
			if (flag == 1)	temp.sname = s;
			if (flag == 2)
			{
				stringstream ssplace(s);				//保存每一行植物数据的分布地 
				string place;
				int placenum = 0;
				while (getline(ssplace, place, '@'))
				{
					temp.place[placenum] = place;
					placenum++;
				}
			}
			if (flag == 3)	temp.detail = s;
			if (temp.name == name)
			{
				cout << line << endl;
				break;
			}
			flag++;
		}
	}
	infile.close();
}

int main()
{
	string name, details;
	cin >> name >> details;
	string filename = "data_edit/plant.txt";
	LinkList L;
	InitList(L);
	//读plant.txt文件
	ReadFile(L, filename);
	if (Changep(L, name, details, filename))
		check(name, filename);
	else
		cout << "修改失败" << endl;
	return 0;
}



