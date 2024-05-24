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


typedef struct LNode {
	Plant data;
	LNode* next;
}LNode, * LinkList;


void ReadFile(LinkList& L, string filename)
{//从文件中读取数据，存入链表L中
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

int exam(LinkList L, string name)
{//判断该植物名称name是否存在于plant.txt中
	LinkList p = L->next;
	while (p) {
		if (p->data.name == name) return 1;
		else p = p->next;
	}
	return 0;
}

bool Insert(LinkList& L, string filename)
{//增加植物信息，输入植物的名称、学名、分布地和详情描述信息，将该植物的基本信息添加到plant.txt中的最后
 //如果该植物名称存在于plant.txt中，返回false，否则，返回true
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out | ios::app);
	Plant temp;
	cin >> temp.name;
	int n, i;
	if (exam(L, temp.name)) return false;
	else {
		cin.ignore();
		getline(cin, temp.sname);
		cin >> n;
		cin.ignore();
		for (i = 0; i < n; i++) getline(cin, temp.place[i]);
		getline(cin, temp.detail);
	}
	ofile << endl<<temp.name << '#' << temp.sname << '#';
	for (i = 0; i < n - 1; i++) ofile << temp.place[i] << '@';
	ofile << temp.place[i] << '#' << temp.detail << endl;
	return true;
}

void InitList(LinkList& L)
{//构造一个空的单链表L
	L = new LNode;
	L->next = NULL;
}

void check(string filename)
{//读取文件最后一行内容，即新增植物信息 
	ifstream infile;
	infile.open(filename.c_str());    						//打开文件
	string line, last_line;
	while (getline(infile, line))
	{
		last_line = line;
	}
	cout << last_line << endl;
	infile.close();
}

int main() {
	LinkList L;
	string filename = "data_edit/plant.txt";
	InitList(L);
	//读plant.txt文件 
	ReadFile(L, filename);
	if (Insert(L, filename))
		check(filename);
	else
		cout << "增加失败\n";
	return 0;
}
