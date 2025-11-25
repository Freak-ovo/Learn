# ===================================
# 模块
# ===================================

# 模块的导入方式
# 1. 直接导入模块
# import 模块名
# 2. 从模块中导入函数、类、变量、常量
# from 模块名 import 函数名
# from 模块名 import * | 类 | 变量 | 常量 as 别名

# from 模块名 import *  导入全部  调用函数时不需要模块名.
     # 不推荐使用，可能会导致命名冲突
     # from 模块名 import *

# 导入python标准库的模块
import math 
import time


from sklearn import datasets
sklearn_data = datasets.load_iris()
print(sklearn_data)
