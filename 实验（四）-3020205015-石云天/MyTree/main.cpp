#include<iostream>
using namespace std;

//���ö���������д洢
//�������tagλ��ͬʱ֧�ֶ������Ͷ�����������������ʱ��1��������ʱ��0
typedef struct tNode{
    char data;
    int ltag;
    int rtag;
    struct tNode * lchild;
    struct tNode * rchild;
}tNode,*Tree;

//�ж�һ�����Ƿ�Ϊ��������������Ϊ��������������e=1����֮e=0
void JudgeThreadTree(Tree T,int &e){
    e = T->rtag;
}

//����ʼ�� ����һ�ÿ���
void InitTree(Tree &T){
    T = NULL;
}

//��������һ�Ŷ��������ݹ飩���սڵ�ʹ��!��ʾ
int PreCreateTree(Tree &T,char a[],int &i,int m){
    if(a[i]!='!'){
        T = new tNode;
        T->data = a[i];
        T->ltag = 0;
        T->rtag = 0;
        i++;
        PreCreateTree(T->lchild,a,i,m);
        PreCreateTree(T->rchild,a,i,m);
    }
    else{
        T = NULL;
        i++;
    }
    if(i > m-1) return 0;
}

void Visit(Tree T){
    if(T->data != '!') cout << T->data << ' ';//����ж������ʵû������
}

//�������������(�ݹ�)
void PreVisit(Tree &T){
    if(T){
        Visit(T);
        PreVisit(T->lchild);
        PreVisit(T->rchild);
    }
}

//����������������ݹ飩
void InVisit(Tree &T){
    if(T){
        InVisit(T->lchild);
        Visit(T);
        InVisit(T->rchild);
    }
}

//����������������ݹ飩
void PostVisit(Tree &T){
    if(T){
        PostVisit(T->lchild);
        PostVisit(T->rchild);
        Visit(T);
    }
}

//���Ҷ�ӦֵΪv�Ľڵ㣨������ͨ��������
void FindNode(Tree T,char &e,char v){
    if(T != NULL){
        if(T->data == v) e = 1;
        FindNode(T->lchild,e,v);
        FindNode(T->rchild,e,v);
    }
}

//��Ҷ�ӽڵ�ĸ������ݹ飩
void LeafNumber(Tree T,int &num){
    if(T){
        if((T->lchild == NULL) && (T->rchild == NULL)) num++;
        LeafNumber(T->lchild,num);
        LeafNumber(T->rchild,num);
    }
}

//��������ĸ߶ȣ��ݹ飩
int GetHeight(Tree T){
    if(T == NULL) return 0;
    else{
        int l = GetHeight(T->lchild);
        int r = GetHeight(T->rchild);
        return (l>r) ? l+1 : r+1;
    }
}

//����һ�Ŷ��������ݹ飩
void CopyTree(Tree T,Tree &M){
    if(T){
        M = new tNode;
        M->data = T->data;
        M->ltag = M->rtag = 0;
        M->lchild = NULL;
        M->rchild = NULL;
        CopyTree(T->lchild,M->lchild);
        CopyTree(T->rchild,M->rchild);
    }
}

//ʵ�ֶ�������������������ʹ��ǰ��Ҫ��ʼ��һ����ʼ�ڵ�
void CreateTreadTree(Tree &T, tNode* &pre){
    if(T){
        CreateTreadTree(T->lchild,pre);
        if(!T->lchild){
            T->lchild = pre;
            T->ltag = 1;
        }
        if(!pre->rchild){
            pre->rchild = T;
            pre->rtag = 1;
        }
        pre = T;
        CreateTreadTree(T->rchild,pre);
    }
}

void CreateTreadTree2(Tree &ThreadT,Tree T){
    ThreadT = new tNode;
    ThreadT->ltag = 0;
    ThreadT->rtag = 1;
    ThreadT->rchild = ThreadT;
    ThreadT->lchild = T;
    tNode* pre = ThreadT;

    CreateTreadTree(T,pre);

    pre->rchild = ThreadT;
    pre->rtag = 1;
    ThreadT->rchild = pre;
}

//Ѱ��������������ǰ���ڵ㣬����ǰ���ڵ��ָ��
int FindFrontNode(Tree T,tNode* p,tNode* &q){
    if(p->ltag == 1) q = p->lchild;
    else{
        tNode* tem = p->lchild;
        while(tem->rtag == 0){
            tem = tem->rchild;
        }
        q = tem;
    }
    if(q->data == NULL) cout << "NO Front Node!" << endl;


}

