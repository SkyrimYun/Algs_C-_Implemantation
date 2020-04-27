#include <iostream>
#include <vector>

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
template <class T>
void merge(T arr[], int left, int mid, int right)
{
    // smallest case: left=mid<right
    // thus mid-right needs +1
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T L[n1];
    T R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2)
    {
        if (L[i] >= R[j])
        {
            arr[k++] = R[j++];
        }
        else
        {
            arr[k++] = L[i++];
        }
    }

    //Copy the remaining elements of L[], if there are any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }

    //Copy the remaining elements of R[], if there are anY
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

template <typename T>
void mergesort(T arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (right + left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

//平均时间复杂度 nlogn
//最坏时间复杂度 n^2
//最优时间复杂度 nlogn
template <class T>
int partition(T arr[], int left, int right)
{
    int i = left, j = right, x = arr[left];
    while (i < j)
    {
        // scan i from left to right if s[i]<s[l]
        while (i < j && arr[i] < x)
            i++;
        if (i < j)
            arr[j--] = arr[i];
        // sacn j from right to left if s[j]>s[l]
        while (i < j && arr[j] >= x)
            j--;
        if (i < j)
            arr[i++] = arr[j];
    }
    arr[i] = x;
    return i;
}

template <class T>
int threeWayPartition(T arr[], int left, int right)
{
    int i = left;
    T v = arr[left];
    int lt = left;
    int gt = right;

    while (i <= right)
    {
        if (arr[i] < v)
        {
            swap(arr[lt++], arr[i++]);
        }
        if (arr[i] == v)
        {
            i++;
        }
        if (arr[i] > v)
        {
            swap(arr[i], arr[gt--]);
        }
    }
    arr[i] = v;
    return i;
}

template <typename T>
void quickSort(T s[], int l, int h)
{
    if (l < h)
    {
        int i = threeWayPartition(s, l, h);

        quickSort(s, l, i - 1);
        quickSort(s, i + 1, h);
    }
}

//平均时间复杂度 2nlogn
//最坏时间复杂度 2nlogn
//最优时间复杂度 nlogn
template <class T>
class Heap
{
private:
    // with all arr[] operation the index needs to minus 1 becuase in heap tree the index begins with 1 not 0
    static void sink(T &arr, int k, int size)
    {
        while (2 * k <= size)
        {
            int j = 2 * k;
            // get the larger child
            if (2 * k + 1 <= size)
                if (arr[2 * k - 1] < arr[2 * k + 1 - 1])
                    j++;
            if (arr[j - 1] < arr[k - 1])
                break;
            swap(arr[k - 1], arr[j - 1]);
            k = j;
        }
    }

public:
    Heap() {}
    static void sort(T &arr)
    {
        int size = arr.size();
        // first pass; heap construction
        for (int k = size / 2; k >= 1; k--)
            sink(arr, k, size);
        // second pass; sortdown
        while (size > 1)
        {
            swap(arr[1 - 1], arr[size - 1]);
            size--;
            sink(arr, 1, size);
        }
    }
};

int main()
{
    // int d[] = {12, 15, 9, 20, 6, 31, 24};
    // cout << "输入数组  { 12, 15, 9, 20, 6, 31, 24 } " << endl;
    // mergesort(d, 0, 6);
    // cout << "排序后结果：";
    // for (int i = 0; i < 7; i++)
    // {
    //     cout << d[i] << " ";
    // }

    vector<int> d = {12, 15, 9, 20, 6, 31, 24};
    cout << "输入数组  { 12, 15, 9, 20, 6, 31, 24 } " << endl;
    Heap<vector<int>>::sort(d);
    cout << "排序后结果：";
    for (int i = 0; i < 7; i++)
    {
        cout << d[i] << " ";
    }
}