#include <iostream>

using namespace std;

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

//设置全局变量，维护循环队列
SqQueue q;

int main()
{
    int n;
    InitQueue(q);
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<1<<' ';//每次循环开始时单独打印“1”
        EnQueue(q,1);
        for(int j=0;j<i-1;j++){
            int x,y;
            DeQueue(q,x);
            DeQueue(q,y);
            cout<<x+y<<' ';
            EnQueue(q,x+y);
            EnQueue(q,x+y);//将两元素和入队两次
        }
        cout<<1<<' '<<endl;//每次循环结束时单独打印“1”
        EnQueue(q,1);
    }
}