//Ѱ�������������ĺ�̽ڵ� ���غ�̽ڵ��ָ��
int FindNextNode(Tree T,tNode* p,tNode* &q){

    if(p->rtag == 1) q = p->rchild;
    else{
        tNode* tem = p->rchild;
        while(tem->ltag == 0){
            tem = tem->lchild;
        }
        q = tem;
    }
    if(q->data == NULL) cout << "NO Next Node!" << endl;
}

//���ٶ��������ݹ飩��������ͨ������������������
void DeleteTree(Tree &T){
    int e;
    JudgeThreadTree(T,e);
    //������ͨ������
    if(!e){
        if(T){
            DeleteTree(T->lchild);
            DeleteTree(T->rchild);
            delete T;
        }
    }
    //��������������(��������)
    else{
        tNode* p = T;
        while(p->lchild != NULL) p = p->lchild;
        tNode* q;
        while(FindNextNode(T,p,q)){
            delete p;
            p = q;
        }
        delete p;
        p = NULL;
    }
}

//���Ҷ�ӦֵΪv�Ľڵ㣨�ݹ飩,���ض�Ӧ�ڵ��ָ�루�˴��������ж��v�������
void FindNode(Tree T,tNode* &poi,char v){
    if(T){
        if(T->data == v) poi = T;
        FindNode(T->lchild,poi,v);
        FindNode(T->rchild,poi,v);
    }
}

void FindNode2(Tree T,tNode* &poi,char v){
    int e = 0;
    JudgeThreadTree(T,e);
    //������ͨ�Ķ�����
    if(!e){
        FindNode(T,poi,v);
    }
    //�����������ɵ�����������
    else{
        tNode* p = T->lchild;
        while(p != T){
            while(p->ltag == 0) p = p->lchild;
            if(p->data == v) poi = p;
            while(p->rtag == 1 && p->rchild != T){
                p = p->rchild;
                if(p->data == v) poi = p;
            }
            p = p->rchild;
        }
    }
}

tNode* FindGivenNode(Tree T,char v){
    tNode* poi = NULL;
    FindNode2(T,poi,v);
    return poi;
}

int main(){
    char a[100];
    cout << "�����������������ַ����У�" << endl;
    cin >> a;
    int m = 0;//ͳ���ַ����ĳ���
    for(int i = 0;a[i] != '\0';i++){
        m++;
    }
    int k = 0;
    Tree T;
    Tree M;
    PreCreateTree(T,a,k,m);//����������T

    cout << "���������������" << endl;
    PreVisit(T);
    cout << endl;
    cout << "���������������" << endl;
    InVisit(T);
    cout << endl;
    cout << "���������������" << endl;
    PostVisit(T);
    cout << endl;
    cout << "���ƶ�����" << endl;
    CopyTree(T,M);
    cout << endl;
    cout << "�Ը��ƺ�Ķ������������������" << endl;
    PreVisit(M);
    cout << endl;

    int x;
    cout << "����Ҷ�ӽڵ������" << endl;
    LeafNumber(T,x);
    cout << x << endl;
    cout << "����������ȣ�" << endl;
    cout << GetHeight(T) << endl;

    int e=0;
    cout << "�ж��Ƿ�Ϊһ������������(���򷵻�1)��" << endl;
    JudgeThreadTree(T,e);
    cout << e << endl;

    cout << "Ѱ��ֵΪE�Ľڵ��Ƿ���ڣ�" << endl;
    if(FindGivenNode(T,'E'))  cout << "���ڣ���ַΪ��" << FindGivenNode(T,'E') << endl;
    else cout << "������" << endl;

    tNode* G;
    cout << "�Զ�������������������" << endl;
    CreateTreadTree2(G,T);

    cout << "�ж��Ƿ�Ϊһ������������(���򷵻�1)��" << endl;
    JudgeThreadTree(G,e);
    cout << e << endl;

    cout << "����һ���ַ� ������ǰ���ڵ�ͺ���ڵ㣺" << endl;
    char t;
    cin>>t;

    tNode* given = FindGivenNode(G,t);
    tNode* fron;
    tNode* nex;
    FindFrontNode(G,given,fron);
    FindNextNode(G,given,nex);
    cout << "ǰ���ڵ��ǣ� " << fron->data << endl;
    cout << "��̽ڵ��ǣ� " << nex->data << endl;
}

