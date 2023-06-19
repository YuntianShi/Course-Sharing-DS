#include<iostream>
using namespace std;

//�ڽӱ����ݽṹ
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
    int n;//�ڵ����
    int e;//�ߵĸ���
    vex vlist[10000];
}Graph;

//�����ڽӱ�
void InitGraph(Graph &G){
    G.n = 9;
    G.e = 11;
    cout << "���������AOE���磺" << endl;
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
    //��������¼������翪ʼʱ��
    cout << "�ؼ�·����" << endl;
    for(int i = 0;i < G.n;i++) ve[i] = 0;
    for(int i = 0;i < G.n;i++){
        edge* p = G.vlist[i].adj;
        while(p != NULL){
            int k = p->to;
            if(ve[i] + p->from > ve[k]) ve[k] = ve[i] + p->from;
            p = p->link;
        }
    }
    //��������¼�������ʼʱ��
    for(int i = 0;i < G.n;i++) vl[i] = ve[G.n-1];
    for(int i = G.n-2;i > 0;i--){
        edge* p = G.vlist[i].adj;
        while(p != NULL){
            int k = p->to;
            if(vl[k] - p->from < vl[i]) vl[i] = vl[k] - p->from;
            p = p->link;
        }
    }
    //�жϲ���ӡ�ؼ�·��
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

