#include<iostream>
using namespace std;

//邻接表数据结构
typedef struct Node{
    int to;
    int from;
    struct Node * link;
}edge;

typedef struct vex{
    int data;
    edge* adj;
}vex;

typedef struct Gnode{
    int n;//节点个数
    int e;//边的个数
    vex vlist[10000];
}Graph;

//建立邻接表
void InitGraph(Graph &G){
    G.n = 9;
    G.e = 11;
    cout << "输入所求的AOE网络：" << endl;
    for(int i = 0;i < G.n;i++){
        G.vlist[i].data = i + 1;
        G.vlist[i].adj = NULL;
    }
    for(int i = 0;i < G.e;i++){
        int tail,head,weight;
        cin >> tail >> head >> weight;
        edge* p = new edge;
        p->from = weight;
        p->to = head;
        p->link = G.vlist[tail].adj;
        G.vlist[tail].adj = p;
    }
}

void CritialPath(Graph G){
    int ve[G.n];
    int vl[G.n];
    //正向计算事件的最早开始时间
    cout << "关键路径：" << endl;
    for(int i = 0;i < G.n;i++) ve[i] = 0;
    for(int i = 0;i < G.n;i++){
        edge* p = G.vlist[i].adj;
        while(p != NULL){
            int k = p->to;
            if(ve[i] + p->from > ve[k]) ve[k] = ve[i] + p->from;
            p = p->link;
        }
    }
    //逆向计算事件的最晚开始时间
    for(int i = 0;i < G.n;i++) vl[i] = ve[G.n-1];
    for(int i = G.n-2;i > 0;i--){
        edge* p = G.vlist[i].adj;
        while(p != NULL){
            int k = p->to;
            if(vl[k] - p->from < vl[i]) vl[i] = vl[k] - p->from;
            p = p->link;
        }
    }
    //判断并打印关键路径
    for(int i = 0;i < G.n;i++){
        edge* p = G.vlist[i].adj;
        while(p != NULL){
            int k = p->to;
            if(ve[i] == vl[k] - p->from) cout << "<" << i + 1 << "," << k + 1 << ">" << endl;
            p = p->link;
        }
    }
}

int main(){
    Graph G;
    InitGraph(G);
    CritialPath(G);
}

