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

typedef struct Linknode_int{
    int data;
    struct Linknode_int *next;
}Linknode_int,*LiStack_int;

//��ջ�ĳ�ʼ������
void InitStack_int(LiStack_int &S){
    S = new Linknode_int;
    S->next = NULL;
}

//��ջ������
void DeleteStack_int(LiStack_int &S){
    Linknode_int *p = S;
    do{
        S = S->next;
        delete(p);
        p = S;
    }while(p);
}

//�ж�ջ�� ջ�շ���0 ջ�ǿշ���1
int StackEmpty_int(LiStack_int S){
    if(S->next == NULL) return 0;
    else return 1;
}

//��ջ
void Push_int(LiStack_int &S,int x){
    Linknode_int *p = new Linknode_int;
    S->data = x;
    p->next = S;
    S = p;
}

//��ջ
void Pop_int(LiStack_int &S,int &x){
    if(!StackEmpty_int(S)) cout<< "The stack is EMPTY!" <<endl;//�ж��Ƿ�Ϊ��ջ
    else{
        Linknode_int * p = S;
        x = p->next->data;
        S = S->next;
        delete(p);
    }
}

//����ջ��Ԫ��
int GetTop_Stack_int(LiStack_int S){
    if(!StackEmpty_int(S)){
        cout<< "The stack is EMPTY!" <<endl;
        return '$';
    }//�ж��Ƿ�Ϊ��ջ
    else{
        return S->next->data;
    }
}

//���ջ��Ԫ��(LIFO)
void PrintStack_int(LiStack_int S){
    if(!StackEmpty_int(S)){
        cout<< "The stack is EMPTY!" <<endl;
    }//�ж��Ƿ�Ϊ��ջ
    else{
        Linknode_int * p = S->next;
        do{
            cout<< p->data << ' ';
            p = p->next;
        }while(p);
    }
}

//��д�����Ƚϴ���ջ�������ջ������������ȼ������ȼ��Ͳ���ջ��0��ʾ�����ȼ�����ջ��1��ʾ�����������໥������2��ʾ
int OperatorCompare(char rest,char inside){
    if((rest == '+') or (rest == '-')){
    if((inside == '+') or (inside == '-') or (inside == '*') or (inside == '/')) return 0;
    else if((inside == '(') or (inside == '?')) return 1;
    else return 0;
    }
    else if((rest == '*') or (rest == '/')){
    if((inside == '+') or (inside == '-') or (inside == '(') or (inside == '?')) return 1;
    else if((inside == '*') or (inside == '/')) return 0;
    else return 0;
    }
    else if(rest == '('){
    return 1;
    }
    else if(rest == ')'){
    if (inside=='(')return 2;
    else return 0;
    }
    else if(rest == '#'){
    if (inside=='?')return 1;
    else return 0;
    }
    else return 0;
}

//����ȫ�ֱ�����ά������ջ�Ͳ�����ջ
LiStack ope;
LiStack_int num;

int main()
{
    InitStack_int(num);
    InitStack(ope);
    Push(ope,'?');//Ϊ��֤OperatorCompare������ʼ״̬��������������Ԥ����ջһ��Ԫ�ء�������ά�������ջ����������
    char expression[100];//�������׺���ʽ�����ַ���Ϊ100
    cin>> expression;
    int i=0;
    while(expression[i]!='\0'){//�ַ���Ϊ������־��/0��ʱִ��ѭ��
        if((expression[i] == '+') or (expression[i] == '-') or (expression[i] == '*') or (expression[i] == '/') or (expression[i] == '(') or (expression[i] == ')') or (expression[i] == '#')){
        //�жϴ���ջ�������ջ������������ȼ�
        char top;//ջ�������
        int level;//���ȼ�
        do{
            top = GetTop_Stack(ope);
            level = OperatorCompare(expression[i],top);//����Ԥ���OperatorCompare�����������ȼ�
            if(level == 1){//�������ջ
                Push(ope,expression[i]);
                break;
            }
            else if(level == 0){//������޷���ջ������������ջ������������������Ӧ����
                int a,b;
                Pop_int(num,b);
                Pop_int(num,a);
                int next=0;//����������
                char next_char;//�����������������
                Pop(ope,next_char);
                switch(next_char)
                {
                case'+':
                    next=b+a;
                    break;
                case'-':
                    next=a-b;
                    break;
                case'*':
                    next=b*a;
                    break;
                case'/':
                    next=a/b;
                    break;
                }
                Push_int(num,next);//���������������������ջ����������ʹ��
            }
            else if(level == 2){
                char brackets;
                Pop(ope,brackets);
            }
        }while(level==0);
        }
        else{
            int p=expression[i]-'0';//���ڲ������������char��ת��Ϊint�ͺ�ѹ�������ջ
            Push_int(num,p);
        }
        i++;
    }
    cout<<GetTop_Stack_int(num)<<endl;//���ղ�����ջ��ʣ��Ĳ�������Ϊ������
}
