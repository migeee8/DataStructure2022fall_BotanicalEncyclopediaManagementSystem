#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define m 6600											//ɢ�б�ı� 
using namespace std;
struct Plant {											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//��������
};
typedef struct LNode {          							//������ 
	Plant data;
	struct LNode* next;
}LNode, * LinkList;
LinkList H[m];                                         	//����ַ��ɢ�б�Ĵ洢��ʾ��m�������� 	

void InitList() {
	//�����ʼ�� 
	for (int i = 0; i < m; i++) {
		H[i] = new LNode;
		H[i]->next = NULL;
	}
}
int Hash(string sname) {
	//ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���6599ȡ�� 
	int sum = 0;
	for (int i = 0; i < sname.length(); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 6599;
}
void ListInsert(Plant p, int& sumCmp) {
	//��ɢ�б��в����µ�ֲ��p
	//�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
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
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ���˳���
	//������ľ���ݵ�����  
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	double plantnum=0;
	while (getline(infile, single)) {
		Plant p;
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
		plantnum++;
		ListInsert(p,sumCmp);
	}
	infile.close();
	return plantnum;
}
int SearchHL(string key) {
	//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
	//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1 
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
	//���ػ�������ַ����ɢ�в��ҵ�ASL 
	double ave= sumCmp / (count*1.00);
	return ave;
}


int main() {
	InitList();
	string filename = "plant.txt";
	int count = 0; 										//��¼ֲ�����ݵ�����
	int sumCmp = 0;										//�ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL 
	count = ReadFile(sumCmp, filename);
	string sname;										//����Ҫ���ҵ�ֲ��ѧ�� 
	getline(cin, sname);
	int flag = SearchHL(sname);
	if (flag != -1) {
		LinkList p = H[flag]->next;						//���ҳɹ�����pָ������ͷ���
		while (p) {
			if (p->data.sname == sname) {					//���������Ϣ 
				cout << "���ҳɹ���" << endl;
				cout << "���ƣ�" << p->data.name << endl;
				cout << "�ֲ��أ�";
				for (int j = 0; j < 100; j++)
					if (p->data.place[j] != "")
						cout << p->data.place[j] << " ";
				cout << endl;
				cout << "����������" << p->data.detail << endl;
				cout << "ƽ�����ҳ���ASLΪ��" << fixed << setprecision(2) << ASL_HL(sumCmp, count) << endl;
				break;
			}
			p = p->next;
		}

	}
	else {
		cout << "����ʧ�ܣ�" << endl;
	}
	return 0;
}
