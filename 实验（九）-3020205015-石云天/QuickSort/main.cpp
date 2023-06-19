#include <iostream>

using namespace std;

void QuickSort(int *array, int low, int high){//��������
    if(low >= high){//������������ֻ��һ��Ԫ�أ����ؿ�
        return ;
    }
    int i = low;//i��Ϊָ���������ɨ��
    int j = high;//j��Ϊָ���������ɨ��
    int key = array[low];//��һ������Ϊ��׼��
    while(i < j){
        while(array[j] >= key && i < j){//���Ҳ�Ѱ��С�ڻ�׼����Ԫ�� ���˴������ж�i�Ƿ�С��j��
            j--;//�Ҳ�����j-1
        }
        array[i] = array[j];//�ҵ���ֵ
        while(array[i] <= key && i < j){//������Ҵ��ڻ�׼����Ԫ��
            i++;//�Ҳ�����i+1
        }
        array[j] = array[i];//�ҵ���ֵ
    }
    array[i] = key;//��i��j����������׼Ԫ�ظ�ֵ��ָ��i��
    QuickSort(array, low, i - 1);//i������еݹ���ÿ���
    QuickSort(array, i + 1, high);//i�Ҳ����еݹ���ÿ���
}
int main(){
    int array[] = {21, 25, 49, 25, 16, 8};
    int length = sizeof(array) / sizeof(*array);
    cout << "���������У�";
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << endl;
    QuickSort(array, 0, length - 1);
    cout << "��������У�";
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    return 0;
}
