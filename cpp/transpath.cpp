#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include <string>
#include<sstream>
#include<string> 
#define MVNum 34                           //最大顶点数
#define ERROR 0
#define MAX 9999
#define PathNUM 100
using namespace std;
int* allpath[PathNUM];
int pathnum = 0;
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
string OrigialVex(Graph G, int u)
{//存在则返回顶点表中下标为u的元素
    return G.vexs[u];
}
void InitGraph(Graph& G) {
    G.vexnum = 34;		//34个省级行政单位
    string place[] = { "北京","上海","天津","重庆","内蒙古","广西","西藏","宁夏","新疆","香港","澳门","河北","山西","辽宁","吉林","黑龙江","江苏","浙江","安徽","福建","江西","山东","河南","湖北","湖南","广东","海南","四川","贵州","云南","陕西","甘肃","青海","台湾" };
    for (int i = 0; i < G.vexnum; i++) {
        G.vexs[i] = place[i];
    }
    for (int i = 0; i < G.vexnum; i++)
        for (int j = 0; j < G.vexnum; j++)
            G.arcs[i][j] = MAX;
}
void CreateGraph(Graph& G, string filename)
{//采用邻接矩阵表示法，读distance.txt，创建有向图G
 //读distance.txt时要调用filename参数
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

void mov(int* a, int* b) //二维数组allpath的行间交换
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
    //先把path数组存到二维数组的0号单元
    for (i = 0; i < len - 1; i++) {
        allpath[0][i + 1] = path[i];
        distance += G.arcs[path[i]][path[i + 1]];
    }
    allpath[0][0] = distance;//每一行的0号单元放distance
    allpath[0][i + 1] = path[i]; i++;
    allpath[0][i + 1] = -1;//结束的标记
    //插入
    i = 1;
    while (distance > allpath[i][0] && allpath[i][0] > 0)//确认插入位置
        i++;
    for (j = pathnum; j >= i; j--)//后移
        mov(allpath[j + 1], allpath[j]);
    mov(allpath[j + 1], allpath[0]);
    /*for (int i = 0; i < len + 2; i++) {
        cout << allpath[j + 1][i] << " ";
        cout << endl;
    }*/
    pathnum++;//总路数＋1
}

//v到w n是最大长度 len是path[]中有效长度
void GoPath(Graph G, int v, int w, int path[], int n, int len) {
    //n小于0表示超过最大长度排除掉 结束这条路线
    //n大于等于0的时候 
    if (n >= 0) {
        path[len++] = v;//将当前的起始顶点加入path数组
        if (v == w) {
            addpath(G, path, len);//走到终点且符合条件 将该路线加入allpath保存
        }
        else//还没到终点
        {
            int i, j;
            //将当前起始顶点的邻顶点（不包括已经走过的）依次作为下一个递归的起始顶点
            //最大长度参数减去对应权值
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
{//找到p1到p2所有长度小于n的路径并按路程从小到大输出
 //若需用到递归函数或全局变量等请自行定义并合理调用
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
    string p1, p2;      	//运输起点p1，终点p2
    int n;				//可接受的最长距离
    Graph G;
    InitGraph(G);
    CreateGraph(G, "distance.txt");	//路径需改为自己的本地路径
    cin >> p1 >> p2 >> n;
    FindWay(G, p1, p2, n);
    return 0;
}
