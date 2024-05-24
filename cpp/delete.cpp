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
} LNode, * LinkList;

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

void Deletep(LinkList& L, string name, string filename)
{//ɾ��ָ��ֲ����Ϣ
	ofstream ofile;
	ofile.open(filename.c_str(), ios::out);
	LinkList p=L;
	while (p->next) {
		if (p->next->data.name == name) {
			LinkList t = p->next;
			p->next = t->next;
			delete(t);
			break;
		}
		p = p->next;
	}
	p = L->next;
	while (p) {
		ofile << p->data.name << '#' << p->data.sname << '#';
		int i=0;
		while(p->data.place[i]!="#" )ofile << p->data.place[i++] << '@';
		ofile << p->data.place[i] << '#' << p->data.detail << endl;
		p=p->next;
	}
}

void InitList(LinkList& L)
{//����һ���յĵ�����L
	L = new LNode;
	L->next = NULL;
}

int check(string name, string filename)
{//��ȡ�ļ����ж��Ƿ�ɾ���ɹ� 
	ifstream infile;
	infile.open(filename);
	string line;
	while (getline(infile, line))
	{						                            //��ȡһ��ֲ������ 
		Plant temp;										//�ݴ�ÿһ��ֲ������ 
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp.name = s;
			if (temp.name == name)
			{
				infile.close();
				return 0;
			}
			flag++;
		}
	}
	infile.close();
	return 1;
}

string PlantInfo(string name, string filename)
{//���Ҵ�ɾ��ֲ����Ϣ
	ifstream infile;
	infile.open(filename);    						//���ļ�
	string line;
	while (getline(infile, line))
	{						//��ȡһ��ֲ������ 
		string temp;										//�ݴ�ÿһ��ֲ������ 
		stringstream ss(line);							//�ָ�ÿһ��ֲ�����ݵ�4��������	
		string s;
		int flag = 0;
		while (getline(ss, s, '#'))
		{
			if (flag == 0)	temp = s;
			flag++;
			if (temp == name)
				return line;
			break;
		}
	}
	return "";
}

int main()
{
	string name;
	cin >> name;
	LinkList L;
	InitList(L);
	string filename = "data_edit/plant.txt";
	//��plant.txt�ļ� 
	ReadFile(L, filename);
	string plant;
	if (PlantInfo(name, filename) != "")
	{
		plant = PlantInfo(name, filename);
		Deletep(L, name, filename);
		if (check(name, filename))                  //���ɾ���ɹ��������ɾ��ֲ���ȫ����Ϣ     
			cout << plant << endl;
		else
			cout << "ɾ��ʧ��" << endl;
	}
	else
		cout << "ɾ��ʧ��" << endl;

	return 0;
}
