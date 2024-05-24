#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include <sstream>
using namespace std;
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
void InitList(LinkList& L) {
	//�����ʼ�� 
	L = new LNode;
	L->next = NULL;
}
void ListInsert(LinkList& L, int i, Plant temp) {
	//�ڴ�ͷ���ĵ�����L�е�i��λ�ò����½��
	LinkList p = L;
	int count=0;//������
	while (p) {
		//����ýڵ��next�Ǹò����λ��
		if (count+1 == i) {
			LinkList pn = new LNode;
			pn->data = temp;
			pn->next = p->next;
			p->next = pn;
			break;
		}
		else {
			count++;
			p = p->next;
		}
	}
}

int ReadFile(LinkList& L, string filename) {
	//��ȡplant.txt�ļ�������ListInsert������ÿ��ֲ�����ݲ�������
	//������ľ���ݵ����� 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count = 0;
	while (getline(infile, single)) {
		Plant p;
		count++;
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
	}
	infile.close();
	return count;
}
LNode* LocateElem(LinkList L, string key) {
	//�ڴ�ͷ���ĵ�����L�в���ֲ��ѧ��Ϊkey��Ԫ�� 
	LinkList p = L->next;
	int count = 0;
	while (p) {
		if (p->data.sname==key) return p;//ƥ���򷵻ظýڵ�
		else p = p->next;//��ƥ�����������
	}
}
double ASL_LinkList(LinkList L, int count) {
	//���ػ��������˳����ҵ�ASL 
	double n=0;
	LinkList p = L->next;
	for (int pos = 1; pos <= count; pos++) {
		p = L->next;
		int i = 1;
		while (p) {
			n++;
			if (i == pos) break;
			else {
				p = p->next; i++;
			}
		}
	}
	return n / count;
}

int main() {
	LinkList L;
	InitList(L);
	string filename = "plant.txt";
	int count = 0;
	count = ReadFile(L, filename);
	string sname;										//����Ҫ���ҵ�ֲ������ 
	getline(cin, sname);
	LNode* p = LocateElem(L, sname);
	if (p != NULL) {
		cout << "���ҳɹ���" << endl;
		cout << "���ƣ�" << p->data.name << endl;
		cout << "�ֲ��أ�";
		for (int j = 0; j < 100; j++)
			if (p->data.place[j] != "")
				cout << p->data.place[j] << " ";
		cout << endl;
		cout << "����������" << p->data.detail << endl;
		cout << "ƽ�����ҳ���ASLΪ��" << fixed << setprecision(2) << ASL_LinkList(L, count) << endl;
	}
	else {
		cout << "����ʧ�ܣ�" << endl;
	}
	return 0;
}
