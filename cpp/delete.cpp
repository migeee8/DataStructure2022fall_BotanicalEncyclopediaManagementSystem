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
} LNode, * LinkList;

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

void Deletep(LinkList& L, string name, string filename)
{//删除指定植物信息
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out);
	LinkList p=L;
	while (p->next) {
		if (p->next->data.name == name) {
			LinkList t = p->next;
			p->next = t->next;
			delete(t);
			break;
		}
		p = p->next;
	}
	p = L->next;
	while (p) {
		ofile << p->data.name << '#' << p->data.sname << '#';
		int i=0;
		while(p->data.place[i]!="#" )ofile << p->data.place[i++] << '@';
		ofile << p->data.place[i] << '#' << p->data.detail << endl;
		p=p->next;
	}
}

void InitList(LinkList& L)
{//构造一个空的单链表L
	L = new LNode;
	L->next = NULL;
}

int check(string name, string filename)
{//读取文件，判断是否删除成功 
	ifstream infile;
	infile.open(filename);
	string line;
	while (getline(infile, line))
	{						                            //读取一行植物数据 
		Plant temp;										//暂存每一行植物数据 
		stringstream ss(line);							//分割每一行植物数据的4个数据项	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp.name = s;
			if (temp.name == name)
			{
				infile.close();
				return 0;
			}
			flag++;
		}
	}
	infile.close();
	return 1;
}

string PlantInfo(string name, string filename)
{//查找待删除植物信息
	ifstream infile;
	infile.open(filename);    						//打开文件
	string line;
	while (getline(infile, line))
	{						//读取一行植物数据 
		string temp;										//暂存每一行植物数据 
		stringstream ss(line);							//分割每一行植物数据的4个数据项	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp = s;
			flag++;
			if (temp == name)
				return line;
			break;
		}
	}
	return "";
}

int main()
{
	string name;
	cin >> name;
	LinkList L;
	InitList(L);
	string filename = "data_edit/plant.txt";
	//读plant.txt文件 
	ReadFile(L, filename);
	string plant;
	if (PlantInfo(name, filename) != "")
	{
		plant = PlantInfo(name, filename);
		Deletep(L, name, filename);
		if (check(name, filename))                  //如果删除成功，输出已删除植物的全部信息     
			cout << plant << endl;
		else
			cout << "删除失败" << endl;
	}
	else
		cout << "删除失败" << endl;

	return 0;
}
