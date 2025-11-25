# ================================================
# JSON 文件是一种轻量级的数据交换格式 可以将不同语言之间的数据进行交换
# 它基于文本，易于人阅读和编写，同时也易于机器解析和生成
# JSON 文件的扩展名是 .json
# ================================================

# JSON 文件的格式是键值对的集合
# 每个键值对之间用逗号分隔
# 键是字符串，值可以是字符串、数字、数组、对象或布尔值
# 例如：
# {
#     "name": "leo",
#     "age": 18,
#     "gender": "男",
#     "hobbies": ["篮球", "足球", "跑步"],
#     "address": {
#         "province": "北京",
#         "city": "北京",
#         "district": "东城区"
#     }
# }

# JSON 和 python中的字典是非常相似的
# 都可以用来存储键值对
# 都可以用来表示对象
# 都可以用来表示数组
# 都可以用来表示字符串
# 都可以用来表示数字
# 都可以用来表示布尔值

import json # 导入 json 模块

# 准备一个列表
data = [{"name": "leo","age": 18,"gender": "男","hobbies": ["篮球", "足球", "跑步"],"address": {"province": "北京","city": "北京","district": "东城区"}},
    {"name": "lee","age": 18, "gender": "男","hobbies": ["篮球", "足球", "跑步"],"address": {"province": "北京","city": "北京","district": "东城区"}}]

# 把列表转换为 JSON 字符串
json_str = json.dumps(data, ensure_ascii=False, indent=4)
print(json_str)

# 把 JSON 字符串转换为列表
l = json.loads(json_str)
print(l)