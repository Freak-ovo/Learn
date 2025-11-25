    def __lt__(self, other):
        """定义学生对象的小于关系，基于年龄比较"""
        return self.age < other.age
    