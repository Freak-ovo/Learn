# 函数
def greet(name):
    print("你好，" + name + "!")



     # 调用函数
greet("张三")


# 函数的参数
def add(a, b):
    result = a + b
    print(result)

    # 调用函数
add(3, 5)

# 函数注释
def multiply(x, y):
    """
    返回两个数的乘积
    :param x: 第一个数
    :param y: 第二个数
    :return: 两个数的乘积
    """

    return x * y

    # 调用函数
result = multiply(4, 6)
print(result)

# 函数嵌套调用
"""
    函数嵌套调用是指在一个函数内部定义另一个函数，并且在外部函数中调用内部函数。
    函数的调用遵循栈的结构，最后被调用的函数最先执行，先被调用的函数后执行。
    LIFO: Last In, First Out
"""
def nested_function():
    def inner_function():
        print("这是内部函数")
    inner_function()
    print("这是外部函数")

nested_function()

# 匿名函数
"""
    匿名函数是指没有函数名的函数，也称为 lambda 函数。
    匿名函数通常用于简单的函数，例如在 map()、filter()、reduce() 等函数中使用。
"""
# 定义一个匿名函数，用于计算两个数的和
lambda x, y: x + y

# 调用匿名函数
result = (lambda x, y: x + y)(10, 20)
print(result)

# 高阶函数
"""
    高阶函数是指接受一个或多个函数作为参数，或者返回一个函数作为结果的函数。
    高阶函数可以用于函数的组合、柯理化、装饰器等功能。
"""
def apply_function(func, value):
    return func(value)

# 定义一个函数，用于将一个数平方
def square(x):
    return x ** 2

# 调用高阶函数，将 square 函数作为参数传递
result = apply_function(square, 5)
print(result)

# 递归函数
"""
    递归函数是指在函数内部调用自身的函数。
    递归函数通常用于解决分治问题，例如计算阶乘、斐波那契数列等。
"""
def factorial(n):
    if n == 0:
        return 1
    else:
        return n * factorial(n - 1)

# 调用递归函数，计算 5 的阶乘
result = factorial(5)
print(result)# 输出: 120    


# 练习：定义一个函数，用于更具传入的一批商品信息（商品名、价格、数量）
# ，优惠（优惠卷、积分抵扣）、运费信息计算订单的总金额。

def CalculateTotal(*args, socre, coupon, express):
    """
    CalculateTotal 的 Docstring
    
    :param args: 说明 商品信息（商品名、价格、数量）
    :param socre: 说明 积分抵扣
    :param coupon: 说明 优惠卷抵扣
    :param express: 说明 运费
    """
    # 订单的总金额 = 商品总金额 - 优惠卷 - 积分抵扣 + 运费
    # 商品总金额
    total_price = [goods[1] * goods[2] for goods in args]

    total_cost = sum(total_price)
    # 扣减优惠卷
    if total_cost >= 5000 and coupon <= total_cost: 
        total_cost -= coupon
    # 扣减积分抵扣
    if socre >= 5000 and socre//100 <= total_cost:
        total_cost -= socre//100 
    # 计算总金额
    total_cost += express

    return total_cost

# 调用函数
order_total = CalculateTotal(
    ("商品A", 1000, 3),
    ("商品B", 500, 4),
    ("商品C", 2000, 1),
    socre=6000,
    coupon=800,
    express=50
)
print(order_total)