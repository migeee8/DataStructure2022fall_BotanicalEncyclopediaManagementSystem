#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define MAX 10000
using namespace std;
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
	int count = 0;
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
void Sort_Seq(SqList L) {
	//根据植物学名对顺序表L由小到大进行排序
	for(int i=0;i<L.length;i++)
		for (int j = 0; j < L.length - i - 1; j++) {
			if (L.plant[j].sname > L.plant[j + 1].sname) {
				Plant temp = L.plant[j];
				L.plant[j] = L.plant[j + 1];
				L.plant[j + 1] = temp;
			}
		}
}
int Search_Bin(SqList L, string key) {
	//在顺序表L中折半查找植物学名等于key的数据元素
	//若找到，则返回该元素在表中的下标，否则返回-1
	int low = 0,high=L.length-1,mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (L.plant[mid].sname == key) return mid;
		else if (L.plant[mid].sname > key) high = mid - 1;
		else low = mid + 1;
	}
	return -1;
}
double ASL_Bin(SqList L) {
	//返回基于顺序表的折半查找的ASL 
	double n=0;
	for (int i = 0; i < L.length; i++) {
		int low = 0, high = L.length - 1, mid;
		while (low <= high) {
			mid = (low + high) / 2;
			n++;
			if (mid == i) break;
			else if (mid>i) high = mid - 1;
			else low = mid + 1;
		}		
	}
	return n / L.length;
}


int main() {
	SqList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	Sort_Seq(L);
	string sname;										//输入要查找的植物名称 
	getline(cin, sname);
	int flag = Search_Bin(L, sname);
	if (flag != -1) {
		cout << "查找成功！" << endl;
		cout << "名称：" << L.plant[flag].name << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (L.plant[flag].place[j] != "")
				cout << L.plant[flag].place[j] << " ";
		cout << endl;
		cout << "详情描述：" << L.plant[flag].detail << endl;
		cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_Bin(L) << endl;
	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
