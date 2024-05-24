
#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include <sstream>
using namespace std;
#define MAX 10000
struct Plant {											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct {            								//顺序表
	Plant* plant;
	int length;
}SqList;
void InitList(SqList& L) {
	//顺序表初始化 
	L.plant = new Plant[MAX];
	L.length = 0;
}
void ListInsert(SqList& L, int i, Plant p) {
	//在顺序表L中第i个位置插入新的植物p 
	for (int j = L.length - 1; j >= i; j--) //后移
		L.plant[j + 1] = L.plant[j];
	L.plant[i] = p;
}
void ReadFile(SqList& L, string filename) {
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count=0;
	while (getline(infile, single)) {
		Plant p;
		L.length++;
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
		count++;
	}
	infile.close();
}
int Search_Seq(SqList L, string key) {
	//在顺序表L中顺序查找植物学名等于key的数据元素
	//若找到，则返回该元素在表中的下标，否则返回-1
	for (int i = 0; i < L.length; i++) {
		if (L.plant[i].sname == key) return i;
	}
	return -1;
}
double ASL_Seq(SqList L) {
	//返回基于顺序表的顺序查找的ASL 
	double n=0;
	for (int i = 0; i < L.length; i++) 
		for (int j = 0; j <= i; j++)
			n++;
	return n / L.length;
}

int main() {
	SqList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	string sname;										//输入要查找的植物学名 
	getline(cin, sname);
	int flag = Search_Seq(L, sname);
	if (flag != -1) {
		cout << "查找成功！" << endl;
		cout << "名称：" << L.plant[flag].name << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (L.plant[flag].place[j] != "")
				cout << L.plant[flag].place[j] << " ";
		cout << endl;
		cout << "详情描述：" << L.plant[flag].detail << endl;
		cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_Seq(L) << endl;
	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
