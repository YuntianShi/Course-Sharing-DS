#include <iostream>

using namespace std;

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

//����ȫ�ֱ�����ά��ѭ������
SqQueue q;

int main()
{
    int n;
    InitQueue(q);
    cin>>n;
    for(int i=1;i<=n;i++){
        cout<<1<<' ';//ÿ��ѭ����ʼʱ������ӡ��1��
        EnQueue(q,1);
        for(int j=0;j<i-1;j++){
            int x,y;
            DeQueue(q,x);
            DeQueue(q,y);
            cout<<x+y<<' ';
            EnQueue(q,x+y);
            EnQueue(q,x+y);//����Ԫ�غ��������
        }
        cout<<1<<' '<<endl;//ÿ��ѭ������ʱ������ӡ��1��
        EnQueue(q,1);
    }
}
