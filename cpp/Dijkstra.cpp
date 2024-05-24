#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string> 
#define MVNum 34                           //最大顶点数
#define ERROR 0
#define Infinite 9999
using namespace std;

typedef struct
{
    string vexs[MVNum];               	//顶点表
    int arcs[MVNum][MVNum];            	//邻接矩阵
    int vexnum;                        	//图的总顶点数
    int arcnum;                        	//图的总边数
}Graph;
int LocateVex(Graph G, string u)
{//存在则返回u在顶点表中的下标，否则返回ERROR
    for (int i = 0; i < G.vexnum; i++)
        if (u == G.vexs[i]) return i;
    return ERROR;
}

void InitGraph(Graph& G) {
    G.vexnum = 34;		//34个省级行政单位
    string place[] = { "北京","上海","天津","重庆","内蒙古","广西","西藏","宁夏","新疆","香港","澳门","河北","山西","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南","陕西","甘肃","青海","台湾" };
    for (int i = 0; i < G.vexnum; i++)
        G.vexs[i] = place[i];
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = Infinite;
}
void CreateGraph(Graph& G, string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要使用filename参数
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
{//利用Dijkstra算法求v1到v2的最短路径并返回路径长度
    int D[MVNum];//记录源点到相应顶点路径长度
    bool S[MVNum];//记录相应顶点是否已被确定最短距离
    int Path[MVNum];//记录相应顶点的前驱顶点
    int i, j;
    int start = LocateVex(G,v1);//起点坐标
    int end = LocateVex(G, v2);//终点坐标
    //初始化S,D,Path
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
{//使用filename读取plant.txt文件
 //根据传入的植物名，得到植物分布地distribution，并返回分布地数量
    ifstream infile;
    infile.open(filename.c_str());
    string single;
    while (getline(infile, single)) {
        //输入新节点的data
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
    string name, place;      //植物名称name和目的省份place
    Graph G;
    InitGraph(G);
    CreateGraph(G, "distance.txt");	//路径需改为自己的本地路径
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
                cout << "该省份已存在，无需移植" << endl;
                flag = 0; break;
            }
            //利用Dijkstra算法求v1到v2的最短路径并返回路径长度
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
