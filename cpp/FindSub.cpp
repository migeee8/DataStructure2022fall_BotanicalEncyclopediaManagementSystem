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
{//初始化二叉树，根结点数据为"植物界"
	BT = new TNode;
	BT->left = NULL;
	BT->right = NULL;
	BT->data = "植物界";
}


BiTree FindNodeByName(BiTree BT, string name)
{//根据植物名递归找到对应TNode结点，若不存在则返回NULL
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
{//根据文件名向树BT中添加结点
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
{//根据分类词（门、纲、目、科、属中的一个），输出隶属于该分类词的植物，空格分隔
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
	//文件路径需要改为自己本地路径
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
