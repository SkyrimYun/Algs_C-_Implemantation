#include <iostream>

using namespace std;

//平均时间复杂度  O(n^{2})
//最坏时间复杂度  O(n^{2})
//最优时间复杂度  O(n^{2})
template <typename T>
void bubblesort(T arr[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

//平均时间复杂度  O(n^{2})
//最坏时间复杂度  O(n^{2})
//最优时间复杂度  O(n)
template <typename T>
void insertsort(T arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        int j = len - 1;
        while (j != i)
        {
            if (arr[j] < arr[i])
                swap(arr[j], arr[i]);
            j--;
        }
    }
}

//平均时间复杂度 nlogn
//最坏时间复杂度 nlogn
//最优时间复杂度 nlogn
template <typename T>
void mergesort(T arr[], int len)
{
    T *a = arr;
    T *b = new T[len];
    for (int seg = 1; seg < len; seg += seg)
    {
        for (int start = 0; start < len; start += seg + seg)
        {
            int low = start;
            int mid = min(start + seg, len);
            int high = min(start + seg + seg, len);

            int k = low;
            int start1 = low;
            int end1 = mid;
            int start2 = mid;
            int end2 = high;

            while (start1 < end1 && start2 < end2)
            {
                b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
            }
            while (start1 < end1)
            {
                b[k++] = a[start1++];
            }
            while (start2 < end2)
            {
                b[k++] = a[start2++];
            }
        }
        T *temp = a;
        a = b;
        b = temp;
    }
    if (a != arr)
    {
        for (int i = 0; i < len; i++)
            b[i] = a[i];
        b = a;
    }
    delete[] b;
}

//平均时间复杂度 nlogn
//最坏时间复杂度 n^2
//最优时间复杂度 nlogn
template <typename T>
void quickSort(T s[], int l, int h)
{
    if (l < h)
    {
        int i = l, j = h, x = s[l];
        while (i < j)
        {
            // scan i from left to right if s[i]<s[l]
            while (i < j && s[i] < x)
                i++;
            if (i < j)
                s[j--] = s[i];
            // sacn j from right to left if s[j]>s[l]
            while (i < j && s[j] >= x)
                j--;
            if (i < j)
                s[i++] = s[j];
        }
        s[i] = x;
        quickSort(s, l, i - 1);
        quickSort(s, i + 1, h);
    }
}

int main()
{
    int d[] = {12, 15, 9, 20, 6, 31, 24};
    cout << "输入数组  { 12, 15, 9, 20, 6, 31, 24 } " << endl;
    insertsort(d, 7);
    cout << "排序后结果：";
    for (int i = 0; i < 7; i++)
    {
        cout << d[i] << " ";
    }
}