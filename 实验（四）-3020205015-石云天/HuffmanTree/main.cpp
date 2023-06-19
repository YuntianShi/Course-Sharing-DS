#include<iostream>
#include <algorithm>
using namespace std;

//�������������ݽṹ
typedef struct tNode{
    int data;
    int parent;
    int lchild;
    int rchild;
}tNode,*HTree;

//������������
int CreateHuffmanTree(HTree &H,int num,int a[]){
    if(num == 0){
        cout << "Empty Tree" << endl;
        return 0;
    }
    int sum = 2 * num -1;
    H = new tNode[sum];//���þ�̬�洢��������

    //��ʼ���洢�ṹ
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

    //����������������漰�����Ľڵ����С��2����ô���򱨴���ֹ
    int x = num;
    while(x < sum){
        int m1=1000000;//�����Դ�һ�����
        int m2=100000;//������Сһ�����
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

//���ٹ������������ͷŴ洢����������ռ�õĿռ�
int DeleteHuffmanTree(HTree &H){
    delete H;
}

//���ɹ��������룬���������ṹ
typedef struct CodeList{
    int pos;
    int data;
    char code[1000];
    int num;//��ʾ����λ��
}CodeNode,*List;

void HuffmanCode(List &C,HTree H,int x){

    C=new CodeNode[x];
    //��ʼ���������dataΪ�ؼ���ʵ�ֱ����Ľ�������
    for(int i = 0;i < x;i++){
        C[i].pos = i;
        C[i].data = H[i].data;
    }
    //��ȡÿ��Ԫ�صĹ��������루˳���෴��
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
        //����������õ�˳����ȷ�Ĺ���������
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
    sort(a,a+num,greater<int>());//������������
    CreateHuffmanTree(H,num,a);//ʵ�ֹ���������
    List C;//���������
    HuffmanCode(C,H,num);

    for(int i = 0;i < num;i++){
        cout << C[i].data << " " << ":" << " ";
        for(int j=0;j<C[i].num;j++)  cout << C[i].code[j];
        cout << endl;
    }
}
