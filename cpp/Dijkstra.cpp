#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string> 
#define MVNum 34                           //��󶥵���
#define ERROR 0
#define Infinite 9999
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

void InitGraph(Graph& G) {
    G.vexnum = 34;		//34��ʡ��������λ
    string place[] = { "����","�Ϻ�","���","����","���ɹ�","����","����","����","�½�","���","����","�ӱ�","ɽ��","����","����","������","����","�㽭","����","����","����","ɽ��","����","����","����","�㶫","����","�Ĵ�","����","����","����","����","�ຣ","̨��" };
    for (int i = 0; i < G.vexnum; i++)
        G.vexs[i] = place[i];
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = Infinite;
}
void CreateGraph(Graph& G, string filename)
{//�����ڽӾ����ʾ������distance.txt����������ͼG
 //��distance.txtʱҪʹ��filename����
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
int Dijkstra(Graph G, string v1, string v2)
{//����Dijkstra�㷨��v1��v2�����·��������·������
    int D[MVNum];//��¼Դ�㵽��Ӧ����·������
    bool S[MVNum];//��¼��Ӧ�����Ƿ��ѱ�ȷ����̾���
    int Path[MVNum];//��¼��Ӧ�����ǰ������
    int i, j;
    int start = LocateVex(G,v1);//�������
    int end = LocateVex(G, v2);//�յ�����
    //��ʼ��S,D,Path
    for (i = 0; i < G.vexnum; i++) {
        S[i] = false;
        D[i] = G.arcs[start][i];
        if (D[i] < Infinite) Path[i] = start;
        else Path[i] = -1;
    }
    S[start] = true;
    D[start] = 0;
    int v=start;
    for (i = 1; i < G.vexnum; i++) {
        int min = Infinite;
        for (j = 0; j < G.vexnum; j++)
            if (!S[j] && D[j] < min) {
                v = j; min = D[j];
            }
        S[v] = true;
        if (v == end) return min;
        for (j = 0; j < G.vexnum; j++)
            if (!S[j] && (D[v] + G.arcs[v][j]) < D[j]) {
                D[j] = D[v] + G.arcs[v][j];
                Path[j] = v;
            }
    }
}
int GetDistribution(string name, string distribution[], string filename)
{//ʹ��filename��ȡplant.txt�ļ�
 //���ݴ����ֲ�������õ�ֲ��ֲ���distribution�������طֲ�������
    ifstream infile;
    infile.open(filename.c_str());
    string single;
    while (getline(infile, single)) {
        //�����½ڵ��data
        stringstream singlestream(single);
        string element;
        string pname;
        int flag = 1;
        while (getline(singlestream, element, '#')) {
            if (flag == 1)	pname = element;
            if (pname == name&&flag==3)
            {
                int i = 0;
                stringstream placestream(element);
                string place;
                while (getline(placestream, place, '@')) {
                    distribution[i++] = place;
                }
                infile.close();
                return i;
            }
            flag++;
        }
    }
}

int main()
{
    string name, place;      //ֲ������name��Ŀ��ʡ��place
    Graph G;
    InitGraph(G);
    CreateGraph(G, "distance.txt");	//·�����Ϊ�Լ��ı���·��
    while (cin >> name >> place) {
        if (name == "0" && place == "0")
            break;
        string distribution[34];
        int placenum = GetDistribution(name, distribution, "plant.txt");
        int min_d = 99999;
        string start_place;
        int flag = 1;
        for (int i = 0; i < placenum; i++) {
            if (distribution[i] == place) {
                cout << "��ʡ���Ѵ��ڣ�������ֲ" << endl;
                flag = 0; break;
            }
            //����Dijkstra�㷨��v1��v2�����·��������·������
            int d = Dijkstra(G, distribution[i], place);
            if (d < min_d) {
                min_d = d;
                start_place = distribution[i];
            }
        }
        if (flag == 1)
            cout << start_place << " " << min_d << endl;
    }
    return 0;
}
