#include<iostream>
using namespace std;

//利用二叉链表进行存储
//添加两个tag位以同时支持二叉树和二叉线索树，有线索时置1，无线索时置0
typedef struct tNode{
    char data;
    int ltag;
    int rtag;
    struct tNode * lchild;
    struct tNode * rchild;
}tNode,*Tree;

//判断一棵树是否为线索二叉树，若为线索二叉树，则e=1，反之e=0
void JudgeThreadTree(Tree T,int &e){
    e = T->rtag;
}

//树初始化 构造一棵空树
void InitTree(Tree &T){
    T = NULL;
}

//先序生成一颗二叉树（递归），空节点使用!表示
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
    if(T->data != '!') cout << T->data << ' ';//这个判断语句其实没有意义
}

//先序遍历二叉树(递归)
void PreVisit(Tree &T){
    if(T){
        Visit(T);
        PreVisit(T->lchild);
        PreVisit(T->rchild);
    }
}

//中序遍历二叉树（递归）
void InVisit(Tree &T){
    if(T){
        InVisit(T->lchild);
        Visit(T);
        InVisit(T->rchild);
    }
}

//后序遍历二叉树（递归）
void PostVisit(Tree &T){
    if(T){
        PostVisit(T->lchild);
        PostVisit(T->rchild);
        Visit(T);
    }
}

//查找对应值为v的节点（面向普通二叉树）
void FindNode(Tree T,char &e,char v){
    if(T != NULL){
        if(T->data == v) e = 1;
        FindNode(T->lchild,e,v);
        FindNode(T->rchild,e,v);
    }
}

//求叶子节点的个数（递归）
void LeafNumber(Tree T,int &num){
    if(T){
        if((T->lchild == NULL) && (T->rchild == NULL)) num++;
        LeafNumber(T->lchild,num);
        LeafNumber(T->rchild,num);
    }
}

//求二叉树的高度（递归）
int GetHeight(Tree T){
    if(T == NULL) return 0;
    else{
        int l = GetHeight(T->lchild);
        int r = GetHeight(T->rchild);
        return (l>r) ? l+1 : r+1;
    }
}

//复制一颗二叉树（递归）
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

//实现二叉树的中序线索化，使用前需要初始化一个开始节点
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

//寻找线索二叉树的前驱节点，返回前驱节点的指针
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

//寻找线索二叉树的后继节点 返回后继节点的指针
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

//销毁二叉树（递归），面向普通二叉树和线索二叉树
void DeleteTree(Tree &T){
    int e;
    JudgeThreadTree(T,e);
    //面向普通二叉树
    if(!e){
        if(T){
            DeleteTree(T->lchild);
            DeleteTree(T->rchild);
            delete T;
        }
    }
    //面向线索二叉树(中序生成)
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

//查找对应值为v的节点（递归）,返回对应节点的指针（此处不考虑有多个v的情况）
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
    //面向普通的二叉树
    if(!e){
        FindNode(T,poi,v);
    }
    //面向中序生成的线索二叉树
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
    cout << "输入先序生成树的字符序列：" << endl;
    cin >> a;
    int m = 0;//统计字符串的长度
    for(int i = 0;a[i] != '\0';i++){
        m++;
    }
    int k = 0;
    Tree T;
    Tree M;
    PreCreateTree(T,a,k,m);//先序生成树T

    cout << "先序遍历二叉树：" << endl;
    PreVisit(T);
    cout << endl;
    cout << "中序遍历二叉树：" << endl;
    InVisit(T);
    cout << endl;
    cout << "后序遍历二叉树：" << endl;
    PostVisit(T);
    cout << endl;
    cout << "复制二叉树" << endl;
    CopyTree(T,M);
    cout << endl;
    cout << "对复制后的二叉树进行先序遍历：" << endl;
    PreVisit(M);
    cout << endl;

    int x;
    cout << "计算叶子节点个数：" << endl;
    LeafNumber(T,x);
    cout << x << endl;
    cout << "计算树的深度：" << endl;
    cout << GetHeight(T) << endl;

    int e=0;
    cout << "判断是否为一颗线索二叉树(是则返回1)：" << endl;
    JudgeThreadTree(T,e);
    cout << e << endl;

    cout << "寻找值为E的节点是否存在：" << endl;
    if(FindGivenNode(T,'E'))  cout << "存在，地址为：" << FindGivenNode(T,'E') << endl;
    else cout << "不存在" << endl;

    tNode* G;
    cout << "对二叉树进行中序线索化" << endl;
    CreateTreadTree2(G,T);

    cout << "判断是否为一颗线索二叉树(是则返回1)：" << endl;
    JudgeThreadTree(G,e);
    cout << e << endl;

    cout << "输入一个字符 查找其前驱节点和后序节点：" << endl;
    char t;
    cin>>t;

    tNode* given = FindGivenNode(G,t);
    tNode* fron;
    tNode* nex;
    FindFrontNode(G,given,fron);
    FindNextNode(G,given,nex);
    cout << "前驱节点是： " << fron->data << endl;
    cout << "后继节点是： " << nex->data << endl;
}

