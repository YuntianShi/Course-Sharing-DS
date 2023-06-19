#include<iostream>
#include <algorithm>
using namespace std;

//哈夫曼树的数据结构
typedef struct tNode{
    int data;
    int parent;
    int lchild;
    int rchild;
}tNode,*HTree;

//创建哈夫曼树
int CreateHuffmanTree(HTree &H,int num,int a[]){
    if(num == 0){
        cout << "Empty Tree" << endl;
        return 0;
    }
    int sum = 2 * num -1;
    H = new tNode[sum];//利用静态存储哈夫曼树

    //初始化存储结构
    for(int i = 0;i < num;i++){
        H[i].data = a[i];
        H[i].parent = -1;
        H[i].lchild = -1;
        H[i].rchild = -1;
    }
    for(int i = num;i < sum;i++){
        H[i].data = 0;
        H[i].parent = -1;
        H[i].lchild = -1;
        H[i].rchild = -1;
    }

    //构造哈夫曼树，若涉及到树的节点个数小于2，那么程序报错终止
    int x = num;
    while(x < sum){
        int m1=1000000;//代表稍大一点的数
        int m2=100000;//代表稍小一点的数
        int p1,p2;
        for(int i = 0;i < x;i++){
            if(H[i].parent == -1){
                if(H[i].data <= m2){
                    p1 = p2;
                    m1 = m2;
                    m2 = H[i].data;
                    p2 = i;
                }
                else if(H[i].data < m1){
                    p1 = i;
                    m1 = H[i].data;
                }
            }
        }
        H[x].data = m1 + m2;
        H[x].lchild = p2;
        H[x].rchild = p1;
        H[p1].parent = x;
        H[p2].parent = x;
        x++;
    }
}

//销毁哈夫曼树，即释放存储哈夫曼树所占用的空间
int DeleteHuffmanTree(HTree &H){
    delete H;
}

//生成哈夫曼编码，创建编码表结构
typedef struct CodeList{
    int pos;
    int data;
    char code[1000];
    int num;//表示编码位数
}CodeNode,*List;

void HuffmanCode(List &C,HTree H,int x){

    C=new CodeNode[x];
    //初始化编码表，以data为关键字实现编码表的降序排列
    for(int i = 0;i < x;i++){
        C[i].pos = i;
        C[i].data = H[i].data;
    }
    //获取每个元素的哈夫曼编码（顺序相反）
    for(int i = 0;i < x;i++){
        int temp = C[i].pos;
        int pre;
        C[i].num = 0;
        while(H[temp].parent != -1){
            pre = temp;
            temp = H[temp].parent;
            if(H[temp].lchild == pre){
                C[i].code[C[i].num] = '0';
                C[i].num++;
            }
            else if(H[temp].rchild == pre){
                C[i].code[C[i].num] = '1';
                C[i].num++;
            }
        }
        //逆序输出，得到顺序正确的哈夫曼编码
        for(int l = 0;l < C[i].num/2;l++){
            char tempchar = C[i].code[l];
            C[i].code[l] = C[i].code[C[i].num-1-l];
            C[i].code[C[i].num-1-l] = tempchar;
        }
    }
}

int main(){
    HTree H;
    int num;
    cin >> num;
    int a[num];
    for(int i = 0;i < num;i++){
        cin >> a[i];
    }
    sort(a,a+num,greater<int>());//建立哈夫曼树
    CreateHuffmanTree(H,num,a);//实现哈夫曼编码
    List C;//建立编码表
    HuffmanCode(C,H,num);

    for(int i = 0;i < num;i++){
        cout << C[i].data << " " << ":" << " ";
        for(int j=0;j<C[i].num;j++)  cout << C[i].code[j];
        cout << endl;
    }
}
