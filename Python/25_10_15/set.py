# 集合(set)操作示例
# 集合(set)是无序、不重复的容器，使用大括号{}定义
#      集合的特性：
# 1. 元素不能重复
# 2. 元素是无序的
# 3. 集合支持数学集合操作，如并集、交集、差集等

my_set = {1, 2, 3, 4, 5, 6, 7, 8, 9}
print("原始集合:", my_set)

# 添加元素
my_set.add(10)
my_set.add(1)
print("添加元素后的集合:", my_set)

# 移除元素
my_set.remove(1)
print("移除元素后的集合:", my_set)

# 随机取一个元素
random_element = my_set.pop()
print("随机取一个元素:", random_element)
print("取元素后的集合:", my_set)

# 清空集合
my_set.clear()
print("清空集合后的集合:", my_set)

# 集合的数学操作
# 并集：合并两个集合的所有元素，重复元素只保留一个
set1 = {1, 2, 3, 4, 5}
set2 = {4, 5, 6, 7, 8}
union_set = set1 | set2
print("并集:", union_set)  # {1, 2, 3, 4, 5, 6, 7, 8}

# 交集：取两个集合中共同的元素
intersection_set = set1 & set2
print("交集:", intersection_set)  # {4, 5}

# 差集：取第一个集合中不在第二个集合中的元素
difference_set = set1 - set2
print("差集:", difference_set)  # {1, 2, 3}

# 对称差集：取两个集合中不共同的元素
symmetric_difference_set = set1 ^ set2
print("对称差集:", symmetric_difference_set)  # {1, 2, 3, 6, 7, 8}

# 统计集合元素的数量
print("集合元素的数量:", len(set1))

# 集合遍历 集合不支持下标索引不能通过while循环遍历
for element in set1:
    print(element)
