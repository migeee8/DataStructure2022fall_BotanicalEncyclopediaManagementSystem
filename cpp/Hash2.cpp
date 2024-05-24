#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define m 6600											//散列表的表长 
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
LinkList H[m];                                         	//链地址法散列表的存储表示，m个单链表 	

void InitList() {
	//链表初始化 
	for (int i = 0; i < m; i++) {
		H[i] = new LNode;
		H[i]->next = NULL;
	}
}
int Hash(string sname) {
	//实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与6599取余 
	int sum = 0;
	for (int i = 0; i < sname.length(); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 6599;
}
void ListInsert(Plant p, int& sumCmp) {
	//往散列表中插入新的植物p
	//在插入的过程中统计总的比较次数sumCmp
	int H0 = Hash(p.sname);
	LinkList pnew=new LNode;
	pnew->data = p;
	pnew->next = NULL;
	LinkList cur = H[H0];
	while (cur->next) {
		cur = cur->next;
		sumCmp++;
	}
	sumCmp++;
	cur->next = pnew;
}
int ReadFile(int& sumCmp, string filename) {
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表
	//返回树木数据的条数  
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	double plantnum=0;
	while (getline(infile, single)) {
		Plant p;
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
		plantnum++;
		ListInsert(p,sumCmp);
	}
	infile.close();
	return plantnum;
}
int SearchHL(string key) {
	//在散列表HT中查找植物学名等于key的元素
	//若找到，则返回散列表的单元标号，否则返回-1 
	int H0 = Hash(key);
	LinkList cur = H[H0]->next;
	if (!cur) return -1;
	else while (cur) {
		if (cur->data.sname == key) return H0;
		else cur=cur->next;
	}
	return -1;
}
double ASL_HL(int sumCmp, int count) {
	//返回基于链地址法的散列查找的ASL 
	double ave= sumCmp / (count*1.00);
	return ave;
}


int main() {
	InitList();
	string filename = "plant.txt";
	int count = 0; 										//记录植物数据的条数
	int sumCmp = 0;										//在插入的过程中统计比较次数，便于计算ASL 
	count = ReadFile(sumCmp, filename);
	string sname;										//输入要查找的植物学名 
	getline(cin, sname);
	int flag = SearchHL(sname);
	if (flag != -1) {
		LinkList p = H[flag]->next;						//查找成功，将p指向单链表头结点
		while (p) {
			if (p->data.sname == sname) {					//输出其他信息 
				cout << "查找成功！" << endl;
				cout << "名称：" << p->data.name << endl;
				cout << "分布地：";
				for (int j = 0; j < 100; j++)
					if (p->data.place[j] != "")
						cout << p->data.place[j] << " ";
				cout << endl;
				cout << "详情描述：" << p->data.detail << endl;
				cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_HL(sumCmp, count) << endl;
				break;
			}
			p = p->next;
		}

	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
