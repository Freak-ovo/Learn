# 字典(dict)操作示例

# 字典(dict)是无序、键值对(key-value)的容器，使用大括号{}定义
#      字典的特性：
# 1. 键(key)必须是唯一的，值(value)可以重复
# 2. 键值对之间用冒号:分隔，键值对之间用逗号,分隔
# 3. 字典支持通过键来访问对应的值
# 4. 字典支持添加、删除、修改、查询等操作

# 创建一个空字典
empty_dict = {}
print("空字典:", empty_dict)

# 创建一个有键值对的字典
person = {"name": "张三", "age": 18, "gender": "男"}
print("有键值对的字典:", person)
print("姓名:", person["name"])
print("年龄:", person["age"])
print("性别:", person["gender"])

# 字典嵌套
# 字典的值可以是任意类型，包括列表、元组、字典等
nested_dict = {
    "leo":{
        "name":"leo",
        "age":18,
        "gender":"男"
    },
    "lily":{
        "name":"lily",
        "age":18,
        "gender":"女"
    }
}
print("嵌套字典:", nested_dict)
print("leo的姓名:", nested_dict["leo"]["name"])
print("lily的年龄:", nested_dict["lily"]["age"])
print("lily的性别:", nested_dict["lily"]["gender"])


# 字典的操作

# 添加键值对
nested_dict["lee"] = {
    "name":"lee",
    "age":18,
    "gender":"男"
}
nested_dict["leo"]["age"] = 19 # 修改leo的年龄为19
print("添加键值对后的字典:", nested_dict)   

# 清空字典
person.clear()
print("清空后的person字典:", person)

# 获取所有key
print("所有键值对:", nested_dict.keys())

# 遍历字典
# 遍历字典的key-value对
for key in nested_dict:
    print(key, nested_dict[key])

# 统计字典元素数量
print("字典元素数量:", len(nested_dict))


woker = {
    "yoyo":{
        "部门":"科技部",
        "工资":3000,
        "等级":"1"
    },
    "jojo":{
        "部门":"市场部",
        "工资":5000,
        "等级":"2"
    },
    "coco":{
        "部门":"市场部",
        "工资":7000,
        "等级":"3"
    },
    "momo":{
        "部门":"科技部",
        "工资":4000,
        "等级":"1"
    },
    "oto":{
        "部门":"市场部",
        "工资":6000,
        "等级":"2"
    }
}

for key in woker:
    print("姓名:", key)
    print("等级:", woker[key]["等级"])
    if woker[key]["等级"] == "1":
       woker[key]["等级"] = "2"
       woker[key]["工资"] += 1000

       print("等级1员工升级为等级2")
       print("更新后工资:", woker[key]["工资"])


for key in woker:
    print("姓名:", key)
    print("更新后等级:", woker[key]["等级"])
    print("更新后工资:", woker[key]["工资"])
