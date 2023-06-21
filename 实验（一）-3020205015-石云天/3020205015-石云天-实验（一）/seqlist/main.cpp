#include <iostream>
#include<algorithm>

using namespace std;

//˳����������
//˳���洢�ṹ
typedef struct{
    int * element;
    int  length;//˳���
}SqList;

//��ʼ��˳���
int InitList(SqList &L){
    L.element=new int[1000];//�����������
    if(!L.element) return 0;//����ռ�ʧ��
    L.length=0;
    return 1;
}

//����˳���
void DestroyList(SqList &L){
    L.length=0;
    delete L.element;
}

//���Ԫ��
int AddList(SqList &L,int x){
    if(L.length>1000) return 0;//Ԫ�ظ����ﵽ����
    L.element[L.length]=x;
    L.length++;
    return 1;
}

//����Ԫ�أ���i��Ԫ��ǰ��
int ListInsert(SqList &L,int x,int i){
    if(i<1 or i>L.length+1 or L.length>=1000) return 0;//˳����������λ�÷Ƿ�
    for(int j=L.length-1;j>=i-1;j--){
        L.element[j+1]=L.element[j];
    }
    L.element[i-1]=x;
    L.length++;
    return 1;
}

//ɾ��Ԫ��
int ListDelete(SqList &L,int i){
    if(i<1 or i>L.length or L.length==0) return 0;//˳���ջ���ɾ��λ�÷Ƿ�
    for(int j=i-1;j<L.length-1;j++){
        L.element[j]=L.element[j+1];
    }
    L.length--;
    return 1;
}

//����Ų���Ԫ��
int GetElem(SqList L,int i,int &x){
    if(i<1 or i>L.length) return 0;//�Ƿ�����
    x=L.element[i-1];
    return 1;
}

//��ֵ����Ԫ��
int LocateElem(SqList L,int x){
    int i=0;
    while(i<L.length and L.element[i]!=x){
        i++;
    }
    if(i==L.length) return -1;//˳������޴�Ԫ��
    else return i;//���ҵ������ض�Ӧ�������±�
}

//��������Ԫ��
void ReverseList(SqList &L){
    for(int i=0;i<(L.length-1)/2;i++){
        int a=L.element[i];
        L.element[i]=L.element[L.length-1-i];
        L.element[L.length-1-i]=a;
    }
}

//�������Ԫ��
void PrintList(SqList L){
    if(!L.length) cout<<"Empty List!"<<endl;//˳����
    else{
        for(int i=0;i<L.length;i++){
            cout<<L.element[i]<<endl;
        }
    }
}

//�����������
//����洢�ṹ
typedef struct Lnode{
    int data;
    struct Lnode* next;
}Lnode,*LinkList;

//��ʼ������
void InitLinkList(LinkList &L){
    L=new Lnode;//����ͷ���
    L->next=NULL;
}

//��������
void DestroyLinkList(LinkList &L){
    Lnode *p=L->next;
    Lnode *q=p;//����˫ָ��������ٲ���
    while(p){
        p=p->next;
        delete q;
        q=p;
    }
}

//����Ԫ�أ�ͷ�巨��
void HeadCreateLinkList(LinkList &L,int x){
    Lnode* m=new Lnode;
    m->data=x;
    m->next=L->next;
    L->next=m;
}

//����Ԫ�أ�β�巨��
void LastCreateLinklist(LinkList &L,int x){
    Lnode* m=new Lnode;
    m->data=x;
    m->next=NULL;
    Lnode *p=L;
    while(p->next){
        p=p->next;
    }//�������������ҵ�β���
    p->next=m;//�������½��
}

//����Ԫ��
void LinkListInsert(LinkList &L,int i,int x){
    Lnode* m=new Lnode;
    m->data=x;
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    m->next=p->next;//�ҵ�����λ���������
    p->next=m;
}

//ɾ��Ԫ��
void LinkListDelete(LinkList &L,int i){
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    int b=1;
    Lnode *q=L->next;//����˫ָ�뱣֤ɾ��������˳����ȷ
    while(q!=0 && b<i-1){
        q=q->next;
        b++;
    }
    q->next=p->next;
    delete p;
}

//����Ԫ�أ�������ң�
int GetElem_LinkList(LinkList L,int i,int &x){
    if(i<1) return -1;//�Ƿ�����
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    if(!p) return -1;
    else x=p->data;
}


//����Ԫ�أ���ֵ�ң�
int LocateElem_LinkList(LinkList L,int x){
    Lnode *p=L->next;
    int a=1;
    while(p!=0 and p->data!=x){
        p=p->next;
        a++;
    }
    if(!p) return -1;//�������޴�Ԫ��
    return a;//�����е�k��Ԫ�ؼ�Ϊ����
}

//��ȡԪ�ظ���
int GetNum(LinkList L){
    Lnode* p=L->next;
    int a=0;
    while(p!=0){
        p=p->next;
        a++;
    }
    return a;
}

//��������
int SortLinkList(LinkList &L){
    //��ȡ������������Ԫ�ز�����������
    int a[GetNum(L)];
    Lnode* p=L->next;
    int b=0;
    while(p!=0){
        a[b]=p->data;
        b++;
        p=p->next;
    }
    sort(a,a+GetNum(L));//����sort����������������
    Lnode* q=L->next;
    int c=0;
    while(q!=0){
        q->data=a[c];
        q=q->next;
        c++;
    }//�ٽ�����������Ԫ��һһ����������
}

//��������Ԫ��
void ReverseLinkList(LinkList &L){
    Lnode* p=L->next;
    Lnode* q=p;
    L->next=NULL;
    while(p!=0){
        p=p->next;
        q->next=L->next;
        L->next=q;
        q=p;
    }//����˫ָ��ı�����ָ�뷽����ɵ������
}

//�������Ԫ��
void PrintLinkList(LinkList L){
    Lnode* p=L->next;
    if(!p) cout<<"Empty LinkList!"<<endl;//�����
    else{
        while(p!=0){
            cout<<p->data<<" ";
            p=p->next;
        }
    }
    cout<<endl;
}

//ʵ������������ں�
void Merge(LinkList &A,LinkList &B){

    InitLinkList(A);
    InitLinkList(B);//��������Ԥ�躯��������������г�ʼ��
    int A_length;
    cin>>A_length;
    int a=0;
    for(int i=0;i<A_length;i++){
        cin>>a;
        HeadCreateLinkList(A,a);
    }
    int B_length;
    cin>>B_length;
    int b=0;
    for(int i=0;i<B_length;i++){
        cin>>b;
        HeadCreateLinkList(B,b);//ʹ��ͷ�巨������������
    }

    SortLinkList(A);
    SortLinkList(B);
    ReverseLinkList(A);
    ReverseLinkList(B);//���õ��������תʵ����������ĵݼ�����
    Lnode *c=A;
    Lnode *pa=A->next;
    Lnode *pb=B->next;
    while(pa!=0 && pb!=0){
        if((pa->data)<(pb->data)){
            Lnode* d=new Lnode;
            d->data=pb->data;
            d->next=pa;
            c->next=d;
            c=d;
            pb=pb->next;
        }
        else if((pa->data)==(pb->data)){
            c=c->next;
            pa=pa->next;
            pb=pb->next;
        }
        else{
            c=c->next;
            pa=pa->next;
        }
    }
    if(pa==0){
        c->next=pb;
    }//ʵ������ϲ������ȥ��
    cout<<endl;
    cout<<"Results:"<<endl;
    PrintLinkList(A);//�������A��
}

int main(){
    LinkList A;
    LinkList B;
    Merge(A,B);
    system("pause");
}
