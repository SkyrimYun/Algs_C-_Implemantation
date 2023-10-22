#include <iostream>
#include <vector>

using namespace std;

//平均时间复杂度  O(n^{2})
//最坏时间复杂度  O(n^{2})
//最优时间复杂度  O(n^{2})
template<typename T>
void bubblesort(T arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - 1 - i; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

//平均时间复杂度  O(n^{2})
//最坏时间复杂度  O(n^{2})
//最优时间复杂度  O(n^{2})
template<typename T>
void selectionSort(T a[], int len) {
    for (int i = 0; i < len - 1; i++) {
        int min = i;
        for (int j = i + 1; j < len; j++)     //走訪未排序的元素
        {
            if (a[j] < a[min])    //找到目前最小值
            {
                min = j;    //紀錄最小值
            }
        }
        if (min != i) {
            swap(a[min], a[i]);
        }
    }
}

//平均时间复杂度  O(n^{2})
//最坏时间复杂度  O(n^{2})
//最优时间复杂度  O(n)
template<typename T>
void insertsort(T arr[], int len) {
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;
        while ((j >= 0) && (key < arr[j])) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

//平均时间复杂度 nlogn
//最坏时间复杂度 nlogn
//最优时间复杂度 nlogn
template<class T>
void merge(vector<T> &arr, int left, int mid, int right) {
    // smallest case: left=mid<right
    // thus mid-right needs +1
    int n1 = mid - left + 1;
    int n2 = right - mid;

    T L[n1];
    T R[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }

    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k++] = R[j++];
        } else {
            arr[k++] = L[i++];
        }
    }

    //Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    //Copy the remaining elements of R[], if there are anY
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

template<typename T>
void mergesort(vector<T> &arr, int left, int right) {
    if (left < right) {
        int mid = (right + left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

//平均时间复杂度 nlogn
//最坏时间复杂度 n^2
//最优时间复杂度 nlogn
template<class T>
int partition(vector<T>& arr, int left, int right) {
    int pivot = arr[left];
    while (left < right) {
        // sacn j from right to left if s[j]>s[l]
        while (arr[right] > pivot) {
            right--;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
            left++;
        }
        // scan i from left to right if s[i]<s[l]
        while (arr[left] < pivot) {
            left++;
        }
        if (left < right) {
            swap(arr[left], arr[right]);
            right--;
        }
    }
    return left;
}

template<typename T>
void quickSort(std::vector<T> &s, int l, int h) {
    if (l < h) {
        int i = partition(s, l, h);

        quickSort(s, l, i - 1);
        quickSort(s, i + 1, h);
    }
}

//平均时间复杂度 2nlogn
//最坏时间复杂度 2nlogn
//最优时间复杂度 nlogn
template<class T>
class Heap {
private:
    // with all arr[] operation the index needs to minus 1 becuase in heap tree the index begins with 1 not 0
    static void sink(T &arr, int k, int size) {
        while (2 * k <= size) {
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

    static void sort(T &arr) {
        int size = arr.size();
        // first pass; heap construction
        for (int k = size / 2; k >= 1; k--)
            sink(arr, k, size);
        // second pass; sortdown
        while (size > 1) {
            swap(arr[1 - 1], arr[size - 1]);
            size--;
            sink(arr, 1, size);
        }
    }
};

int main() {

    vector<int> d = {1,1,1,1,1,5,4,3,2,9,8,7,6};
    cout << "输入数组" << endl;
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
    quickSort(d, 0, d.size() - 1);
    cout << "排序后结果：";
    for (int i = 0; i < d.size(); i++) {
        cout << d[i] << " ";
    }
}