#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define MAXSIZE 6490
using namespace std;
struct Plant{											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct{            								//˳���
	Plant *p;									
	int length; 										//˳�����
}SqList;

void InitList(SqList& L) {
	//˳����ʼ��
	L.p = new Plant[MAXSIZE + 1];
	L.length = 0;
}
void ListInsert(SqList& L, int i, Plant p) {
	//��˳���L�е�i+1��λ�ò����µ�ֲ��p
	//ע��p[0]�����ڱ���Ԫ 
	L.p[i] = p;
}
void ReadFile(SqList& L, string filename) {
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳��� 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
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
		ListInsert(L, L.length, p);//����ListInsert������ÿ��ֲ�����ݲ���˳��� 
	}
	infile.close();
}
void BInsertSort(SqList& L, int& cmpNum, int& movNum) {
	//��˳���L���۰��������
	//ע��p[0]�����ڱ���Ԫ 
	int i, j;
	for (i = 2; i <= L.length; i++) {
		L.p[0] = L.p[i];
		movNum++;
		int low = 1;
		int high = i - 1;
		int mid;
		while (low <= high) {
			cmpNum++;
			mid = (low + high) / 2;
			if (L.p[mid].sname > L.p[0].sname) {
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= low; j--) {
			L.p[j + 1] = L.p[j];
			movNum++;
		}
		L.p[j + 1] = L.p[0];
		movNum++;
	}
}

int main() {
	SqList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	int cmpNum = 0;
	int movNum = 0;
	BInsertSort(L, cmpNum, movNum);
	int flag;
	cin >> flag;
	if (flag == 1) {
		cout << "�ܵĹؼ��ֱȽϴ���KCNΪ��" << cmpNum << endl;
		cout << "�ܵļ�¼�ƶ�����RMNΪ��" << movNum << endl;
	}

	int pos[3] = { 1022,2022,4022 };
	for (int k = 0; k < 3; k++) {
		int i = pos[k];
		cout << "���˳������±�Ϊ" << i << "��ֲ����Ϣ" << endl;
		cout << "���ƣ�" << L.p[i].name << endl;
		cout << "ѧ����" << L.p[i].sname << endl;
		cout << "�ֲ��أ�";
		for (int j = 0; j < 100; j++)
			if (L.p[i].place[j] != "")
				cout << L.p[i].place[j] << " ";
		cout << endl;
		cout << "����������" << L.p[i].detail << endl;
	}
	return 0;
}
