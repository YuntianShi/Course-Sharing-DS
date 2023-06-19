#include <iostream>

using namespace std;

typedef struct Linknode{
    char data;
    struct Linknode *next;
}Linknode,*LiStack;

//链栈的初始化函数
void InitStack(LiStack &S){
    S = new Linknode;
    S->next = NULL;
}

//链栈的销毁
void DeleteStack(LiStack &S){
    Linknode * p = S;
    do{
        S = S->next;
        delete(p);
        p = S;
    }while(p);
}

//判断栈空 栈空返回0 栈非空返回1
int StackEmpty(LiStack S){
    if(S->next == NULL) return 0;
    else return 1;
}

//入栈
void Push(LiStack &S,char x){
    Linknode * p = new Linknode;
    S->data = x;
    p->next = S;
    S = p;
}

//出栈
void Pop(LiStack &S,char &x){
    if(!StackEmpty(S)) cout<< "The stack is EMPTY!" <<endl;//判断是否为空栈
    else{
        Linknode * p = S;
        x = p->next->data;
        S = S->next;
        delete(p);
    }
}

//返回栈顶元素
char GetTop_Stack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
        return '$';
    }//判断是否为空栈
    else{
        return S->next->data;
    }
}

//输出栈内元素(LIFO)
void PrintStack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
    }//判断是否为空栈
    else{
        Linknode * p = S->next;
        do{
            cout<< p->data << ' ';
            p = p->next;
        }while(p);
    }
}

typedef struct{
    int* data;
    int front;
    int rear;
}SqQueue;

int MAXSIZE=100;//全局变量设置最大长度

//队列的初始化
int InitQueue(SqQueue &Q){
    Q.data = new int[MAXSIZE-1];
    if(!Q.data) return -1;//内存分配失败
    else{
        Q.front = 0;
        Q.rear = 0;
        return 1;
    }
}

//队列的销毁
void DeleteQueue(SqQueue &Q){
    if(!Q.data){
        cout<< "There is no need to delete because it is EMPTY" <<endl;
    }//判断队列是否为空
    else{
       delete(Q.data);
    }
}

//入队
int EnQueue(SqQueue &Q,int x){
    if(((Q.rear+1)%MAXSIZE) == Q.front){
        cout<< "The queue is FULL" <<endl;
        return -1;
    }//判断队列是否已满
    else{
        Q.data[Q.rear] = x;
        Q.rear = (Q.rear+1) % MAXSIZE;
        return 1;
    }
}

//出队
int DeQueue(SqQueue &Q,int &x){
    if(Q.front == Q.rear){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//判断队列是否为空
    else{
        x = Q.data[Q.front];
        Q.front = (Q.front+1) % MAXSIZE;
        return 1;
    }
}

//返回队头元素
int GetTop_Queue(SqQueue &Q,int &x){
    if(Q.rear == Q.front){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//判断队列是否为空
    else{
        x = Q.data[Q.front];
        return 1;
    }
}

//输出队列内元素(FIFO)
int PrintQueue(SqQueue Q){
    if(Q.front == Q.rear){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//判断队列是否为空
    else if(Q.front < Q.rear){
        for(int i=Q.front;i<Q.rear;i++){
            cout<< Q.data[i] << ' ' ;
        }
        return 1;
    }
    else{
        for(int i=Q.front;i<Q.rear+MAXSIZE;i++){
            cout<< Q.data[i] << ' ' ;
        }
        return 1;
    }
}

int main(){
    cout<< "Hello World!"<<endl;
    return 0;
}
