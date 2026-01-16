# 模块
"""
    模块是指一个包含 Python 代码的文件，用于组织和重用代码。
    模块可以包含函数、类、变量等。
    模块可以被其他 Python 程序导入和使用。
"""

# 模块导入
"""
    模块导入是指在 Python 程序中使用 import 语句导入其他模块的代码。
    导入模块后，程序可以使用模块中定义的函数、类、变量等。
    Python 提供了许多内置模块，也可以创建自定义模块。
    import 模块名
    可以使用 as 关键字为导入的模块指定别名。
    import 模块名 as 别名
    from 模块名 import 成员名
    可以使用 from ... import 语句从模块中导入特定的成员。
"""

# 导入整个模块
import math

# 调用模块中的函数
result = math.sqrt(9)
print(result)


import my_module as mm
print(mm.PI)
print(mm.Name)
