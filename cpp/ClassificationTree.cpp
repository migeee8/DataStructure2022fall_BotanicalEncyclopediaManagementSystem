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
{///��ʼ�������������������Ϊ"ֲ���"
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
		BiTree t=FindNodeByName(BT, father);
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

void FindClass(BiTree& BT, string name)
{//����ֲ�����������ӽ絽���������Ϣ����Ҫ���ж���ݹ麯�����������õ�ջ�������ж��壩
	string str = name;
	BiTree temp;
	while (temp = FindParent(BT, str)) {
		if (!temp) break;
		else if (temp->left != NULL && temp->left->data == str) {//���parent����Ǹ��׽������������ֵܽڵ������
			if(temp->data=="ֲ���")cout << temp->data;
			else cout << temp->data << " ";
		}
		str = temp->data;//���� ��������Ѱ��
	}
	cout << endl;
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
		FindClass(BT, name);
	}
	return 0;
}
