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

//平均时间复杂度 nlogn
//最坏时间复杂度 nlogn
//最优时间复杂度 nlogn
template<class T>
class Heap {
private:
    // 下沉；顾名思义，在heap tree中把指定的parentIdx沿着树下沉到正确的位置
    static void sink(T &arr, int parentIdx, int size) {
        while (2 * parentIdx + 1 < size) {
            // get child node index
            int leftChildIdx = 2 * parentIdx + 1;
            int rightChildIdx = leftChildIdx + 1;

            // get the larger child
            int maxChildIdx = leftChildIdx;
            if (rightChildIdx <= size) {
                if (arr[leftChildIdx] < arr[rightChildIdx]) {
                    maxChildIdx++;
                }
            }

            // compare child and parent
            // if parent > child, which is correct; break
            if (arr[maxChildIdx] < arr[parentIdx]) {
                break;
            }
            // else, swap parent and child
            swap(arr[parentIdx], arr[maxChildIdx]);
            parentIdx = maxChildIdx;
        }
    }

public:
    Heap() = default;

    static void sort(T &arr) {
        int size = arr.size();

        // first pass; heap construction
        // loop all the parent nodes; from the last parent node, to the root
        for (int parentIdx = size / 2; parentIdx >= 0; parentIdx--) {
            sink(arr, parentIdx, size);
        }

        // second pass; sort down
        // 此时，数组中最大的值必然在root；把root和队列尾部的元素交换，，固定尾部元素
        // 然后再对新root做下沉操作，就可以得到下一个最大值，循环往复
        while (size > 0) {
            swap(arr[0], arr[size - 1]);
            size--;
            sink(arr, 0, size);
        }
    }
};

//int main() {
//
//    vector<int> d = {1,1,1,1,1,5,4,3,2,9,8,7,6};
//    cout << "输入数组" << endl;
//    for (int i = 0; i < d.size(); i++) {
//        cout << d[i] << " ";
//    }
//    Heap<vector<int>>::sort(d);
//    cout << "排序后结果：";
//    for (int i = 0; i < d.size(); i++) {
//        cout << d[i] << " ";
//    }
//}