# ======================================================
# 调试示例1
# 下面是一个简单的调试示例1，演示了如何使用调试器来调试代码。
# ======================================================

try:
    a = int(input("请输入一个整数："))
    b = int(input("请输入另一个整数："))
    result = a / b
    print(result)
except ValueError:
    print("请输入一个整数")
except ZeroDivisionError:
    print("除数不能为0")

# 捕获所有异常
except Exception as e:
    print("发生了一个异常：", e)

# else 程序运行正常时执行
else:
    print("程序运行正常")
    
# finally 无论是否发生异常，都会执行
finally:
    print("程序结束")


def fun1():
    print("fun1")
    n = 1/0
    print("fun1 end")

def fun2():
    print("fun2")
    fun1()
    print("fun2 end")

def main():
    try:
        fun2()
    except Exception as e:
        print("发生了一个异常：", e)

main()