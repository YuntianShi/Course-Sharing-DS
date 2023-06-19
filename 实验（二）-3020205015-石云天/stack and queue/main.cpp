#include <iostream>

using namespace std;

typedef struct Linknode{
    char data;
    struct Linknode *next;
}Linknode,*LiStack;

//��ջ�ĳ�ʼ������
void InitStack(LiStack &S){
    S = new Linknode;
    S->next = NULL;
}

//��ջ������
void DeleteStack(LiStack &S){
    Linknode * p = S;
    do{
        S = S->next;
        delete(p);
        p = S;
    }while(p);
}

//�ж�ջ�� ջ�շ���0 ջ�ǿշ���1
int StackEmpty(LiStack S){
    if(S->next == NULL) return 0;
    else return 1;
}

//��ջ
void Push(LiStack &S,char x){
    Linknode * p = new Linknode;
    S->data = x;
    p->next = S;
    S = p;
}

//��ջ
void Pop(LiStack &S,char &x){
    if(!StackEmpty(S)) cout<< "The stack is EMPTY!" <<endl;//�ж��Ƿ�Ϊ��ջ
    else{
        Linknode * p = S;
        x = p->next->data;
        S = S->next;
        delete(p);
    }
}

//����ջ��Ԫ��
char GetTop_Stack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
        return '$';
    }//�ж��Ƿ�Ϊ��ջ
    else{
        return S->next->data;
    }
}

//���ջ��Ԫ��(LIFO)
void PrintStack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
    }//�ж��Ƿ�Ϊ��ջ
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

int MAXSIZE=100;//ȫ�ֱ���������󳤶�

//���еĳ�ʼ��
int InitQueue(SqQueue &Q){
    Q.data = new int[MAXSIZE-1];
    if(!Q.data) return -1;//�ڴ����ʧ��
    else{
        Q.front = 0;
        Q.rear = 0;
        return 1;
    }
}

//���е�����
void DeleteQueue(SqQueue &Q){
    if(!Q.data){
        cout<< "There is no need to delete because it is EMPTY" <<endl;
    }//�ж϶����Ƿ�Ϊ��
    else{
       delete(Q.data);
    }
}

//���
int EnQueue(SqQueue &Q,int x){
    if(((Q.rear+1)%MAXSIZE) == Q.front){
        cout<< "The queue is FULL" <<endl;
        return -1;
    }//�ж϶����Ƿ�����
    else{
        Q.data[Q.rear] = x;
        Q.rear = (Q.rear+1) % MAXSIZE;
        return 1;
    }
}

//����
int DeQueue(SqQueue &Q,int &x){
    if(Q.front == Q.rear){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//�ж϶����Ƿ�Ϊ��
    else{
        x = Q.data[Q.front];
        Q.front = (Q.front+1) % MAXSIZE;
        return 1;
    }
}

//���ض�ͷԪ��
int GetTop_Queue(SqQueue &Q,int &x){
    if(Q.rear == Q.front){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//�ж϶����Ƿ�Ϊ��
    else{
        x = Q.data[Q.front];
        return 1;
    }
}

//���������Ԫ��(FIFO)
int PrintQueue(SqQueue Q){
    if(Q.front == Q.rear){
        cout<< "The queue is EMPTY" <<endl;
        return -1;
    }//�ж϶����Ƿ�Ϊ��
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
