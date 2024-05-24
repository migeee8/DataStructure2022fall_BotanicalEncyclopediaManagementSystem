#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
using namespace std;
#define MAX 100
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
{//�������ݵݹ��ҵ���Ӧ��㣬���������򷵻�NULL
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

BiTree FindParent(BiTree& BT, string name) {
	if (BT == NULL) {
		return NULL;
	}
	if (BT->left != NULL && BT->left->data == name ||
		BT->right != NULL && BT->right->data == name) {
		// �����ǰ���������������������д���Ҫ���ҵĽ�㣬��ǰ���ΪĿ����ĸ��׽��
		return BT;
	}
	// �ݹ������������������
	BiTree left = FindParent(BT->left, name);
	if (left != NULL) {
		return left;
	}
	BiTree right = FindParent(BT->right, name);
	if (right != NULL) {
		return right;
	}
	return NULL;
}

void FindBrother(BiTree& BT, string name)
{//����ֲ������������ֵ���Ϣ���ո�ָ�
	string str = name;
	string* bro;//����װһ���ֵܽ��data��string����
	bro = new string[MAX];
	int n = 0;
	BiTree temp;
	while (temp = FindParent(BT, str)) {
		if (!temp) break;
		else if (temp->left != NULL && temp->left->data == str) {//�ҵ���һ�����׽ڵ�
			break;
		}
		str = temp->data;//���� ��������Ѱ��
	}
	BiTree p = temp->left;
	while (p) {
		if (p->data != name) bro[n++] = p->data;//������ֵܽڵ� ��������
		p = p->right;
	}
	int i;
	for (i = 0; i < n - 1; i++) {
		cout << bro[i] << " ";
	}
	cout << bro[i] << endl;
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
		FindBrother(BT, name);
	}
	return 0;
}
