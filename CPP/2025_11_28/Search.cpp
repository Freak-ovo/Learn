/**
 * @file Search.cpp
 * @author your name (you@domain.com)
 * @brief 查找算法
 * @version 0.1
 * @date 2025-11-28
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include <iostream>
#include <vector>

// 二分查找
/**
 * @brief 二分查找 : 在已排序的数组中查找目标值 “target”，如果找到则返回索引，否则返回-1。
 * @note 数组必须是升序排列的。
 * 
 * @param arr 数组
 * @param size 数组大小
 * @param target 目标值
 * @return int 目标值索引，未找到返回-1
 */
int binarySearchIterative(const std::vector<int>& arr, int target) {
    int left = 0;                  // 查找范围左边界
    int high = arr.size() - 1;    // 查找范围右边界

    while (left <= high) {
        // 计算中间位置（避免low+high溢出，等价于(low+high)/2）
        int mid = left + (high - left) / 2;

        if (arr[mid] == target) {
            return mid;  // 找到目标，返回下标
        } else if (arr[mid] < target) {
            left = mid + 1;  // 目标在右半部分，调整左边界
        } else {
            high = mid - 1; // 目标在左半部分，调整右边界
        }
    }

    return -1; // 未找到目标
}

/**
 * @brief 递归辅助函数：在arr[left...high]范围内查找target
 * 
 * @param arr 数组
 * @param target 目标值
 * @param left 低索引
 * @param high 高索引
 * @return int 目标值索引，未找到返回-1
 */
int binarySearchRecursive(const std::vector<int>& arr, int target, int left, int high) {
    if (left > high) {
        return -1; // 递归终止：未找到
    }

    int mid = left + (high - left) / 2; // 计算中间位置
    if (arr[mid] == target) {
        return mid; // 找到目标
    } else if (arr[mid] < target) {
        // 递归查找右半部分
        return binarySearchRecursive(arr, target, mid + 1, high);
    } else {
        // 递归查找左半部分
        return binarySearchRecursive(arr, target, left, mid - 1);
    }
}

/**
 * @brief 递归封装：在arr[0...size-1]范围内查找target
 * @note 递归逻辑需要 low 和 high 来限定查找范围，但用户调用时只关心 “数组” 和 “目标值”，不需要知道内部的边界参数（比如初始的 low=0、high=size-1）。
        封装后对外只暴露 binarySearchRecursive(arr, target)，
        而把需要额外参数的 binarySearchRecursiveHelper(arr, target, low, high) 隐藏起来
         —— 用户无需手动传递 low/high，既减少了参数错误的可能（比如传错初始边界），也让调用更直观。
 * 
 * @param arr 数组
 * @param target 目标值
 * @return int 目标值索引，未找到返回-1
 */
int binarySearchRecursive(const std::vector<int>& arr, int target) {
    return binarySearchRecursive(arr, target, 0, arr.size() - 1);
}






int main() {
    std::vector<int> arr = {2, 4, 6, 8, 10, 12, 14};
    int target1 = 8;
    int target2 = 5;

    int result1 = binarySearchRecursive(arr, target1);
    int result2 = binarySearchRecursive(arr, target2);

    std::cout << "目标值 " << target1 << (result1 != -1 ? " 找到，下标：" + std::to_string(result1) : " 未找到") << std::endl;
    std::cout << "目标值 " << target2 << (result2 != -1 ? " 找到，下标：" + std::to_string(result2) : " 未找到") << std::endl;

    return 0;
}