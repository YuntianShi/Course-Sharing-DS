#include <iostream>
using namespace std;
#define DEFAULT_SIZE 10

struct KeyType
{
    int key;
    bool otherInfo;//��¼�����Ƿ����*
    KeyType() {}
    KeyType(int key, bool other = false) : key(key), otherInfo(other){}
    bool operator<(const KeyType &other) const{ return key < other.key;}
};

ostream &operator<<(ostream &out, KeyType &k){//���������������������
    out << k.key << (k.otherInfo ? "*" : "");
    return out;
}

class SqList//˳���
{
    private:
        KeyType *data;//ͨ��ָ����С������
        int size;//����������
    public:
        SqList(int size = DEFAULT_SIZE);//ͨ��ָ����С������
        SqList(KeyType *data, int size);//ͨ��ָ�����鴴����
        ~SqList(){ delete[] data;}//��������
        int GetSize(){ return size;}//��ȡ����������
        void PrintList();//��ӡ��������
        KeyType &operator[](int index){ return data[index];}//�����±������
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

void ShellSort(SqList &table){//ϣ������
    int i, j, gap, n = table.GetSize();
    for(gap = n / 2; gap > 0; gap /= 2){//ֱ�Ӳ�������
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
    cout << "����ǰ��" << endl;
    table.PrintList();
    cout << "�����" << endl;
    ShellSort(table);
    table.PrintList();
    return 0;
}
