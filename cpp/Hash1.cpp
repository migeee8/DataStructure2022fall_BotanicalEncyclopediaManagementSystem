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
typedef struct {            								//开放地址法散列表的存储表示
	Plant* key;
	int length;
}HashTable;
void InitHT(HashTable& HT) {
	//散列表初始化 
	HT.key = new Plant[m];
}
int H(string sname) {
	//实现散列函数：字符串sname中各字符的下标（从0开始）的平方乘以字符对应的ASCII码值，相加后与6599取余 
	int sum = 0;
	for (int i = 0; i < sname.length(); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 6599;
}
void HTInsert(HashTable& HT, Plant p, int& sumCmp) {
	//往散列表中插入新的植物p
	//在插入的过程中统计总的比较次数sumCmp
	int H0 = H(p.sname);
	sumCmp++;
	if (HT.key[H0].sname == "") HT.key[H0] = p;
	else for (int i = 1; i < m; i++) {
		int Hi = (H0 + i) % m;
		sumCmp++;
		if (HT.key[Hi].sname == "") {
			HT.key[Hi] = p; break;
		}
	}
}
void ReadFile(HashTable& HT, int& sumCmp, string filename) {
	//读取plant.txt文件，调用HT函数将每条植物数据插入散列表 
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
		HTInsert(HT, p, sumCmp);
	}
	infile.close();
}
int SearchHash(HashTable HT, string key) {
	//在散列表HT中查找植物学名等于key的元素
	//若找到，则返回散列表的单元标号，否则返回-1 
	int H0 = H(key);
	if (HT.key[H0].sname == "") return -1;
	else if(HT.key[H0].sname == key) return H0;
	else for (int i = 1; i < m; i++) {
		int Hi = (H0 + i) % m;
		if (HT.key[Hi].sname == "") return -1;
		else if (HT.key[Hi].sname == key) return Hi;
	}
	return -1;//满了的情况
}
double ASL_HT(HashTable HT, int sumCmp) {
	//返回基于开放地址法的散列查找的ASL 
	double num=0,ave;
	for (int i = 0; i < m; i++) {
		if (HT.key[i].sname != "") num++;
	}
	ave = sumCmp / num;
	return ave;
}

int main() {
	HashTable HT;
	InitHT(HT);
	string filename = "plant.txt";
	int sumCmp = 0;										//在插入的过程中统计比较次数，便于计算ASL 
	ReadFile(HT, sumCmp, filename);
	string sname;										//输入要查找的植物学名 
	getline(cin, sname);
	int flag = SearchHash(HT, sname);
	if (flag != -1) {
		cout << "查找成功！" << endl;
		cout << "名称：" << HT.key[flag].name << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (HT.key[flag].place[j] != "")
				cout << HT.key[flag].place[j] << " ";
		cout << endl;
		cout << "详情描述：" << HT.key[flag].detail << endl;
		cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_HT(HT, sumCmp) << endl;
	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
