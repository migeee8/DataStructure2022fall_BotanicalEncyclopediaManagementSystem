#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
using namespace std;
#define MAX 1000
typedef struct TNode {
	string data;
	struct TNode* left;
	struct TNode* right;
}TNode, * BiTree;

void InitTree(BiTree& BT)
{//��ʼ�������������������Ϊ"ֲ���"
	BT = new TNode;
	BT->left = NULL;
	BT->right = NULL;
	BT->data = "ֲ���";
}


BiTree FindNodeByName(BiTree BT, string name)
{//����ֲ�����ݹ��ҵ���ӦTNode��㣬���������򷵻�NULL
	if (BT) {
		if (name == BT->data) return BT;
		else {
			BiTree temp;
			temp = FindNodeByName(BT->left, name);
			if (temp != NULL) return temp;
			else return FindNodeByName(BT->right, name);
		}
	}
	else return NULL;
}

void CreateByFile(BiTree& BT, string filename)
{//�����ļ�������BT����ӽ��
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	while (getline(infile, single)) {
		stringstream singlestream(single);
		string element;
		string leaf, father;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) leaf = element;
			else father = element;
			flag++;
		}
		BiTree tnew = new TNode;
		tnew->data = leaf;
		tnew->left = NULL;
		tnew->right = NULL;
		BiTree t = FindNodeByName(BT, father);
		if (t->left == NULL) {
			t->left = tnew;
		}
		else {
			BiTree cur = t->left;
			while (cur) {
				if (cur->right == NULL) {
					cur->right = tnew; break;
				}
				else cur = cur->right;
			}
		}
	}
	infile.close();
}

void findLeaf(BiTree& BT,string* leave,int& n) {
	if (BT) {
		if (BT->left == NULL) {
			BiTree p = BT;
			while (p) {
				leave[n++] = p->data;
				p = p->right;
			}
			//if (n = 9)
			//	cout << " ";
			return;
		}
		else {
			findLeaf(BT->left, leave, n);
			findLeaf(BT->right, leave, n);
		}
	}
}

void FindSubLeaf(BiTree& BT, string name)
{//���ݷ���ʣ��š��١�Ŀ���ơ����е�һ��������������ڸ÷���ʵ�ֲ��ո�ָ�
	string* leave;
	leave = new string[MAX];
	int n = 0, i = 0;
	BiTree target;
	target = FindNodeByName(BT, name);
	if(target->left)findLeaf(target->left, leave,n);
	for (i = 0; i < n - 1; i++) {
		cout << leave[i] << " ";
	}
	cout<< leave[i] << endl;
}


void CreateTree(BiTree& BT) {
	//�ļ�·����Ҫ��Ϊ�Լ�����·��
	CreateByFile(BT, "relation6.txt");
	CreateByFile(BT, "relation5.txt");
	CreateByFile(BT, "relation4.txt");
	CreateByFile(BT, "relation3.txt");
	CreateByFile(BT, "relation2.txt");
	CreateByFile(BT, "relation1.txt");
}

int main() {
	BiTree BT;
	InitTree(BT);
	CreateTree(BT);
	while (1) {
		string name;
		cin >> name;
		if (name == "0")
			break;
		FindSubLeaf(BT, name);
	}
	return 0;
}
