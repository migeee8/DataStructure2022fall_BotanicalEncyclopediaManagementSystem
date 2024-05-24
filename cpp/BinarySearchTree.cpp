#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
using namespace std;
struct Plant {											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct BSTNode {									//���������� 
	Plant data;
	struct BSTNode* lchild, * rchild;
}BSTNode, * BSTree;
void InitBSTree(BSTree& T) {
	//������������ʼ�� 
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
	//��ȡplant.txt�ļ�������BSTreeInsert������ÿ��ֲ�����ݲ������������
	//������ľ���ݵ����� 
	ifstream infile;
	infile.open(filename.c_str());
	string single;
	int count = 0;
	while (getline(infile, single)) {
		Plant p;
		count++;
		//����plant��Ϣ
		stringstream singlestream(single);
		string element;
		int flag = 1;
		while (getline(singlestream, element, '#')) {
			if (flag == 1) p.name = element;//��������
			else if (flag == 2) p.sname = element;//����Ӣ����
			else if (flag == 3) {
				int i = 0;
				stringstream placestream(element);
				string place;
				while (getline(placestream, place, '@')) {
					p.place[i++] = place;
				}
			}//����ֲ���
			else p.detail = element;//flag==4 ����ֲ������
			if (flag == 4) flag = 0;//����element������ɣ�flag����
			else flag++;//Ҫ����������һ��element��ʱ��flag++
		}
		BSTreeInsert(T,p);//�µĽ��������������
	}
	infile.close();
	return count;
}
void InOrderTraverse(BSTree T) {
	//�������������T�ĵݹ��㷨
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->data.sname << endl;
		InOrderTraverse(T->rchild);
	}
}
BSTree SearchBST(BSTree T, string key) {
	//�ڸ�ָ��T��ָ�����������еݹ�ز���ĳֲ��ѧ������key������Ԫ��
	//�����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
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
	//���ػ��ڶ������������ҵ�ASL
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
	InOrderTraverse(T);									//��������������������Ƿ񴴽��ɹ� 
	string sname;										//����Ҫ���ҵ�ֲ��ѧ�� 
	getline(cin, sname);
	BSTNode* t = SearchBST(T, sname);
	if (t != NULL) {
		cout << "���ҳɹ���" << endl;
		cout << "���ƣ�" << t->data.name << endl;
		cout << "�ֲ��أ�";
		for (int j = 0; j < 100; j++)
			if (t->data.place[j] != "")
				cout << t->data.place[j] << " ";
		cout << endl;
		cout << "����������" << t->data.detail << endl;
		cout << "ƽ�����ҳ���ASLΪ��" << fixed << setprecision(2) << ASL_BSTree(T, count) << endl;
	}
	else {
		cout << "����ʧ�ܣ�" << endl;
	}
	return 0;
}
