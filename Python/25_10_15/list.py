# 数据容器介绍
# 数据容器是可以容纳多份数据的数据类型，每一份数据称为元素
# 元素可以是任意类型：数字、字符串、列表、元组、字典、集合等
# Python中常用的5类数据容器：
# - 列表(list)：有序、可修改、允许重复元素
# - 元组(tuple)：有序、不可修改、允许重复元素
# - 字符串(str)：有序、不可修改、由字符组成
# - 字典(dict)：无序（Python 3.7+为有序）、可修改、键值对形式
# - 集合(set)：无序、可修改、不允许重复元素


import random

# ==============================================
# 列表(list)操作示例
# 列表是最常用的数据容器之一，使用方括号[]定义，元素间用逗号分隔
#   列表的常用方法
# - append()：在列表末尾添加一个元素
# - extend()：在列表末尾添加多个元素
# - insert()：在指定位置插入一个元素
# - remove()：删除第一个匹配的元素
# - pop()：删除并返回指定位置的元素（默认最后一个）
# - clear()：清空列表所有元素
# - index()：查找元素首次出现的索引
# - count()：统计元素出现次数
# - sort()：对列表元素进行排序（默认升序）
# - reverse()：将列表元素反转
# ==============================================

# ------------------------------
# 1. 列表的定义与初始化
# ------------------------------

# 定义一个简单的字符串列表
name_list = ['张三', '李四', '王五', '赵六']
print("初始姓名列表:", name_list)

# 定义一个包含字典元素的复杂列表
# 每个元素是一个字典，存储个人信息（姓名、年龄、性别）
person_info_list = [
    {'name': '张三', 'age': 18, 'gender': '男'},
    {'name': '李四', 'age': 19, 'gender': '男'},
    {'name': '王五', 'age': 20, 'gender': '男'},
    {'name': '赵六', 'age': 21, 'gender': '男'},
]
print("初始个人信息列表:", person_info_list)


# ------------------------------
# 2. 列表元素的访问
# ------------------------------

# 访问列表元素：通过索引（从0开始）
print("\n访问姓名列表第1个元素:", name_list[0])
print("访问个人信息列表第1个元素:", person_info_list[0])

# 访问列表中字典元素的具体值：先通过索引取字典，再通过键取 value
print("第1个人的姓名:", person_info_list[0]['name'])
print("第1个人的年龄:", person_info_list[0]['age'])
print("第1个人的性别:", person_info_list[0]['gender'])


# ------------------------------
# 3. 列表元素的查找
# ------------------------------

# 查找元素索引：index()方法返回元素首次出现的索引
# 注意：如果元素不存在会抛出ValueError
print("\n'张三'在姓名列表中的索引:", name_list.index('张三'))

# 查找复杂元素（字典）的索引
# 注意：字典作为元素时，必须完全匹配才能找到
target_person = {'name': '张三', 'age': 18, 'gender': '男'}
print("'张三'信息在列表中的索引:", person_info_list.index(target_person))


# ------------------------------
# 4. 列表元素的添加
# ------------------------------

# 4.1 插入元素：在指定索引位置插入（原位置及之后元素后移）
name_list.insert(1, '王二')  # 在索引1位置插入'王二'
print("\n插入'王二'后的姓名列表:", name_list)

# 插入字典元素
person_info_list.insert(1, {'name': '王二', 'age': 18, 'gender': '男'})
print("插入'王二'信息后的列表:", person_info_list)


# 4.2 追加元素：在列表末尾添加单个元素
name_list.append('王二')  # 在列表末尾追加'王二'
print("\n追加'王二'后的姓名列表:", name_list)

# 追加字典元素
person_info_list.append({'name': '王二', 'age': 18, 'gender': '男'})
print("追加'王二'信息后的列表:", person_info_list)


# 4.3 批量添加元素：extend()方法添加多个元素
name_list.extend(['王三', '王四'])  # 批量添加多个姓名
print("\n批量添加后的姓名列表:", name_list)

# 批量添加字典元素
person_info_list.extend([
    {'name': '王二', 'age': 18, 'gender': '男'},
    {'name': '王三', 'age': 19, 'gender': '男'},
    {'name': '王四', 'age': 20, 'gender': '男'},
])
print("批量添加信息后的列表:", person_info_list)


# ------------------------------
# 5. 列表元素的删除
# ------------------------------

# 5.1 删除指定元素：remove()删除首次出现的指定元素
# 注意：如果元素不存在会抛出ValueError
name_list.remove('王二')  # 删除首次出现的'王二'
print("\n删除'王二'后的姓名列表:", name_list)

# 删除指定的字典元素
person_info_list.remove({'name': '王二', 'age': 18, 'gender': '男'})
print("删除'王二'信息后的列表:", person_info_list)


# 5.2 按索引删除：pop()删除指定索引的元素，并返回被删除的元素
# 注意：如果索引超出范围会抛出IndexError
removed_person = person_info_list.pop(4)  # 删除索引4的元素
print("\n被删除的元素:", removed_person)
print("删除索引4元素后的列表:", person_info_list)


# 5.3 清空列表：clear()删除列表中所有元素
name_list.clear()
print("\n清空后的姓名列表:", name_list)

person_info_list.clear()
print("清空后的个人信息列表:", person_info_list)


# ------------------------------
# 6. 列表的遍历
# ------------------------------

# 6.1 直接遍历元素
print("\n遍历姓名列表（当前为空）:")
for name in name_list:
    print(name)

print("遍历个人信息列表（当前为空）:")
for person_info in person_info_list:
    print(person_info)


# 6.2 同时获取索引和元素：enumerate()方法
print("\n带索引的姓名列表遍历（当前为空）:")
for index, name in enumerate(name_list):
    print(f"索引: {index}, 姓名: {name}")

print("带索引的个人信息列表遍历（当前为空）:")
for index, person_info in enumerate(person_info_list):
    print(f"索引: {index}, 信息: {person_info}")


