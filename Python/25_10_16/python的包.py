# ================================================
# python 的包 相当于 文件夹
# 文件夹中可以包含 python 文件
# 每个 python 文件都是一个模块
# 模块中可以定义函数、类、变量等
# 模块可以被其他模块导入
# 导入模块后，就可以使用模块中定义的函数、类、变量等
# 导入模块时，模块名就是文件名
# 导入模块后，就可以使用模块中定义的函数、类、变量等
# 导入模块的语法：import 模块名
# 导入模块中的函数、类、变量的语法：from 模块名 import 函数名、类名、变量名
#
# ================================================


# ================================================
# python 的创建包
# 要创建一个包，只需要在文件夹中创建一个 __init__.py 文件即可
# __init__.py 文件可以为空，也可以包含一些初始化代码
# 导入包时，会自动执行 __init__.py 文件中的代码
# 可以在 __init__.py 文件中定义 __all__ 变量，指定包中哪些模块可以被导入
# __all__ 变量是一个列表，列表中包含模块名
# 导入包中的模块时，只能导入 __all__ 变量中指定的模块
# 导入包中的模块的语法：from 包名 import 模块名
# ================================================  

# ================================================
# python 的导的安装
# 要安装一个模块，只需要在命令行中输入 pip install 模块名 即可
# 例如：pip install numpy
# 安装完成后，就可以在 python 中导入该模块了
# 换源安装
# 要换源安装一个模块，只需要在命令行中输入 pip install -i 源地址 模块名 即可
# 例如：pip install -i https://pypi.tuna.tsinghua.edu.cn/simple numpy
# ================================================


import My_utils.str_util
import My_utils.file_util

print(My_utils.str_util.str_reverse("开花暖春，海大朝面"))
print(My_utils.str_util.str_substr("我很来劲呢", 0,4))

print(My_utils.file_util.print_file_info(r"D:\Learn\VSCode\Python\25_10_15\file.txt"))
print(My_utils.file_util.append_to_file(r"D:\Learn\VSCode\Python\25_10_16\file.txt", "面朝大海，春暖花开"))