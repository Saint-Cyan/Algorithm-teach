#include <iostream>

void merge(int ans[], int low, int high, int buf[]);
/**
 * 并归排序算法，时间复杂度nlogn
 * 并归的本质是合并和递归，也算是入门算法中比较重要的一些概念了，这个算法是我实现的，可能会有错误，仅供参考。
 */
void merge_sort(int ans[], int low, int high, int buf[])
{

    if (low < high)
    {
        int mid = (low + high) / 2;
        merge_sort(ans, low, mid, buf);
        merge_sort(ans, mid + 1, high, buf);
        merge(ans, low, high, buf);
    }
}

// 实现合并操作
void merge(int ans[], int low, int high, int buf[])
{
    int mid = (low + high) / 2;

    int ans_index = low;
    int low_index = low;
    int high_index = mid + 1;

    while (low_index < mid + 1 && high_index < high + 1)
    {
        // 这里是从低到高排序，如果是从低到高就是大于号
        if (buf[low_index] < buf[high_index])
        {
            ans[ans_index++] = buf[low_index++];
        }
        else
        {
            ans[ans_index++] = buf[high_index++];
        }
    }

    while (low_index < mid + 1)
    {
        ans[ans_index++] = buf[low_index++];
    }

    while (high_index < high + 1)
    {
        ans[ans_index++] = buf[high_index++];
    }
}

int main(void)
{
    int arr[] = {11, 44, 23, 67, 88, 65, 77, 12, 99};
    int low = 0;
    int high = 8;
    int ans[] = {11, 44, 23, 67, 88, 65, 77, 12, 99};
    merge_sort(ans, low, high, arr);

    for (int i = 0; i < 9; i++)
    {
        std::cout << ans[i] << ' ';
    }
    std::cout << std::endl;
}