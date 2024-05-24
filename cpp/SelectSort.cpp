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
	//ע��p[0]���� 
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
void BubbleSort(SqList &L,int &cmpNum,int &movNum){
	//��˳���L��ð������
	//����һ������flag�������ĳһ�������Ƿ�������
	//ע��p[0]����
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
