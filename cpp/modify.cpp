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


typedef struct LNode
{
	Plant data;    	   //����������   
	struct LNode* next; //ָ����
}LNode, * LinkList;

void ReadFile(LinkList& L, string filename)
{
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
				p->data.place[i] = "#";
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

bool Changep(LinkList& L, string name, string details, string filename)
{//�޸�ֲ����Ϣ
 //����ֲ�����ƴ�����plant.txt�У�����true������,����false
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out);
	LinkList p = L->next;
	int flag=0;
	while (p) {
		if (p->data.name == name) {
			p->data.detail = details;
			flag = 1;
			break;
		}
		p = p->next;
	}
	if (flag == 0) return false;
	p = L->next;
	while (p) {
		ofile << p->data.name << '#' << p->data.sname << '#';
		int i = 0;
		while (p->data.place[i] != "#")ofile << p->data.place[i++] << '@';
		ofile << p->data.place[i] << '#' << p->data.detail << endl;
		p = p->next;
	}
	return true;
}

void InitList(LinkList& L)
{//����һ���յĵ�����L
	L = new LNode;
	L->next = NULL;
}

void check(string name, string filename)
{//��ȡ�ļ�������޸ĺ�ֲ����Ϣ 
	ifstream infile;
	infile.open(filename);    						//���ļ�
	string line;
	while (getline(infile, line))
	{						//��ȡһ��ֲ������ 
		Plant temp;										//�ݴ�ÿһ��ֲ������ 
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp.name = s;
			if (flag == 1)	temp.sname = s;
			if (flag == 2)
			{
				stringstream ssplace(s);				//����ÿһ��ֲ�����ݵķֲ��� 
				string place;
				int placenum = 0;
				while (getline(ssplace, place, '@'))
				{
					temp.place[placenum] = place;
					placenum++;
				}
			}
			if (flag == 3)	temp.detail = s;
			if (temp.name == name)
			{
				cout << line << endl;
				break;
			}
			flag++;
		}
	}
	infile.close();
}

int main()
{
	string name, details;
	cin >> name >> details;
	string filename = "data_edit/plant.txt";
	LinkList L;
	InitList(L);
	//��plant.txt�ļ�
	ReadFile(L, filename);
	if (Changep(L, name, details, filename))
		check(name, filename);
	else
		cout << "�޸�ʧ��" << endl;
	return 0;
}



