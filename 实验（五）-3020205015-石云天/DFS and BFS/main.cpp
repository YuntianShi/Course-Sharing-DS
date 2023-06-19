#include<iostream>
using namespace std;

//邻接表数据结构

typedef struct Node{
    int to;
    int from;
    Node * link;
}edge;

typedef struct vex{
    char data;
    edge* adj;
}vex;

typedef struct Gnode{
    int n;//节点个数
    int e;//边的个数
    vex vlist[10000];
}Graph;

//邻接表的建立

void InitGraph(Graph &G){
    G.n = 15;
    G.e = 32;
    for(int i = 0;i < G.n;i++){
        G.vlist[i].data = 65 + i;
        G.vlist[i].adj = NULL;
    }
    for(int i = 0;i < G.e;i++){
        int tail,head;
        cin >> tail >> head;
        edge* p = new edge;
        p->to = head;
        p->link = G.vlist[tail].adj;
        G.vlist[tail].adj = p;
    }
}

//获取节点的第一个相邻节点
int getfirst(Graph G,int v){
    if(G.vlist[v].adj == NULL) return -1;
    else return G.vlist[v].adj->to;
}

//获取邻接表中w后面的节点
int GetNextVex(Graph G,int v,int w){
    edge *p = G.vlist[v].adj;
    while(p->to != w){
        p = p->link;
    }
    if(p->link == NULL) return -1;
    else return p->link->to;

}

//建立队列用于BFS算法
typedef struct Qnode{
    int data;
    Qnode* next;
}Qnode,*Queue;

void InitQueue(Queue &Q){
    Q->next = NULL;
}

int QueueEmpty(Queue Q){
    if(Q->next == NULL) return 1;
    else return 0;
}

void EnQueue(Queue &Q,int v){
    Qnode* p = new Qnode;
    p->data = v;
    p->next = NULL;
    Qnode *q = Q;
    while(q->next != NULL){
        q = q->next;
    }
    q->next = p;
}

void DeQueue(Queue &Q,int &v){
    Qnode* p = Q->next;
    v = p->data;
    Q->next = p->next;
    delete p;
}

//建立栈用于DFS算法
typedef struct Snode{
    int data;
    Snode *next;
}Snode,*Stack;

void InitStack(Stack &S){
    S = new Snode;
    S->next = NULL;
}

int StackEmpty(Stack S){
    if(S->next == NULL) return 0;
    else return 1;
}

void Push(Stack &S,int e){
    Snode *p = new Snode;
    S->data = e;
    p->next = S;
     S = p;
}

void Pop(Stack &S,int &e){
    if(!StackEmpty(S)) cout << "The Stack is EMPTY!" << endl;
    else{
        Snode* p = S;
        e = p->next->data;
        S = S->next;
        delete(p);
    }
}

//DFS算法的递归实现
void DFS(Graph G,int k,int v,int visited[]){
    //执行遍历并记录连通分支
    cout << "第" << k << "个连通分支：  " << G.vlist[v].data << endl;
    visited[v] = 1;
    int w = getfirst(G,v);
    while(w != -1){
        if(visited[w] == 0){
            DFS(G,k,w,visited);
        }
        w = GetNextVex(G,v,w);
    }
}

//DFS算法的非递归实现（调用栈）
void DFS2 (Graph G,int k,int v,int visited[]) {
   Stack s;
   InitStack(s);
   while (StackEmpty(s)){
            Pop(s, v);
            if (visited[v] == 0)  {
            cout << "第" << k << "个连通分支：  " << G.vlist[v].data << endl;
            visited[v] = 1;
            }
        int w = getfirst(G, v);
        while( w != -1){
            if(!visited[w]) Push (s, w);
            w = GetNextVex(G, v, w);
        }
    }
}

//BFS算法的非递归实现（调用队列）
void BFS(Graph G,int k,int v,int visited[]){
    //执行遍历 并记录连通分支
    cout << "第" << k << "个连通分支：  " << G.vlist[v].data << endl;
    visited[v] = 1;
    Queue q;
    InitQueue(q);
    EnQueue(q,v);
    while(QueueEmpty(q) == 0){
        DeQueue(q,v);
        int w = getfirst(G,v);
        while(w != -1){
            if(visited[w] == 0){
                cout << "第" << k << "个连通分支：  " << G.vlist[w].data << endl;
                visited[w] = 1;
                EnQueue(q,w);
            }
            w = GetNextVex(G,v,w);
        }
    }
}

//BFS主函数
void GraphBFS(Graph &G){
    int visited[G.n];
    for(int i = 0;i < G.n;i++) visited[i] = 0;
    int k = 1;//用来表示第几个连通分支
    for(int i = 0;i < G.n;i++){
        if(visited[i] == 0){
            //深度优先遍历
            BFS(G,k,i,visited);
            k++;
        }
    }
}

//DFS主函数
void GraphDFS(Graph &G){
    int visited[G.n];
    for(int i = 0;i < G.n;i++) visited[i] = 0;
    int k = 1;//用来表示第几个连通分支
    for(int i = 0;i < G.n;i++){
        if(visited[i] == 0){
            //深度优先遍历
            DFS(G,k,i,visited);
            k++;
        }
    }
}

int main(){
    Graph G;
    InitGraph(G);
    cout << "BFS算法结果：" << endl;
    GraphBFS(G);
    cout << endl;
    cout << "DFS算法结果：" << endl;
    GraphDFS(G);
}

