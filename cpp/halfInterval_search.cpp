#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define MAX 10000
using namespace std;
struct Plant {											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct {            								//˳���
	Plant* plant;
	int length;
}SqList;
void InitList(SqList& L) {
	//˳����ʼ�� 
	L.plant = new Plant[MAX];
	L.length = 0;
}
void ListInsert(SqList& L, int i, Plant p) {
	//��˳���L�е�i��λ�ò����µ�ֲ��p 
	for (int j = L.length - 1; j >= i; j--) //����
		L.plant[j + 1] = L.plant[j];
	L.plant[i] = p;
}
void ReadFile(SqList& L, string filename) {
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳��� 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count = 0;
	while (getline(infile, single)) {
		Plant p;
		L.length++;
		//����plant��Ϣ
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p.name = element;//��������
			else if (flag == 2) p.sname = element;//����Ӣ����
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p.place[i++] = place;
				}
			}//����ֲ���
			else p.detail = element;//flag==4 ����ֲ������
			if (flag == 4) flag = 0;//����element������ɣ�flag����
			else flag++;//Ҫ����������һ��element��ʱ��flag++
		}
		ListInsert(L, count, p);//����ListInsert������ÿ��ֲ�����ݲ���˳��� 
		count++;
	}
	infile.close();
}
void Sort_Seq(SqList L) {
	//����ֲ��ѧ����˳���L��С�����������
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
	//��˳���L���۰����ֲ��ѧ������key������Ԫ��
	//���ҵ����򷵻ظ�Ԫ���ڱ��е��±꣬���򷵻�-1
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
	//���ػ���˳�����۰���ҵ�ASL 
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
	string sname;										//����Ҫ���ҵ�ֲ������ 
	getline(cin, sname);
	int flag = Search_Bin(L, sname);
	if (flag != -1) {
		cout << "���ҳɹ���" << endl;
		cout << "���ƣ�" << L.plant[flag].name << endl;
		cout << "�ֲ��أ�";
		for (int j = 0; j < 100; j++)
			if (L.plant[flag].place[j] != "")
				cout << L.plant[flag].place[j] << " ";
		cout << endl;
		cout << "����������" << L.plant[flag].detail << endl;
		cout << "ƽ�����ҳ���ASLΪ��" << fixed << setprecision(2) << ASL_Bin(L) << endl;
	}
	else {
		cout << "����ʧ�ܣ�" << endl;
	}
	return 0;
}
