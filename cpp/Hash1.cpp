#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#define m 6600											//ɢ�б�ı� 
using namespace std;
struct Plant {											//ֲ����Ϣ���� 
	string name;										//���� 
	string sname;										//ѧ��
	string place[100];									//�ֲ��� 
	string detail;										//�������� 
};
typedef struct {            								//���ŵ�ַ��ɢ�б�Ĵ洢��ʾ
	Plant* key;
	int length;
}HashTable;
void InitHT(HashTable& HT) {
	//ɢ�б��ʼ�� 
	HT.key = new Plant[m];
}
int H(string sname) {
	//ʵ��ɢ�к������ַ���sname�и��ַ����±꣨��0��ʼ����ƽ�������ַ���Ӧ��ASCII��ֵ����Ӻ���6599ȡ�� 
	int sum = 0;
	for (int i = 0; i < sname.length(); i++) {
		sum += ((i) * (i) * int(sname[i]));
	}
	return sum % 6599;
}
void HTInsert(HashTable& HT, Plant p, int& sumCmp) {
	//��ɢ�б��в����µ�ֲ��p
	//�ڲ���Ĺ�����ͳ���ܵıȽϴ���sumCmp
	int H0 = H(p.sname);
	sumCmp++;
	if (HT.key[H0].sname == "") HT.key[H0] = p;
	else for (int i = 1; i < m; i++) {
		int Hi = (H0 + i) % m;
		sumCmp++;
		if (HT.key[Hi].sname == "") {
			HT.key[Hi] = p; break;
		}
	}
}
void ReadFile(HashTable& HT, int& sumCmp, string filename) {
	//��ȡplant.txt�ļ�������HT������ÿ��ֲ�����ݲ���ɢ�б� 
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
		HTInsert(HT, p, sumCmp);
	}
	infile.close();
}
int SearchHash(HashTable HT, string key) {
	//��ɢ�б�HT�в���ֲ��ѧ������key��Ԫ��
	//���ҵ����򷵻�ɢ�б�ĵ�Ԫ��ţ����򷵻�-1 
	int H0 = H(key);
	if (HT.key[H0].sname == "") return -1;
	else if(HT.key[H0].sname == key) return H0;
	else for (int i = 1; i < m; i++) {
		int Hi = (H0 + i) % m;
		if (HT.key[Hi].sname == "") return -1;
		else if (HT.key[Hi].sname == key) return Hi;
	}
	return -1;//���˵����
}
double ASL_HT(HashTable HT, int sumCmp) {
	//���ػ��ڿ��ŵ�ַ����ɢ�в��ҵ�ASL 
	double num=0,ave;
	for (int i = 0; i < m; i++) {
		if (HT.key[i].sname != "") num++;
	}
	ave = sumCmp / num;
	return ave;
}

int main() {
	HashTable HT;
	InitHT(HT);
	string filename = "plant.txt";
	int sumCmp = 0;										//�ڲ���Ĺ�����ͳ�ƱȽϴ��������ڼ���ASL 
	ReadFile(HT, sumCmp, filename);
	string sname;										//����Ҫ���ҵ�ֲ��ѧ�� 
	getline(cin, sname);
	int flag = SearchHash(HT, sname);
	if (flag != -1) {
		cout << "���ҳɹ���" << endl;
		cout << "���ƣ�" << HT.key[flag].name << endl;
		cout << "�ֲ��أ�";
		for (int j = 0; j < 100; j++)
			if (HT.key[flag].place[j] != "")
				cout << HT.key[flag].place[j] << " ";
		cout << endl;
		cout << "����������" << HT.key[flag].detail << endl;
		cout << "ƽ�����ҳ���ASLΪ��" << fixed << setprecision(2) << ASL_HT(HT, sumCmp) << endl;
	}
	else {
		cout << "����ʧ�ܣ�" << endl;
	}
	return 0;
}
