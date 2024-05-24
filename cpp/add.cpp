#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include <sstream>
using namespace std;
struct Plant
{
	//ֲ����Ϣ���� 
	string name;										//ֲ������ 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};


typedef struct LNode {
	Plant data;
	LNode* next;
}LNode, * LinkList;


void ReadFile(LinkList& L, string filename)
{//���ļ��ж�ȡ���ݣ���������L��
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	LinkList cur = L;
	while (getline(infile, single)) {
		LinkList p = new LNode;
		//�����½ڵ��data
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p->data.name = element;//��������
			else if (flag == 2) p->data.sname = element;//����Ӣ����
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p->data.place[i++] = place;
				}
			}//����ֲ���
			else p->data.detail = element;//flag==4 ����ֲ������
			if (flag == 4) flag = 0;//����element������ɣ�flag����
			else flag++;//Ҫ����������һ��element��ʱ��flag++
		}
		//���½ڵ��������
		p->next = NULL;
		cur->next = p;
		cur = p;
	}
}

int exam(LinkList L, string name)
{//�жϸ�ֲ������name�Ƿ������plant.txt��
	LinkList p = L->next;
	while (p) {
		if (p->data.name == name) return 1;
		else p = p->next;
	}
	return 0;
}

bool Insert(LinkList& L, string filename)
{//����ֲ����Ϣ������ֲ������ơ�ѧ�����ֲ��غ�����������Ϣ������ֲ��Ļ�����Ϣ��ӵ�plant.txt�е����
 //�����ֲ�����ƴ�����plant.txt�У�����false�����򣬷���true
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out | ios::app);
	Plant temp;
	cin >> temp.name;
	int n, i;
	if (exam(L, temp.name)) return false;
	else {
		cin.ignore();
		getline(cin, temp.sname);
		cin >> n;
		cin.ignore();
		for (i = 0; i < n; i++) getline(cin, temp.place[i]);
		getline(cin, temp.detail);
	}
	ofile << endl<<temp.name << '#' << temp.sname << '#';
	for (i = 0; i < n - 1; i++) ofile << temp.place[i] << '@';
	ofile << temp.place[i] << '#' << temp.detail << endl;
	return true;
}

void InitList(LinkList& L)
{//����һ���յĵ�����L
	L = new LNode;
	L->next = NULL;
}

void check(string filename)
{//��ȡ�ļ����һ�����ݣ�������ֲ����Ϣ 
	ifstream infile;
	infile.open(filename.c_str());    						//���ļ�
	string line, last_line;
	while (getline(infile, line))
	{
		last_line = line;
	}
	cout << last_line << endl;
	infile.close();
}

int main() {
	LinkList L;
	string filename = "data_edit/plant.txt";
	InitList(L);
	//��plant.txt�ļ� 
	ReadFile(L, filename);
	if (Insert(L, filename))
		check(filename);
	else
		cout << "����ʧ��\n";
	return 0;
}
