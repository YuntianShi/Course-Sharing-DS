#include <iostream>

using namespace std;

typedef struct Linknode{
    char data;
    struct Linknode *next;
}Linknode,*LiStack;

//链栈的初始化函数
void InitStack(LiStack &S){
    S = new Linknode;
    S->next = NULL;
}

//链栈的销毁
void DeleteStack(LiStack &S){
    Linknode * p = S;
    do{
        S = S->next;
        delete(p);
        p = S;
    }while(p);
}

//判断栈空 栈空返回0 栈非空返回1
int StackEmpty(LiStack S){
    if(S->next == NULL) return 0;
    else return 1;
}

//入栈
void Push(LiStack &S,char x){
    Linknode * p = new Linknode;
    S->data = x;
    p->next = S;
    S = p;
}

//出栈
void Pop(LiStack &S,char &x){
    if(!StackEmpty(S)) cout<< "The stack is EMPTY!" <<endl;//判断是否为空栈
    else{
        Linknode * p = S;
        x = p->next->data;
        S = S->next;
        delete(p);
    }
}

//返回栈顶元素
char GetTop_Stack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
        return '$';
    }//判断是否为空栈
    else{
        return S->next->data;
    }
}

//输出栈内元素(LIFO)
void PrintStack(LiStack S){
    if(!StackEmpty(S)){
        cout<< "The stack is EMPTY!" <<endl;
    }//判断是否为空栈
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

//链栈的初始化函数
void InitStack_int(LiStack_int &S){
    S = new Linknode_int;
    S->next = NULL;
}

//链栈的销毁
void DeleteStack_int(LiStack_int &S){
    Linknode_int *p = S;
    do{
        S = S->next;
        delete(p);
        p = S;
    }while(p);
}

//判断栈空 栈空返回0 栈非空返回1
int StackEmpty_int(LiStack_int S){
    if(S->next == NULL) return 0;
    else return 1;
}

//入栈
void Push_int(LiStack_int &S,int x){
    Linknode_int *p = new Linknode_int;
    S->data = x;
    p->next = S;
    S = p;
}

//出栈
void Pop_int(LiStack_int &S,int &x){
    if(!StackEmpty_int(S)) cout<< "The stack is EMPTY!" <<endl;//判断是否为空栈
    else{
        Linknode_int * p = S;
        x = p->next->data;
        S = S->next;
        delete(p);
    }
}

//返回栈顶元素
int GetTop_Stack_int(LiStack_int S){
    if(!StackEmpty_int(S)){
        cout<< "The stack is EMPTY!" <<endl;
        return '$';
    }//判断是否为空栈
    else{
        return S->next->data;
    }
}

//输出栈内元素(LIFO)
void PrintStack_int(LiStack_int S){
    if(!StackEmpty_int(S)){
        cout<< "The stack is EMPTY!" <<endl;
    }//判断是否为空栈
    else{
        Linknode_int * p = S->next;
        do{
            cout<< p->data << ' ';
            p = p->next;
        }while(p);
    }
}

//编写函数比较待入栈运算符与栈顶运算符的优先级，优先级低不入栈用0表示，优先级高入栈用1表示，左右括号相互抵消用2表示
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

//设置全局变量，维护符号栈和操作数栈
LiStack ope;
LiStack_int num;

int main()
{
    InitStack_int(num);
    InitStack(ope);
    Push(ope,'?');//为保证OperatorCompare函数初始状态有两个操作数，预先入栈一个元素‘？’以维护运算符栈的正常工作
    char expression[100];//输入的中缀表达式上限字符数为100
    cin>> expression;
    int i=0;
    while(expression[i]!='\0'){//字符不为结束标志‘/0’时执行循环
        if((expression[i] == '+') or (expression[i] == '-') or (expression[i] == '*') or (expression[i] == '/') or (expression[i] == '(') or (expression[i] == ')') or (expression[i] == '#')){
        //判断待入栈运算符与栈顶运算符的优先级
        char top;//栈顶运算符
        int level;//优先级
        do{
            top = GetTop_Stack(ope);
            level = OperatorCompare(expression[i],top);//利用预设的OperatorCompare函数计算优先级
            if(level == 1){//运算符入栈
                Push(ope,expression[i]);
                break;
            }
            else if(level == 0){//运算符无法入栈，弹出操作数栈中两个操作数进行相应运算
                int a,b;
                Pop_int(num,b);
                Pop_int(num,a);
                int next=0;//初步运算结果
                char next_char;//初步运算所用运算符
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
                Push_int(num,next);//将初步运算结果存入操作数栈供后续运算使用
            }
            else if(level == 2){
                char brackets;
                Pop(ope,brackets);
            }
        }while(level==0);
        }
        else{
            int p=expression[i]-'0';//对于操作数，将其从char型转换为int型后压入操作数栈
            Push_int(num,p);
        }
        i++;
    }
    cout<<GetTop_Stack_int(num)<<endl;//最终操作数栈中剩余的操作数即为运算结果
}
