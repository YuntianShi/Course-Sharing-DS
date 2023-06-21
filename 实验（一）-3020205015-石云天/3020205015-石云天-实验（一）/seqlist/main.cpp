#include <iostream>
#include<algorithm>

using namespace std;

//顺序表基本操作
//顺序表存储结构
typedef struct{
    int * element;
    int  length;//顺序表长
}SqList;

//初始化顺序表
int InitList(SqList &L){
    L.element=new int[1000];//声明最大容量
    if(!L.element) return 0;//分配空间失败
    L.length=0;
    return 1;
}

//销毁顺序表
void DestroyList(SqList &L){
    L.length=0;
    delete L.element;
}

//添加元素
int AddList(SqList &L,int x){
    if(L.length>1000) return 0;//元素个数达到上限
    L.element[L.length]=x;
    L.length++;
    return 1;
}

//插入元素（第i个元素前）
int ListInsert(SqList &L,int x,int i){
    if(i<1 or i>L.length+1 or L.length>=1000) return 0;//顺序表满或插入位置非法
    for(int j=L.length-1;j>=i-1;j--){
        L.element[j+1]=L.element[j];
    }
    L.element[i-1]=x;
    L.length++;
    return 1;
}

//删除元素
int ListDelete(SqList &L,int i){
    if(i<1 or i>L.length or L.length==0) return 0;//顺序表空或者删除位置非法
    for(int j=i-1;j<L.length-1;j++){
        L.element[j]=L.element[j+1];
    }
    L.length--;
    return 1;
}

//按序号查找元素
int GetElem(SqList L,int i,int &x){
    if(i<1 or i>L.length) return 0;//非法查找
    x=L.element[i-1];
    return 1;
}

//按值查找元素
int LocateElem(SqList L,int x){
    int i=0;
    while(i<L.length and L.element[i]!=x){
        i++;
    }
    if(i==L.length) return -1;//顺序表中无此元素
    else return i;//若找到，返回对应的数组下标
}

//倒序排列元素
void ReverseList(SqList &L){
    for(int i=0;i<(L.length-1)/2;i++){
        int a=L.element[i];
        L.element[i]=L.element[L.length-1-i];
        L.element[L.length-1-i]=a;
    }
}

//按序输出元素
void PrintList(SqList L){
    if(!L.length) cout<<"Empty List!"<<endl;//顺序表空
    else{
        for(int i=0;i<L.length;i++){
            cout<<L.element[i]<<endl;
        }
    }
}

//链表基本操作
//链表存储结构
typedef struct Lnode{
    int data;
    struct Lnode* next;
}Lnode,*LinkList;

//初始化链表
void InitLinkList(LinkList &L){
    L=new Lnode;//创建头结点
    L->next=NULL;
}

//销毁链表
void DestroyLinkList(LinkList &L){
    Lnode *p=L->next;
    Lnode *q=p;//利用双指针完成销毁操作
    while(p){
        p=p->next;
        delete q;
        q=p;
    }
}

//插入元素（头插法）
void HeadCreateLinkList(LinkList &L,int x){
    Lnode* m=new Lnode;
    m->data=x;
    m->next=L->next;
    L->next=m;
}

//插入元素（尾插法）
void LastCreateLinklist(LinkList &L,int x){
    Lnode* m=new Lnode;
    m->data=x;
    m->next=NULL;
    Lnode *p=L;
    while(p->next){
        p=p->next;
    }//根据链表性质找到尾结点
    p->next=m;//链接至新结点
}

//插入元素
void LinkListInsert(LinkList &L,int i,int x){
    Lnode* m=new Lnode;
    m->data=x;
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    m->next=p->next;//找到所需位置完成链接
    p->next=m;
}

//删除元素
void LinkListDelete(LinkList &L,int i){
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    int b=1;
    Lnode *q=L->next;//利用双指针保证删除后链接顺序正确
    while(q!=0 && b<i-1){
        q=q->next;
        b++;
    }
    q->next=p->next;
    delete p;
}

//查找元素（按序号找）
int GetElem_LinkList(LinkList L,int i,int &x){
    if(i<1) return -1;//非法查找
    int a=1;
    Lnode *p=L->next;
    while(p!=0 && a<i){
        p=p->next;
        a++;
    }
    if(!p) return -1;
    else x=p->data;
}


//查找元素（按值找）
int LocateElem_LinkList(LinkList L,int x){
    Lnode *p=L->next;
    int a=1;
    while(p!=0 and p->data!=x){
        p=p->next;
        a++;
    }
    if(!p) return -1;//链表中无此元素
    return a;//链表中第k个元素即为所找
}

//获取元素个数
int GetNum(LinkList L){
    Lnode* p=L->next;
    int a=0;
    while(p!=0){
        p=p->next;
        a++;
    }
    return a;
}

//递增排序
int SortLinkList(LinkList &L){
    //先取出链表中所有元素并置于数组中
    int a[GetNum(L)];
    Lnode* p=L->next;
    int b=0;
    while(p!=0){
        a[b]=p->data;
        b++;
        p=p->next;
    }
    sort(a,a+GetNum(L));//利用sort函数进行数组排序
    Lnode* q=L->next;
    int c=0;
    while(q!=0){
        q->data=a[c];
        q=q->next;
        c++;
    }//再将排序后的数组元素一一存入链表中
}

//倒序排列元素
void ReverseLinkList(LinkList &L){
    Lnode* p=L->next;
    Lnode* q=p;
    L->next=NULL;
    while(p!=0){
        p=p->next;
        q->next=L->next;
        L->next=q;
        q=p;
    }//利用双指针改变链表指针方向，完成倒序操作
}

//按序输出元素
void PrintLinkList(LinkList L){
    Lnode* p=L->next;
    if(!p) cout<<"Empty LinkList!"<<endl;//链表空
    else{
        while(p!=0){
            cout<<p->data<<" ";
            p=p->next;
        }
    }
    cout<<endl;
}

//实现两个链表的融合
void Merge(LinkList &A,LinkList &B){

    InitLinkList(A);
    InitLinkList(B);//首先利用预设函数对两个链表进行初始化
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
        HeadCreateLinkList(B,b);//使用头插法建立两个链表
    }

    SortLinkList(A);
    SortLinkList(B);
    ReverseLinkList(A);
    ReverseLinkList(B);//利用递增排序后翻转实现两个链表的递减排序
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
    }//实现两表合并并完成去重
    cout<<endl;
    cout<<"Results:"<<endl;
    PrintLinkList(A);//按序输出A表
}

int main(){
    LinkList A;
    LinkList B;
    Merge(A,B);
    system("pause");
}
