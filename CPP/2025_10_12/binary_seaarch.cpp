#include <iostream>   // 用于输入输出
#include <vector>    // 必须包含，否则编译器不认识std::vector


/**
 * @brief 二分查找算法
 * 功能：在有序容器中查找是否存在指定的元素val
 * 返回值：如果找到元素，返回true；如果未找到元素，返回false
 * 参数：
 * binary_search(beg, end, val)：在有序容器中查找是否存在指定的元素val
 *      beg：容器开始迭代器
 *      end：容器结束迭代器
 *      val：要查找的元素
 *      return：如果找到元素，返回true；如果未找到元素，返回false
 */


//二分查找实现
// 在有序数组v中查找target，返回索引（-1表示未找到）
int binary_Search(const std::vector<int>& v, int target) {
    int left = 0;
    int right = v.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // 避免溢出（等价于 (left+right)/2）
        
        if (v[mid] == target) {
            return mid; // 找到目标，返回索引
        } else if (v[mid] < target) {
            left = mid + 1; // 目标在右半部分
        } else {
            right = mid - 1; // 目标在左半部分
        }
    }
    
    return -1; // 未找到
}
int main() {
    std::vector<int> nums = {1, 3, 5, 7, 9, 11, 13};  // 有序容器（升序）
    int target = 7;
    
    int index = binary_Search(nums, target);
    if (index != -1) {
        std::cout << "找到目标 " << target << "，索引为：" << index << std::endl;
    } else {
        std::cout << "未找到目标 " << target << std::endl;
    }
    
    return 0;
}