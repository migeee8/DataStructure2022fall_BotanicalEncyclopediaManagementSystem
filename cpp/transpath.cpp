#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string> 
#define MVNum 34                           //��󶥵���
#define ERROR 0
#define MAX 9999
#define PathNUM 100
using namespace std;
int* allpath[PathNUM];
int pathnum = 0;
using namespace std;
typedef struct
{
    string vexs[MVNum];               	//�����
    int arcs[MVNum][MVNum];            	//�ڽӾ���
    int vexnum;                        	//ͼ���ܶ�����
    int arcnum;                        	//ͼ���ܱ���
}Graph;
int LocateVex(Graph G, string u)
{//�����򷵻�u�ڶ�����е��±꣬���򷵻�ERROR
    for (int i = 0; i < G.vexnum; i++)
        if (u == G.vexs[i]) return i;
    return ERROR;
}
string OrigialVex(Graph G, int u)
{//�����򷵻ض�������±�Ϊu��Ԫ��
    return G.vexs[u];
}
void InitGraph(Graph& G) {
    G.vexnum = 34;		//34��ʡ��������λ
    string place[] = { "����","�Ϻ�","���","����","���ɹ�","����","����","����","�½�","���","����","�ӱ�","ɽ��","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","�Ĵ�","����","����","����","����","�ຣ","̨��" };
    for (int i = 0; i < G.vexnum; i++) {
        G.vexs[i] = place[i];
    }
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MAX;
}
void CreateGraph(Graph& G, string filename)
{//�����ڽӾ����ʾ������distance.txt����������ͼG
 //��distance.txtʱҪ����filename����
    ifstream infile;
    infile.open(filename.c_str());
    string single;
    while (getline(infile, single)) {
        stringstream singlestream(single);
        string element;
        int flag = 1;
        int i, j;
        while (getline(singlestream, element, '#')) {
            if (flag == 1)	 i = LocateVex(G, element);
            if (flag == 2)	 j = LocateVex(G, element);
            if (flag == 3) {
                int n = atoi(element.c_str());
                G.arcs[i][j] = atoi(element.c_str());
                G.arcs[j][i] = G.arcs[i][j];
            }
            flag++;
        }
    }
    infile.close();
}

void mov(int* a, int* b) //��ά����allpath���м佻��
{
    int i = 0;
    while (++i) {
        a[i - 1] = b[i - 1];
        if (b[i - 1] == -1) break;
    }

}
void addpath(Graph G, int path[], int len) {
    int distance = 0;
    int i, j;
    //�Ȱ�path����浽��ά�����0�ŵ�Ԫ
    for (i = 0; i < len - 1; i++) {
        allpath[0][i + 1] = path[i];
        distance += G.arcs[path[i]][path[i + 1]];
    }
    allpath[0][0] = distance;//ÿһ�е�0�ŵ�Ԫ��distance
    allpath[0][i + 1] = path[i]; i++;
    allpath[0][i + 1] = -1;//�����ı��
    //����
    i = 1;
    while (distance > allpath[i][0] && allpath[i][0] > 0)//ȷ�ϲ���λ��
        i++;
    for (j = pathnum; j >= i; j--)//����
        mov(allpath[j + 1], allpath[j]);
    mov(allpath[j + 1], allpath[0]);
    /*for (int i = 0; i < len + 2; i++) {
        cout << allpath[j + 1][i] << " ";
        cout << endl;
    }*/
    pathnum++;//��·����1
}

//v��w n����󳤶� len��path[]����Ч����
void GoPath(Graph G, int v, int w, int path[], int n, int len) {
    //nС��0��ʾ������󳤶��ų��� ��������·��
    //n���ڵ���0��ʱ�� 
    if (n >= 0) {
        path[len++] = v;//����ǰ����ʼ�������path����
        if (v == w) {
            addpath(G, path, len);//�ߵ��յ��ҷ������� ����·�߼���allpath����
        }
        else//��û���յ�
        {
            int i, j;
            //����ǰ��ʼ������ڶ��㣨�������Ѿ��߹��ģ�������Ϊ��һ���ݹ����ʼ����
            //��󳤶Ȳ�����ȥ��ӦȨֵ
            for (i = 0; i < G.vexnum; i++) {
                if (G.arcs[v][i] < MAX) {
                    for (j = 0; j < len; j++)
                        if (path[j] == i) break;
                    if (j == len) {
                        GoPath(G, i, w, path, n - G.arcs[v][i], len);
                    }
                }
            }
        }
    }

}
void FindWay(Graph G, string p1, string p2, int n)
{//�ҵ�p1��p2���г���С��n��·������·�̴�С�������
 //�����õ��ݹ麯����ȫ�ֱ����������ж��岢�������
    int start, end;
    int i, j;
    start = LocateVex(G, p1);
    end = LocateVex(G, p2);
    int path[MVNum];
    int pathlen = 0;
    for (i = 0; i < PathNUM; i++) {
        allpath[i] = new int[MVNum] {0};
    }
    GoPath(G, start, end, path, n, pathlen);
    for (i = 1; i <= pathnum; i++) {
        for (j = 1; allpath[i][j + 1] != -1; j++)
            cout << OrigialVex(G, allpath[i][j]) << " ";
        cout << OrigialVex(G, allpath[i][j]) << endl;
    }
}


int main()
{
    string p1, p2;      	//�������p1���յ�p2
    int n;				//�ɽ��ܵ������
    Graph G;
    InitGraph(G);
    CreateGraph(G, "distance.txt");	//·�����Ϊ�Լ��ı���·��
    cin >> p1 >> p2 >> n;
    FindWay(G, p1, p2, n);
    return 0;
}
