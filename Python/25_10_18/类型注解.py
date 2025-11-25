# 类型注解
# 变量名: 类型
# 函数名(参数名: 类型, ...) -> 返回值类型:

from numpy import var


var_1: int = 10
var_2: float = 3.14
var_3: str = "hello"
var_4: bool = True

class Student:
    """学生类：用于表示学生的基本信息和行为"""
    def __init__(self, name: str, age: int, university: str, grade: str):
        """
        初始化学生对象
        
        参数：
            name (str): 学生姓名
            age (int): 学生年龄
            university (str): 所在大学
            grade (str): 年级（如"本科"、"研究生"）
        """
        # 实例属性初始化
        self.__name = name          # 学生姓名
        self.__age = age            # 学生年龄
        self.__university = university  # 所在大学
        self.__grade = grade        # 年级  

leo: Student = Student("leo", 20, "DHU", "master")


# 函数注解
def add(a: int, b: int) -> int: # 函数注解 返回值类型
    """
    对两个整数进行加法运算
    
    参数：
        a (int): 第一个整数
        b (int): 第二个整数
        
    返回：
        int: 两个整数的和
    """
    return a + b    

t = add(1, 2)
print(t)

# 1. 基础类型注解：明确指定列表/字典的元素类型
# 作用：让变量类型更清晰，方便IDE提示和代码检查
# list[int]：表示这是一个元素全为int类型的列表
My_list: list[int] = [1, 2, 3]  # 正确：列表元素均为int，符合注解

# dict[str, int]：表示这是一个“键为str类型、值为int类型”的字典
My_dict: dict[str, int] = {"a": 1, "b": 2, "c": 3}  # 正确：键是str、值是int，符合注解


# 2. 导入Union类型：用于标注“变量/元素可以是多个类型中的任意一个”
from typing import Union

# 关键修正：Union[int, str] 表示“元素可以是int或str”，外层用list包裹表示“列表”
# 即：My_union_list 是一个列表，列表中的每个元素既可以是int，也可以是str
My_union_list: list[Union[int, str]] = [1, "a", 2, "b"]  # 正确：元素类型符合Union注解

# 3. Union类型的其他常见用法示例（扩展理解）
# 示例1：变量可以是int或str类型（单个变量的多类型可选）
age_or_name: Union[int, str] = 25  # 合法：25是int类型
age_or_name = "Leo"  # 合法："Leo"是str类型，符合Union注解

# 示例2：字典的值支持多类型（值可以是int、str或bool）
mixed_dict: dict[str, Union[int, str, bool]] = {
    "age": 25,       # int类型，符合
    "name": "Leo",   # str类型，符合
    "is_student": True  # bool类型，符合
}