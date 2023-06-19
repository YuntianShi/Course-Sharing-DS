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

//设置全局变量，维护符号栈
LiStack ope;

int main()
{
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
            level = OperatorCompare(expression[i],top);
            if(level == 1){//运算符入栈
                Push(ope,expression[i]);
                break;
            }
            else if(level == 0){//运算符无法入栈，打印栈顶运算符即可
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
        else{//对于操作数，直接打印即可
            cout<<expression[i]<<' ';
        }
        i++;
    }
    cout<<'#'<<endl;
}
