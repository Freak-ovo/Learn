# 函数

# 关键词参数：
# 关键词参数是指在调用函数时，使用参数名=参数值的方式传递参数，而不是使用位置参数的方式。
# 关键词参数可以不按照函数定义时的参数顺序传递，因为函数会根据参数名进行匹配。
def print_info(name, age):
    print(f"姓名：{name}，年龄：{age}")

print_info(age=20, name="leo")  # 输出：姓名：张三，年龄：20

def user_info(name, age, sex ):
    print(f"姓名：{name}，年龄：{age}，性别：{sex}")

user_info(age=21, name="le", sex="男")  # 输出：姓名：张三，年龄：20，性别：男
user_info(age=25, name="lee", sex="男")  # 输出：姓名：lee，年龄：20，性别：男

 
# 不定长参数
# 不定长参数是指在定义函数时，使用*args或**kwargs的方式来接收不定数量的参数。
# *args用于接收任意数量的位置参数，将它们作为元组传递给函数。
# **kwargs用于接收任意数量的关键词参数，将它们作为字典传递给函数。

# 位置不定长参数：
# 位置不定长参数是指在调用函数时，传递的参数数量可以是任意数量的位置参数。
# 这些参数会被打包成一个元组，传递给函数。
def print_info(name, age, *args):
    print(f"姓名：{name}，年龄：{age}")
    for arg in args:
        print(arg)

print_info("lee", 25, "男", "北京")  # 输出：姓名：lee，年龄：25，男，北京


# 关键词不定长参数：
# 关键词不定长参数是指在调用函数时，传递的参数数量可以是任意数量的关键词参数。
# 这些参数会被打包成一个字典，传递给函数。
def user_info(name, age, sex, **kwargs):
    print(f"姓名：{name}，年龄：{age}，性别：{sex}")
    for key, value in kwargs.items():
        print(f"{key}：{value}")

user_info("lee", 25, "男", 手机号="13812345678", 邮箱="DHU@example.com")
# 输出：
# 姓名：lee，年龄：25，性别：男
# 手机号：13812345678
# 邮箱：DHU@example.com 



# ======================================================
# 函数作为参数：
# 函数作为参数是指在调用函数时，传递的参数可以是一个函数。
# 这种方式可以实现函数的动态调用，使代码更加灵活。
# ======================================================


def apply(func, x, y):
    return func(x, y)

def add(a, b):
    return a + b

def mul(a, b):
    return a * b

print(apply(add, 2, 3))  # 输出：5
print(apply(mul, 2, 3))  # 输出：6


# 匿名函数：
# 匿名函数是指没有函数名的函数，通常用于简单的函数场景。
# 匿名函数使用lambda关键字定义，格式为lambda 参数列表: 表达式。
# 匿名函数只能包含一个表达式，不能包含复杂的语句。
# 匿名函数通常用于需要一个简单函数的场景，例如作为参数传递给其他函数。
# ======================================================

lambda x, y: x + y
print((lambda x, y: x + y)(2, 3))  # 输出：5