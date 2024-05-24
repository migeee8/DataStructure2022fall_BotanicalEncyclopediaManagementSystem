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
int cmpNum=0;											//�Ƚϴ���
int movNum=0;											//�ƶ�����
void InitList(SqList& L) {
	//˳����ʼ��
	L.p = new Plant[MAXSIZE + 1];
	L.length = 0;
}
void ListInsert(SqList& L, int i, Plant p) {
	//��˳���L�е�i��λ�ò����µ�ֲ��p
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
int Partition(SqList& L, int low, int high) {
	//��˳���L�е��ӱ�p[low..high]����һ�����򣬷�������λ��
	//ע��p[0]���������¼
	//���ڴ˶ԱȽϴ������ƶ����������޸�
	string pivotkey;
	L.p[0] = L.p[low];  
	movNum++;
	pivotkey = L.p[low].sname;
	while (low < high)
	{
		while (low < high && L.p[high].sname >= pivotkey) {
			cmpNum++;
			--high;//�������ƶ����� ָ����ǰ
		}
		if(low < high)cmpNum++;
		L.p[low] = L.p[high];//�������� ����
		movNum++;
		while (low < high && L.p[low].sname <= pivotkey) {
			cmpNum++;
			++low;//�������ƶ����� ָ�����
		}
		if(low < high)cmpNum++;
		L.p[high] = L.p[low];//�������� ����
		movNum++;
	}
	L.p[low] = L.p[0];//low==high��λ�÷��ڱ�
	movNum++;
	return low;
}

void QSort(SqList& L, int low, int high) {
	//����ǰ�ó�ֵ��low=1; high=L.length;
	//��˳���L�е�������L.p[low..high]����������
	int pivotloc;
	if (low < high)//�ݹ����������low>=high
	{
		pivotloc = Partition(L, low, high);
		QSort(L, low, pivotloc - 1);
		QSort(L, pivotloc + 1, high);
	}

}
void QuickSort(SqList& L) {
	//��˳���L���������� 
	QSort(L, 1, L.length);
}

int main() {
	SqList L;
	InitList(L);
	string filename = "plant.txt";
	ReadFile(L, filename);
	QuickSort(L);
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
