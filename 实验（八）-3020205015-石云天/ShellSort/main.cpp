#include <iostream>
using namespace std;
#define DEFAULT_SIZE 10

struct KeyType
{
    int key;
    bool otherInfo;//记录数据是否带有*
    KeyType() {}
    KeyType(int key, bool other = false) : key(key), otherInfo(other){}
    bool operator<(const KeyType &other) const{ return key < other.key;}
};

ostream &operator<<(ostream &out, KeyType &k){//重载输出运算符，便于输出
    out << k.key << (k.otherInfo ? "*" : "");
    return out;
}

class SqList//顺序表
{
    private:
        KeyType *data;//通过指定大小创建表
        int size;//表内数据量
    public:
        SqList(int size = DEFAULT_SIZE);//通过指定大小创建表
        SqList(KeyType *data, int size);//通过指定数组创建表
        ~SqList(){ delete[] data;}//析构函数
        int GetSize(){ return size;}//获取表内数据量
        void PrintList();//打印表内数据
        KeyType &operator[](int index){ return data[index];}//重载下标运算符
};

SqList::SqList(int size){
    this->size = size;
    data = new KeyType[size + 1];
}

SqList::SqList(KeyType *data, int size){
    this->size = size;
    this->data = new KeyType[size+1];
    for(int i = 0; i < size; i++) this->data[i + 1] = data[i];
}

void SqList::PrintList(){
    for(int i = 1; i <= size; i++) cout << data[i] << " ";
    cout << endl;
}

void ShellSort(SqList &table){//希尔排序
    int i, j, gap, n = table.GetSize();
    for(gap = n / 2; gap > 0; gap /= 2){//直接插入排序
        for(i = gap + 1; i <= n; i++){
            table[0] = table[1];
            for(j = 1 - gap; j > 0 && table[0] < table[j]; j -= gap)
                table[j + gap] = table[j];
            table[j + gap] = table[0];
        }
    }
}

int main()
{
    KeyType data[] = {21, 25, 49, {25, true}, 16, 8};
    SqList table(data, 6);
    cout << "排序前：" << endl;
    table.PrintList();
    cout << "排序后：" << endl;
    ShellSort(table);
    table.PrintList();
    return 0;
}
