#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define MAXSIZE 6490
using namespace std;
struct Plant{											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct{            								//顺序表
	Plant *p;									
	int length; 										//顺序表长度
}SqList;

void InitList(SqList& L) {
	//顺序表初始化
	L.p = new Plant[MAXSIZE + 1];
	L.length = 0;
}
void ListInsert(SqList& L, int i, Plant p) {
	//在顺序表L中第i+1个位置插入新的植物p
	//注：p[0]闲置 
	L.p[i] = p;
}
void ReadFile(SqList& L, string filename) {
	//读取plant.txt文件，调用ListInsert函数将每条植物数据插入顺序表 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
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
		ListInsert(L, L.length, p);//调用ListInsert函数将每条植物数据插入顺序表 
	}
	infile.close();
}
void BubbleSort(SqList &L,int &cmpNum,int &movNum){
	//对顺序表L做冒泡排序
	//定义一个变量flag用来标记某一趟排序是否发生交换
	//注：p[0]闲置
    int flag=1,j,m=L.length - 1;
	while((m>0)&&(flag==1)){
        flag=0;
        for (j = 1; j <=m ; j++) {
            cmpNum++;
			if (L.p[j].sname > L.p[j + 1].sname) {
                flag=1;
                movNum+=3;
				Plant temp = L.p[j];
				L.p[j] = L.p[j + 1];
				L.p[j + 1] = temp;
			}
	    }
        m--;
    }
		
}

int main() {
	SqList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	int cmpNum = 0;
	int movNum = 0;
	BubbleSort(L, cmpNum, movNum);
	int flag;
	cin >> flag;
	if (flag == 1) {
		cout << "总的关键字比较次数KCN为：" << cmpNum << endl;
		cout << "总的记录移动次数RMN为：" << movNum << endl;
	}

	int pos[3] = { 1022,2022,4022 };
	for (int k = 0; k < 3; k++) {
		int i = pos[k];
		cout << "输出顺序表中下标为" << i << "的植物信息" << endl;
		cout << "名称：" << L.p[i].name << endl;
		cout << "学名：" << L.p[i].sname << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (L.p[i].place[j] != "")
				cout << L.p[i].place[j] << " ";
		cout << endl;
		cout << "详情描述：" << L.p[i].detail << endl;
	}
	return 0;
}
