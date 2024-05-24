#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include <sstream>
using namespace std;
using namespace std;
struct Plant {											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct LNode {          							//单链表 
	Plant data;
	struct LNode* next;
}LNode, * LinkList;
void InitList(LinkList& L) {
	//链表初始化 
	L = new LNode;
	L->next = NULL;
}
void ListInsert(LinkList& L, int i, Plant temp) {
	//在带头结点的单链表L中第i个位置插入新结点
	LinkList p = L;
	int count=0;//计数器
	while (p) {
		//如果该节点的next是该插入的位置
		if (count+1 == i) {
			LinkList pn = new LNode;
			pn->data = temp;
			pn->next = p->next;
			p->next = pn;
			break;
		}
		else {
			count++;
			p = p->next;
		}
	}
}

int ReadFile(LinkList& L, string filename) {
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入链表
	//返回树木数据的条数 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count = 0;
	while (getline(infile, single)) {
		Plant p;
		count++;
		//输入plant信息
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p.name = element;//输入名字
			else if (flag == 2) p.sname = element;//输入英文名
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p.place[i++] = place;
				}
			}//输入分布地
			else p.detail = element;//flag==4 输入植物详情
			if (flag == 4) flag = 0;//所有element输入完成，flag归零
			else flag++;//要继续输入下一个element的时候flag++
		}
		ListInsert(L, count, p);//调用ListInsert函数将每条植物数据插入顺序表 
	}
	infile.close();
	return count;
}
LNode* LocateElem(LinkList L, string key) {
	//在带头结点的单链表L中查找植物学名为key的元素 
	LinkList p = L->next;
	int count = 0;
	while (p) {
		if (p->data.sname==key) return p;//匹配则返回该节点
		else p = p->next;//不匹配继续向后查找
	}
}
double ASL_LinkList(LinkList L, int count) {
	//返回基于链表的顺序查找的ASL 
	double n=0;
	LinkList p = L->next;
	for (int pos = 1; pos <= count; pos++) {
		p = L->next;
		int i = 1;
		while (p) {
			n++;
			if (i == pos) break;
			else {
				p = p->next; i++;
			}
		}
	}
	return n / count;
}

int main() {
	LinkList L;
	InitList(L);
	string filename = "plant.txt";
	int count = 0;
	count = ReadFile(L, filename);
	string sname;										//输入要查找的植物名称 
	getline(cin, sname);
	LNode* p = LocateElem(L, sname);
	if (p != NULL) {
		cout << "查找成功！" << endl;
		cout << "名称：" << p->data.name << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (p->data.place[j] != "")
				cout << p->data.place[j] << " ";
		cout << endl;
		cout << "详情描述：" << p->data.detail << endl;
		cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_LinkList(L, count) << endl;
	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
