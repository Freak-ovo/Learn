#include <stdio.h>

//遍历查找
int search1(int* nums, int numsSize, int target){
    for (int i = 0; i < numsSize; i++){
        if (nums[i] == target){
            return i;//循环n次 找到为止 时间复杂度O(n)
        }
    }
    return -1;

}
//有序数组数组元素按小到大排列 提前结束
int searchBreak(int* nums, int numsSize, int target){
    for (int i = 0; i < numsSize; i++){
        if (nums[i] == target){
            return i;//循环n次 找到为止 时间复杂度O(n)
        }
        if (nums[i] > target){
            break;
        }
    }
    return -1;


}


//二分查找 有序数组数组元素按小到大排列
int binarySearch(int* nums, int target, int left, int right) {
    if (left > right) return -1;
    int mid = (left + right) / 2;
    if (nums[mid] == target) return mid;
    if (nums[mid] < target) 
        return binarySearch(nums, target, mid + 1, right);
    else 
        return binarySearch(nums, target, left, mid - 1);
}
int search(int* nums, int numsSize, int target){
    return  binarySearch(nums, target, 0, numsSize - 1);

}




int main()
{
    int arr[] = {1, 3, 4, 6, 7, 8, 10, 11, 13, 15},target = 3;
    printf("%d", search(arr, 10, target));
    return 0;
}