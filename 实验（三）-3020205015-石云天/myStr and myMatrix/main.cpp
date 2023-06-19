#include <iostream>
#include <cstring>
#define maxnum  100
using namespace std;

class myStr
{
public:
    char str[maxnum];
    //�ַ�����ʼ������'\0'��β
    int next[maxnum];
    myStr()
    {
        str[0] = '\0';
    }
    //�ַ�������
    ~myStr()
    {
        str[0] = '\0';
    }
    //next����ļ���
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
    //��ӡnext����
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
    //���ַ���ƥ��
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
    //�Ľ�KMP�ַ���ƥ��
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
    //�����滻
    int Replace(myStr &s, myStr &t, int pos)
    {
        int i = pos, j = 0;
        i = KMPmatch(s, i);
        if(i != -1)
        {
            int lt = strlen(t.str);
            int ls = strlen(s.str);
            int k = i + ls - 1;//������λ��
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
    //��ӡ�ַ���
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

//ϡ�����
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
    //ϡ������ʼ��
    void InitMatrix()
    {
        cout << "���������������������ͷ���Ԫ�ظ�����" << endl;
        cin >> row >> col >> num;
        cout << "���������Ԫ�ص��кš��кź�ֵ��" << endl;
        for(int i = 0; i < num; i++)
        {
            cin >> data[i].row >> data[i].col >> data[i].value;
        }
    }
    //��ӡ�����У��У�ֵ
    void PrintMatrix()
    {
        for(int i = 0; i < num; i++)
        {
            cout << data[i].row << " " << data[i].col << " " << data[i].value << endl;
        }
    }
    //ϡ�����Ŀ���ת��
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
    cout << "������������" << endl;
    cin >> a.str;
    cout << "�������Ӵ���" << endl;
    cin >> b.str;
    cout << "�������滻����" << endl;
    cin >> c.str;
    b.Getnext();
    cout << "next����Ϊ��" << endl;
    b.Printnext();
    cout << "��ƥ����Ϊ��" << a.Simplematch(b) << endl;
    cout << "KMPƥ����Ϊ��" << a.KMPmatch(b) << endl;
    cout << "�������滻λ�ã�" << endl;
    cin >> num;
    a.Replace(b,c,num);
    cout << "�滻��Ĵ�Ϊ��" << endl;
    a.StrPrint();

    myMatrix m, n;
    m.InitMatrix();
    m.TransposeMatrix(n);
    cout << "ת�ú�Ľ��Ϊ" << endl;
    n.PrintMatrix();
    return 0;
}
