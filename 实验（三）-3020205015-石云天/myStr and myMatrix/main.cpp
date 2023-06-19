#include <iostream>
#include <cstring>
#define maxnum  100
using namespace std;

class myStr
{
public:
    char str[maxnum];
    //字符串初始化，以'\0'结尾
    int next[maxnum];
    myStr()
    {
        str[0] = '\0';
    }
    //字符串销毁
    ~myStr()
    {
        str[0] = '\0';
    }
    //next数组的计算
    void Getnext()
    {
        int i = 0, j = -1;
        next[0] = -1;
        while(str[i] != '\0')
        {
            if(j == -1 || str[i] == str[j])
            {
                i++;
                j++;
                next[i] = j;
            }
            else
            {
                j = next[j];
            }
        }
    }
    //打印next数组
    void Printnext()
    {
        int i = 0;
        while(str[i] != '\0')
        {
            cout << next[i] << " ";
            i++;
        }
        cout << endl;
    }
    //简单字符串匹配
    int Simplematch(myStr &s, int pos = 1)
    {
        int i = pos-1, j = 0;
        while(str[i] != '\0' && s.str[j] != '\0')
        {
            if(str[i] == s.str[j])
            {
                i++;
                j++;
            }
            else
            {
                i = i - j + 1;
                j = 0;
            }
        }
        if(s.str[j] == '\0')
        {
            return i - j+1;
        }
        else
        {
            return -1;
        }
    }
    //改进KMP字符串匹配
    int KMPmatch(myStr &s, int pos = 1)
    {
        int i = pos-1, j = 0;
        while((str[i] != '\0' && s.str[j] != '\0')||j == -1)
        {
            if(j == -1 || str[i] == s.str[j])
            {
                i++;
                j++;
            }
            else
            {
                j = s.next[j];
            }
        }
        if(s.str[j] == '\0')
        {
            return i - j + 1;
        }
        else
        {
            return -1;
        }
    }
    //串的替换
    int Replace(myStr &s, myStr &t, int pos)
    {
        int i = pos, j = 0;
        i = KMPmatch(s, i);
        if(i != -1)
        {
            int lt = strlen(t.str);
            int ls = strlen(s.str);
            int k = i + ls - 1;//保留的位置
            char temp[maxnum];
            int f = 0;
            while(t.str[f] != '\0')
            {
                temp[f] = t.str[f];
                f++;
            }
            while(str[k] != '\0')
            {
                temp[f] = str[k];
                k++;
                f++;
            }
            temp[f] = '\0';
            k = i - 1;
            while(f >= 0)
            {
                str[k] = temp[j];
                k++;
                j++;
                f--;
            }
            return 1;
        }
        else
        {
            return 0;
        }

    }
    //打印字符串
    void StrPrint()
    {
        int i = 0;
        while(str[i] != '\0')
        {
            cout << str[i];
            i++;
        }
        cout << endl;
    }

};

//稀疏矩阵
class myMatrix
{
public:
    struct element
    {
        int row, col, value;
    };
    element data[maxnum];
    int row, col, num;
    myMatrix()
    {
        row = col = num = 0;
    }
    ~myMatrix()
    {
        row = col = num = 0;
    }
    //稀疏矩阵初始化
    void InitMatrix()
    {
        cout << "请输入矩阵的行数、列数和非零元素个数：" << endl;
        cin >> row >> col >> num;
        cout << "请输入非零元素的行号、列号和值：" << endl;
        for(int i = 0; i < num; i++)
        {
            cin >> data[i].row >> data[i].col >> data[i].value;
        }
    }
    //打印矩阵：行，列，值
    void PrintMatrix()
    {
        for(int i = 0; i < num; i++)
        {
            cout << data[i].row << " " << data[i].col << " " << data[i].value << endl;
        }
    }
    //稀疏矩阵的快速转置
    void TransposeMatrix(myMatrix &m)
    {
        int i, j, k, colnum[maxnum], rowpos[maxnum];
        m.row = col;
        m.col = row;
        m.num = num;
        if(num > 0)
        {
            for(i = 0; i < col; i++)
            {
                colnum[i] = 0;
            }
            for(i = 0; i < num; i++)
            {
                colnum[data[i].col]++;
            }
            rowpos[0] = 0;
            for(i = 1; i < col; i++)
            {
                rowpos[i] = rowpos[i - 1] + colnum[i - 1];
            }
            for(i = 0; i < num; i++)
            {
                j = data[i].col;
                k = rowpos[j];
                m.data[k].row = data[i].col;
                m.data[k].col = data[i].row;
                m.data[k].value = data[i].value;
                rowpos[j]++;
            }
        }
    }

};

int main()
{
    myStr a,b,c;
    int num;
    cout << "请输入主串：" << endl;
    cin >> a.str;
    cout << "请输入子串：" << endl;
    cin >> b.str;
    cout << "请输入替换串：" << endl;
    cin >> c.str;
    b.Getnext();
    cout << "next数组为：" << endl;
    b.Printnext();
    cout << "简单匹配结果为：" << a.Simplematch(b) << endl;
    cout << "KMP匹配结果为：" << a.KMPmatch(b) << endl;
    cout << "请输入替换位置：" << endl;
    cin >> num;
    a.Replace(b,c,num);
    cout << "替换后的串为：" << endl;
    a.StrPrint();

    myMatrix m, n;
    m.InitMatrix();
    m.TransposeMatrix(n);
    cout << "转置后的结果为" << endl;
    n.PrintMatrix();
    return 0;
}
