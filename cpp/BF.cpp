#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string>
#define SSIZE 6000
#define TSIZE 1000
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
{//��ȡ�ļ��������ݴ�������L
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


int Is_EngChar(char c)
{//�ж��Ƿ�ΪӢ���ַ������ǣ��򷵻�1�������򷵻�0
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z')) || c == '=' || c == '!' || c == '?' || c == '_' || c == '{' || c == '}' || c == ',' || c == ';' || c == '-' || c == '/' || c == '(' || c == ')' || c == ':' || c == '��' || c == '[' || c == ']' || c == '.' || c == 'I')
		return 1;

	else
		return 0;
}

int Index_BF(string S, string T, int pos)
{//����ģʽT������S�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á��������ڣ��򷵻�ֵΪ0
 //���У�T�ǿգ�1��pos��S.length
 //Ϊ�ж��Ƿ�Ϊ���֣������Is_EngChar����
	string TS[SSIZE], TT[TSIZE];
	int slen = 1, tlen = 1;
	for (int i = 0; i < S.length(); i++) {
		if (Is_EngChar(S[i])) TS[slen++] = S[i];
		else {
			string a;
			TS[slen++].append(S, i, 2);
			i++;
		}
	}
	for (int i = 0; i < T.length(); i++) {
		if (Is_EngChar(T[i])) TT[tlen++] = T[i];
		else {
			TT[tlen++].append(T, i, 2);
			i++;
		}
	}
	slen--; tlen--;
	int i = pos, j = 1;
	while (i <= slen && j <= tlen) {
		if (TS[i] == TT[j]) { i++; j++; }
		else { i = i - j + 2; j = 1; }
		if (j > tlen)return i - tlen;
	}
	return 0;
}

void SearchInfo(LinkList L, string keyWord)
{//����Index_BF�㷨���йؼ���Ϣ��ѯ
	LinkList p = L->next;
	while (p) {
		if (Index_BF(p->data.detail, keyWord, 1)) {
			cout << p->data.name << endl;
		}
		p = p->next;
	}
}



void InitList(LinkList& L)
{//����һ���յĵ�����L
	L = new LNode;
	L->next = NULL;
}

int main()
{
	string keyWord;
	cin >> keyWord;
	LinkList L;
	InitList(L);
	//��plant.txt�ļ�
	string filename = "plant.txt";
	ReadFile(L, filename);
	SearchInfo(L, keyWord);
	return 0;
}

