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

//����ȫ�ֱ�����ά������ջ
LiStack ope;

int main()
{
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
            level = OperatorCompare(expression[i],top);
            if(level == 1){//�������ջ
                Push(ope,expression[i]);
                break;
            }
            else if(level == 0){//������޷���ջ����ӡջ�����������
                char next_char;
                Pop(ope,next_char);
                cout<< next_char <<' ';
            }
            else if(level == 2){
                char brackets;
                Pop(ope,brackets);
            }
        }while(level==0);
        }
        else{//���ڲ�������ֱ�Ӵ�ӡ����
            cout<<expression[i]<<' ';
        }
        i++;
    }
    cout<<'#'<<endl;
}
