# 字符串(str)操作示例
# 字符串是由字符组成的有序、不可修改的序列
# 特性：
# 1. 使用单引号('')、双引号("")或三引号(''''''/"""""")定义
# 2. 不可修改，一旦创建就不能改变其中的字符
# 3. 支持索引访问和切片操作
# 4. 可以包含任意字符，包括数字、字母、符号和空格


# ------------------------------
# 1. 字符串的定义与初始化
# ------------------------------

# 基本字符串定义
single_quote_str = 'Hello World'  # 单引号定义
double_quote_str = "Hello Python"  # 双引号定义
print("单引号字符串:", single_quote_str)
print("双引号字符串:", double_quote_str)

# 包含引号的字符串
str_with_quotes = "He said 'Hello'"  # 双引号中包含单引号
str_with_quotes2 = 'She said "Hi"'   # 单引号中包含双引号
print("包含单引号的字符串:", str_with_quotes)
print("包含双引号的字符串:", str_with_quotes2)

# 多行字符串（三引号定义）
multi_line_str = '''第一行文本
第二行文本
第三行文本'''
print("\n多行字符串:")
print(multi_line_str)

# 空字符串
empty_str = ""
print("\n空字符串:", empty_str, "长度:", len(empty_str))


# ------------------------------
# 2. 字符串的访问与切片
# ------------------------------

text = "Python Programming"

# 通过索引访问单个字符（索引从0开始）
print("\n字符串:", text)
print("索引0的字符:", text[0])   # 'P'
print("索引6的字符:", text[6])   # ' '（空格）

# 负索引访问（从末尾开始，-1表示最后一个字符）
print("最后一个字符:", text[-1])  # 'g'
print("倒数第三个字符:", text[-3])  # 'i'

# 切片操作（获取子字符串）
# 语法：str[start:end:step]，包含start，不包含end
print("前6个字符:", text[:6])        # 'Python'
print("从第7个到结尾:", text[7:])     # 'Programming'
print("第7到15个字符:", text[7:15])  # 'Program'
print("每隔2个字符:", text[::2])     # 'Pto rgamn'
print("反转字符串:", text[::-1])     # 'gnimmargorP nohtyP'


# ------------------------------
# 3. 字符串的常用操作
# ------------------------------

# 字符串拼接
str1 = "Hello"
str2 = "World"
combined_str = str1 + " " + str2
print("\n拼接后的字符串:", combined_str)  # 'Hello World'

# 字符串重复
repeat_str = "Hi" * 3
print("重复后的字符串:", repeat_str)  # 'HiHiHi'

# 计算字符串长度
print("字符串长度:", len(text))  # 18

# 检查子字符串是否存在
print("'Pro'是否在文本中:", 'Pro' in text)  # True
print("'Java'是否在文本中:", 'Java' in text)  # False


# ------------------------------
# 4. 字符串的常用方法
# ------------------------------

sample = "  Hello World!  "

# 大小写转换
print("\n原字符串:", sample)
print("全部大写:", sample.upper())       # '  HELLO WORLD!  '
print("全部小写:", sample.lower())       # '  hello world!  '
print("首字母大写:", sample.title())     # '  Hello World!  '
print("大小写反转:", sample.swapcase())  # '  hELLO wORLD!  '

# 去除空白
print("去除两端空白:", sample.strip())    # 'Hello World!'
print("去除左侧空白:", sample.lstrip())   # 'Hello World!  '
print("去除右侧空白:", sample.rstrip())   # '  Hello World!'

# 查找与替换
message = "Hello Python, I love Python!"
print("\n原消息:", message)
print("'Python'首次出现的索引:", message.find("Python"))  # 6
print("替换后的消息:", message.replace("Python", "Java"))  # 'Hello Java, I love Java!'

# 分割与连接
csv_str = "apple,banana,orange"
print("\n分割字符串:", csv_str.split(','))  # ['apple', 'banana', 'orange']

words = ["Hello", "World", "Python"]
print("连接字符串:", '-'.join(words))  # 'Hello-World-Python'

# 检查字符串开头/结尾
url = "https://www.example.com"
print("是否以'https'开头:", url.startswith("https"))  # True
print("是否以'com'结尾:", url.endswith("com"))        # True


# ------------------------------
# 5. 字符串的不可修改性
# ------------------------------

try:
    # 尝试修改字符串中的字符（会报错）
    text[0] = 'p'
except TypeError as e:
    print("\n修改字符串时的错误:", e)  # 输出错误信息


# ------------------------------
# 6. 字符串的遍历
# ------------------------------

print("\n遍历字符串中的每个字符:")
for char in "Python":
    print(char)

# 带索引遍历
print("\n带索引遍历:")
for index, char in enumerate("Python"):
    print(f"索引{index}: {char}")


# ------------------------------
# 7. 格式化字符串
# ------------------------------

name = "Alice"
age = 30

# 使用f-string（Python 3.6+）
print("\n格式化字符串(f-string):")
print(f"姓名: {name}, 年龄: {age}")

# 使用format()方法
print("格式化字符串(format()):")
print("姓名: {0}, 年龄: {1}".format(name, age))
print("姓名: {n}, 年龄: {a}".format(n=name, a=age))

# 旧式格式化（%操作符）
print("旧式格式化:")
print("姓名: %s, 年龄: %d" % (name, age))
