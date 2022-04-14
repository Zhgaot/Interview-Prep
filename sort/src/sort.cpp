#include "sort.h"

using namespace ZSort;
using namespace std;

/* ========================= public ========================= */
/**
 * @brief 冒泡排序-基础
 * @param arr 待排序数组
*/
void Sort::pop_sort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1])
                this->swap_num_(arr[j], arr[j + 1]);
        }
    }
}

/**
 * @brief 冒泡排序-序而不排
 * @param arr 待排序数组
*/
void Sort::pop_sort_optimization(vector<int>& arr) {
    bool flag = true;
    for (int i = 0; i < arr.size() - 1; ++i) {
        flag = true;
        for (int j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                this->swap_num_(arr[j], arr[j + 1]);
                flag = false;
            }
        }
        if (flag)
            break;
    }
}

/**
 * @brief 选择排序-基础
 * @param arr 待排序数组
*/
void Sort::select_sort(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[i])
                this->swap_num_(arr[j], arr[i]);
        }
    }
}

/**
 * @brief 选择排序-比而不换
 * @param arr 待排序数组
*/
void Sort::select_sort_optimization(vector<int>& arr) {
    int index = 0;
    for (int i = 0; i < arr.size() - 1; ++i) {
        index = i;
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[index])
                index = j;
        }
        if (index != i)
            this->swap_num_(arr[i], arr[index]);
    }
}

/**
 * @brief 插入排序
 * @param arr 待排序数组
*/
void Sort::insert_sort(vector<int>& arr) {
    int temp = 0, i = 0, j = 0;
    for (i = 1; i < arr.size(); ++i) {
        temp = arr[i];
        for (j = i; j - 1 >= 0 && temp < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

/**
 * @brief 希尔排序
 * @param arr 待排序数组
*/
void Sort::shell_sort(vector<int>& arr) {
    int len = arr.size();
    int gap = len / 2;
    int temp = 0, i = 0, j = 0;
    while (gap >= 1) {
        for (i = gap; i < len; ++i) {
            temp = arr[i];
            for (j = i; j - gap >= 0 && temp < arr[j - gap]; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
        gap /= 2;
    }
}

/**
 * @brief 快速排序
 * @param arr 待排序数组
 * @param start 数组首元素
 * @param end 数组尾元素
*/
void Sort::quick_sort(vector<int>& arr, const int& start, const int& end) {
    // base case
    if (start >= end)
        return;
    // small array use insert sort
    if (end - start + 1 <= 10) {
        this->insert_sort_(arr, start, end);
        return;
    }
    // quick sort
    int i = start, j = end, left = start, right = end;
    int pivot = this->three_median_(arr, start, end);
    while (i < j) {
        while (i < j && arr[j] >= pivot) {
            if (arr[j] == pivot) {
                this->swap_num_(arr[j], arr[right]);
                --right;
            }
            --j;
        }
        arr[i] = arr[j];
        while (i < j && arr[i] <_ pivot) {
            if (arr[i] == pivot) {
                this->swap_num_(arr[i], arr[left]);
                ++left;
            }
            ++i;
        }
        arr[j] = arr[i];
    }
    arr[i] = pivot;
    // aggregate the same elements
    int p = start, q = i - 1;
    while (p < left && arr[q] != pivot) {
        this->swap_num_(arr[p], arr[q]);
        ++p;
        --q;
    }
    p = end, q = i + 1;
    while (p > right && arr[q] != pivot) {
        this->swap_num_(arr[p], arr[q]);
        --p;
        ++q;
    }
    // recursion
    int left_len = left - start, right_len = end - right;
    this->quick_sort(arr, start, i - left_len - 1);
    this->quick_sort(arr, i + right_len + 1, end);
}

/**
 * @brief 归并排序
*/
void Sort::merge_sort(vector<int>& arr, const int& start, const int& end) {
    /* 创建辅助变量 */
    static vector<int> temp(arr.size(), 0);
    int mid = start + ((end - start) >> 1);

    /* 归并之递归 */
    this->merge_sort(arr, start, mid);
    this->merge_sort(arr, mid + 1, end);

    /* 归并之合并 */
    this->merge_array_inner_(arr, temp, start, mid, end);
}

/**
 * @brief 堆排序(升序 - 大顶堆)
*/
void Sort::heap_sort(vector<int>& arr) {
    // 由最后一个非叶子节点开始，自底向上构建大顶堆
    int size = arr.size();
    for (int i = size / 2 - 1; i >= 0; --i) {
        this->max_heapify(arr, i, size - 1);
    }

    // heap sort
    for (int i = size - 1; i > 0; --i) {
        this->swap_num_(arr[0], arr[i]);
        this->max_heapify(arr, 0, i - 1);
    }
}
/* ========================= public ========================= */


/* ========================= private ========================= */
/**
 * @brief 在同一个数组内进行有序数组合并
*/
void Sort::merge_array_inner_(vector<int>& arr, vector<int>& temp,
                        const int& start, const int& mid, const int& end) {
    /* 创建辅助变量 */
    int i = start, j = mid + 1, k = start;
    int l = start;  // 用于最后将temp中的元素拷贝进arr中
    
    while (i <= mid && j <= end) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else if (arr[j] < arr[i])
            temp[k++] = arr[j++];
        else {
            temp[k++] = arr[i++];
            temp[k++] = arr[j++];
        }
    }
    if (i > mid) {
        while (j <= end)
            temp[k++] = arr[j++];
    } else {
        while (i <= mid)
            temp[k++] = arr[i++];
    }
    while (l <= end) {
        arr[l] = temp[l];
        ++l;
    }
}

/**
 * @brief 位运算法交换元素的值，仅适用于short、int、long等整型
*/
void Sort::swap_num_(int& num1, int& num2) {
    if (num1 == num2)
        return;
    num1 = num1 ^ num2;
    num2 = num1 ^ num2;
    num1 = num1 ^ num2;
}

/**
 * @brief 快速排序中取基准值(pivot)时使用的三数取中
*/
const int Sort::three_median_(const vector<int>& arr, const int& low, const int& high) {
    int mid = low + ((high - low) >> 1);
    if (arr[mid] > arr[high])
        this->swap_num_(arr[mid], arr[high]);
    if (arr[low] > arr[high])
        this->swap_num_(arr[low], arr[high]);
    if (arr[mid] > arr[low])
        this->swap_num_(arr[mid], arr[low]);
    return arr[low];
}

/**
 * @brief 快速排序中当前数组元素过少时直接使用插入排序
*/
void Sort::insert_sort_(vector<int>& arr, const int& start, const int& end) {
    int temp = 0, i = 0, j = 0;
    for (i = start + 1; i <= end; ++i) {
        temp = arr[i];
        for (j = i; j - 1 >= start && temp < arr[j - 1]; --j)
            arr[j] = arr[j - 1];
        arr[j] = temp;
    }
}

/**
 * @brief 自任一节点开始向下构建大顶堆
*/
void Sort::max_heapify_(vector<int>& arr, const int& start, const int& end) {
    int dad = start;
    int son = dad * 2 + 1;  // dad的左子节点
    while (son <= end) {
        if (son + 1 <= end && arr[son] < arr[son + 1])
            ++son;
        if (arr[son] > arr[dad]) {
            this->swap_num_(arr[son], arr[dad]);
            dad = son;
            son = dad * 2 + 1;
        } else {
            return;
        }
    }
}

/* ========================= private ========================= */