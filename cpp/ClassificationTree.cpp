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
{///初始化二叉树，根结点数据为"植物界"
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
		// 如果当前结点的左子树或者右子树中存在要查找的结点，则当前结点为目标结点的父亲结点
		return BT;
	}
	// 递归查找左子树和右子树
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
{//根据植物名，输出其从界到属的类别信息，需要自行定义递归函数（若还需用到栈，请自行定义）
	string str = name;
	BiTree temp;
	while (temp = FindParent(BT, str)) {
		if (!temp) break;
		else if (temp->left != NULL && temp->left->data == str) {//如果parent结点是父亲结点则输出，是兄弟节点则不输出
			if(temp->data=="植物界")cout << temp->data;
			else cout << temp->data << " ";
		}
		str = temp->data;//迭代 继续向上寻找
	}
	cout << endl;
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
		FindClass(BT, name);
	}
	return 0;
}
