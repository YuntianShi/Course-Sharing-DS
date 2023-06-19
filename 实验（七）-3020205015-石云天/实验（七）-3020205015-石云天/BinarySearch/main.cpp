#include<bits/stdc++.h>
using namespace std;

int BinarySearch(int arr[],int length,int key)
{
    int low = 0;//定义初始最小
    int high = length - 1;//定义初始最大
    int mid;//定义中间值
    while(low <= high)
    {
        mid = (low + high) / 2;//找中间值
        if(key == arr[mid])//判断min与key是否相等
        return mid;
        else if(key > arr[mid])//如果key>mid 新区间为[mid+1,high]
        low = mid + 1;
        else//如果key<mid 新区间为[liw,mid-1]
        high = mid - 1;
    }
    return -1;//如果数组中无目标值key,则返回-1；
}

int main()
{
    cout << "测试一 " << endl;
    int arr[11] = {5, 13, 19, 21, 37, 56, 64, 75, 80, 88, 92};
    cout << BinarySearch(arr,(sizeof(arr) / sizeof(arr[0])),21);
    cout << endl;
    cout << "测试二 " << endl;
    cout << BinarySearch(arr,(sizeof(arr) / sizeof(arr[0])),70);
}
