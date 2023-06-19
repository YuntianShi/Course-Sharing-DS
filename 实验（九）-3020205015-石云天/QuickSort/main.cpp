#include <iostream>

using namespace std;

void QuickSort(int *array, int low, int high){//快速排序
    if(low >= high){//若待排序序列只有一个元素，返回空
        return ;
    }
    int i = low;//i作为指针从左向右扫描
    int j = high;//j作为指针从右向左扫描
    int key = array[low];//第一个数作为基准数
    while(i < j){
        while(array[j] >= key && i < j){//从右侧寻找小于基准数的元素 （此处仍需判断i是否小于j）
            j--;//找不到则j-1
        }
        array[i] = array[j];//找到则赋值
        while(array[i] <= key && i < j){//从左边找大于基准数的元素
            i++;//找不到则i+1
        }
        array[j] = array[i];//找到则赋值
    }
    array[i] = key;//当i和j相遇，将基准元素赋值到指针i处
    QuickSort(array, low, i - 1);//i左侧序列递归调用快排
    QuickSort(array, i + 1, high);//i右侧序列递归调用快排
}
int main(){
    int array[] = {21, 25, 49, 25, 16, 8};
    int length = sizeof(array) / sizeof(*array);
    cout << "待排序序列：";
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << endl;
    QuickSort(array, 0, length - 1);
    cout << "排序后序列：";
    for(int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    return 0;
}
