#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
using namespace std;
struct Plant {											//植物信息定义 
	string name;										//名称 
	string sname;										//学名
	string place[100];									//分布地 
	string detail;										//详情描述 
};
typedef struct BSTNode {									//二叉排序树 
	Plant data;
	struct BSTNode* lchild, * rchild;
}BSTNode, * BSTree;
void InitBSTree(BSTree& T) {
	//二叉排序树初始化 
	T = new BSTNode;
	T->lchild = NULL;
	T->rchild = NULL;
}
void BSTreeInsert(BSTree& T, Plant temp) {
	BSTree tn = new BSTNode;
	tn->data = temp;
	tn->lchild = NULL;
	tn->rchild = NULL;
	if (T->data.sname=="") 
		T = tn;
	else {
		BSTree cur = T;
		while (cur) {
			if (temp.sname > cur->data.sname) {
				if (!cur->rchild) {
					cur->rchild = tn; break;
				}
				else cur = cur->rchild;
			}
			else {
				if (!cur->lchild) {
					cur->lchild = tn; break;
				}
				else cur = cur->lchild;
			}
		}
		
	}
}
int ReadFile(BSTree& T, string filename) {
	//读取plant.txt文件，调用BSTreeInsert函数将每条植物数据插入二叉排序树
	//返回树木数据的条数 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count = 0;
	while (getline(infile, single)) {
		Plant p;
		count++;
		//输入plant信息
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p.name = element;//输入名字
			else if (flag == 2) p.sname = element;//输入英文名
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p.place[i++] = place;
				}
			}//输入分布地
			else p.detail = element;//flag==4 输入植物详情
			if (flag == 4) flag = 0;//所有element输入完成，flag归零
			else flag++;//要继续输入下一个element的时候flag++
		}
		BSTreeInsert(T,p);//新的结点插入二叉排序树
	}
	infile.close();
	return count;
}
void InOrderTraverse(BSTree T) {
	//中序遍历二叉树T的递归算法
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->data.sname << endl;
		InOrderTraverse(T->rchild);
	}
}
BSTree SearchBST(BSTree T, string key) {
	//在根指针T所指二叉排序树中递归地查找某植物学名等于key的数据元素
	//若查找成功，则返回指向该数据元素结点的指针，否则返回空指针
	BSTree cur = T;
	while (cur) {
		if (key == cur->data.sname) return cur;
		else if (key > cur->data.sname)
			cur=cur->rchild;
		else cur = cur->lchild;
	}
	return NULL;
}

void PathSum(BSTree T,int n,double&sum) {
	if (T) {
		n++;
		sum += n;
		PathSum(T->lchild, n, sum);
		PathSum(T->rchild, n, sum);
	}
}

double ASL_BSTree(BSTree T, int count) {
	//返回基于二叉排序树查找的ASL
	int n = 0;
	double sum = 0;
	PathSum(T, n, sum);
	return sum / count;
}


int main() {
	BSTree T;
	InitBSTree(T);
	int count = 0;
	string filename = "plant.txt";
	count = ReadFile(T, filename);
	InOrderTraverse(T);									//输出二叉排序树，测试是否创建成功 
	string sname;										//输入要查找的植物学名 
	getline(cin, sname);
	BSTNode* t = SearchBST(T, sname);
	if (t != NULL) {
		cout << "查找成功！" << endl;
		cout << "名称：" << t->data.name << endl;
		cout << "分布地：";
		for (int j = 0; j < 100; j++)
			if (t->data.place[j] != "")
				cout << t->data.place[j] << " ";
		cout << endl;
		cout << "详情描述：" << t->data.detail << endl;
		cout << "平均查找长度ASL为：" << fixed << setprecision(2) << ASL_BSTree(T, count) << endl;
	}
	else {
		cout << "查找失败！" << endl;
	}
	return 0;
}
