#pragma once
#include <iostream>
#include <vector>

namespace ZSort{

class Sort {
public:
    void pop_sort(vector<int>& arr);                   // 冒泡排序-基础
    void pop_sort_optimization(vector<int>& arr);      // 冒泡排序-序而不排
    void select_sort(vector<int>& arr);                // 选择排序-基础
    void select_sort_optimization(vector<int>& arr);   // 选择排序-比而不换
    void insert_sort(vector<int>& arr);                // 插入排序
    void shell_sort(vector<int>& arr);                 // 希尔排序
    void quick_sort(vector<int>& arr,
                    const int& start,
                    const int& end);                   // 快速排序
    void merge_sort(vector<int>& arr,
                    const int& start,
                    const int& end);                   // 归并排序
    void heap_sort(vector<int>& arr);                  // 堆排序

private:
    void swap_num_(int& num1, int& num2);  // 元素交换
    const int three_median_(const vector<int>& arr,
                            const int& low,
                            const int& high);  // 快速排序取基准值-三数取中
    void insert_sort_(vector<int>& arr,
                      const int& start,
                      const int& end);  // 快速排序剩余数组元素过少-插入排序
    void max_heapify_(vector<int>& arr,
                       const int& start,
                       const int& end);  // 大顶堆构建
    void merge_array_inner_(vector<int>& arr,
                            vector<int>& temp,
                            const int& start,
                            const int& mid,
                            const int& end);  // 在同个数组内合并两个有序数组
};

}  // namespace ZSort
