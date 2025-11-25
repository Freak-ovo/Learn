# ==============================================
# 元组(tuple)操作示例
# 元组是有序、不可修改的容器、允许重复元素，使用圆括号()定义
#      元组的特性：
# 1. 元素可以是任意类型，允许重复
# 2. 一旦定义，元素不能被修改、添加或删除
# 3. 支持索引访问和切片操作
# 4. 比列表更节省内存，访问速度更快
#   元组的常用方法
# 1. index()：返回元素首次出现的索引
# 2. count()：返回元素出现的次数
# 3. len()：返回元组中元素的数量
# ==============================================


# ------------------------------
# 1. 元组的定义与初始化
# ------------------------------

# 定义空元组
empty_tuple = ()
print("空元组:", empty_tuple, "类型:", type(empty_tuple))

# 定义单个元素的元组（注意必须加逗号，否则会被视为普通类型）
single_element_tuple = ("苹果",)  # 正确定义
not_tuple = ("苹果")  # 这是字符串，不是元组
print("单个元素的元组:", single_element_tuple, "类型:", type(single_element_tuple))
print("容易混淆的非元组:", not_tuple, "类型:", type(not_tuple))

# 定义多个元素的元组
fruit_tuple = ("苹果", "香蕉", "橙子", "葡萄", "苹果")
print("水果元组:", fruit_tuple)

# 定义包含不同类型元素的元组
mixed_tuple = (10, "hello", 3.14, True, [1, 2, 3])
print("混合类型元组:", mixed_tuple)

# 定义嵌套元组
nested_tuple = (("张三", 20), ("李四", 25), ("王五", 30))
print("嵌套元组:", nested_tuple)


# ------------------------------
# 2. 元组元素的访问
# ------------------------------

# 通过索引访问元素（索引从0开始）
print("\n访问水果元组第2个元素:", fruit_tuple[1])  # 香蕉
print("访问混合元组第3个元素:", mixed_tuple[2])     # 3.14

# 访问嵌套元组的元素
print("访问嵌套元组中的姓名:", nested_tuple[0][0])  # 张三
print("访问嵌套元组中的年龄:", nested_tuple[1][1])  # 25

# 负索引访问（从末尾开始，-1表示最后一个元素）
print("访问最后一个水果:", fruit_tuple[-1])  # 苹果
print("访问倒数第二个水果:", fruit_tuple[-2])  # 葡萄

# 切片操作（获取子元组）
# 语法：tuple[start:end:step]，包含start，不包含end
print("水果元组的前3个元素:", fruit_tuple[:3])  # ("苹果", "香蕉", "橙子")
print("水果元组的第2到第4个元素:", fruit_tuple[1:4])  # ("香蕉", "橙子", "葡萄")
print("每隔一个取水果:", fruit_tuple[::2])  # ("苹果", "橙子", "苹果")


# ------------------------------
# 3. 元组的常用操作和方法
# ------------------------------

# 计算元组长度
print("\n水果元组的长度:", len(fruit_tuple))  # 5

# 统计元素出现次数
print("'苹果'在水果元组中出现的次数:", fruit_tuple.count("苹果"))  # 2

# 查找元素首次出现的索引（元素不存在会报错）
print("'橙子'在水果元组中的索引:", fruit_tuple.index("橙子"))  # 2

# 元组的连接（生成新元组，原元组不变）
tuple1 = (1, 2, 3)
tuple2 = (4, 5, 6)
combined_tuple = tuple1 + tuple2
print("连接后的元组:", combined_tuple)  # (1, 2, 3, 4, 5, 6)
print("原元组1不变:", tuple1)  # (1, 2, 3)

# 元组的重复
repeat_tuple = ("A", "B") * 3
print("重复后的元组:", repeat_tuple)  # ("A", "B", "A", "B", "A", "B")


# ------------------------------
# 4. 元组的不可修改性（重要特性）
# ------------------------------

print("\n元组不可修改的演示:")
try:
    # 尝试修改元组元素（会报错）
    fruit_tuple[0] = "西瓜"
except TypeError as e:
    print("修改元素时的错误:", e)

try:
    # 尝试删除元组元素（会报错）
    del fruit_tuple[1]
except TypeError as e:
    print("删除元素时的错误:", e)

# 注意：如果元组中包含可变元素（如列表），该元素内部可以修改
print("\n元组中可变元素的修改:")
print("修改前的混合元组:", mixed_tuple)
mixed_tuple[4].append(4)  # 修改元组中的列表元素
print("修改后的混合元组:", mixed_tuple)


# ------------------------------
# 5. 元组的遍历
# ------------------------------

print("\n遍历水果元组:")
for fruit in fruit_tuple:
    print(fruit)

print("\n带索引遍历嵌套元组:")
for index, person in enumerate(nested_tuple):
    print(f"索引{index}: 姓名={person[0]}, 年龄={person[1]}")


# ------------------------------
# 6. 元组与列表的转换
# ------------------------------

# 元组转列表（可用于修改操作）
fruit_list = list(fruit_tuple)
fruit_list[0] = "西瓜"
print("\n元组转列表并修改:", fruit_list)

# 列表转元组（可用于保护数据不被修改）
new_tuple = tuple(fruit_list)
print("列表转元组:", new_tuple)
