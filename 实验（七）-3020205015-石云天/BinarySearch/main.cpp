#include<bits/stdc++.h>
using namespace std;

int BinarySearch(int arr[],int length,int key)
{
    int low = 0;//�����ʼ��С
    int high = length - 1;//�����ʼ���
    int mid;//�����м�ֵ
    while(low <= high)
    {
        mid = (low + high) / 2;//���м�ֵ
        if(key == arr[mid])//�ж�min��key�Ƿ����
        return mid;
        else if(key > arr[mid])//���key>mid ������Ϊ[mid+1,high]
        low = mid + 1;
        else//���key<mid ������Ϊ[liw,mid-1]
        high = mid - 1;
    }
    return -1;//�����������Ŀ��ֵkey,�򷵻�-1��
}

int main()
{
    cout << "����һ " << endl;
    int arr[11] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};
    cout << BinarySearch(arr,(sizeof(arr) / sizeof(arr[0])),21);
    cout << endl;
    cout << "���Զ� " << endl;
    cout << BinarySearch(arr,(sizeof(arr) / sizeof(arr[0])),70);
}
