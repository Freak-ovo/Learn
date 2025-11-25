# ==========================================================
# 面向对象编程示例：学生类与手机类的设计
# 涵盖类定义、属性方法、封装、继承等核心概念
# ==========================================================


class Student:
    """学生类：用于表示学生的基本信息和行为"""
    
    def __init__(self, name, age, university, grade):
        """
        初始化学生对象
        
        参数：
            name (str): 学生姓名
            age (int): 学生年龄
            university (str): 所在大学
            grade (str): 年级（如"本科"、"研究生"）
        """
        # 实例属性初始化
        self.name = name          # 学生姓名
        self.age = age            # 学生年龄
        self.university = university  # 所在大学
        self.grade = grade        # 年级
    
    def __str__(self):
        """返回学生对象的字符串表示（用于print输出）"""
        return f"姓名：{self.name}，年龄：{self.age}，大学：{self.university}，年级：{self.grade}"

    # ==========================================================
    # 比较方法：基于年龄定义学生对象的比较规则
    # ==========================================================
    def __lt__(self, other):
        """小于比较：self.age < other.age"""
        return self.age < other.age
    
    def __le__(self, other):
        """小于等于比较：self.age <= other.age"""
        return self.age <= other.age
    
    def __gt__(self, other):
        """大于比较：self.age > other.age"""
        return self.age > other.age
    
    def __ge__(self, other):
        """大于等于比较：self.age >= other.age"""
        return self.age >= other.age

    # ==========================================================
    # 普通方法：学生的行为定义
    # ==========================================================
    def say_hi(self):
        """学生打招呼的方法"""
        print(f"你好，我是{self.name}")
    
    def print_school_info(self, grade_year):
        """
        输出学生的学校信息
        
        参数：
            grade_year (str): 入学年份（如"25"表示2025级）
        """
        print(f"我是{self.university}的{grade_year}级{self.grade}")
    
    def beep(self):
        """播放提示音（仅Windows系统有效）"""
        try:
            import winsound
            winsound.Beep(1000, 500)  # 频率1000Hz，持续500毫秒
        except ImportError:
            print("提示：非Windows系统不支持提示音功能")


# ==========================================================
# 手机类：基础设备类（演示封装特性）
# ==========================================================
class Phone:
    """手机基类：定义手机的基础功能"""
    
    def __init__(self):
        # 私有属性：仅能在类内部访问
        self.__is_5g_enabled = False  # 是否开启5G（默认关闭）

    # 私有方法：仅能在类内部调用
    def __check_5g(self):
        """检查5G网络状态"""
        if self.__is_5g_enabled:
            print("5G已开启")
        else:
            print("5G未开启, 使用4G网络")

    # 公开方法：提供外部访问接口
    def call_by_5g(self):
        """通过5G网络拨打电话"""
        self.__check_5g()  # 内部调用私有方法
        print("正在通话中...")

    # 新增：提供5G开关控制（封装的合理开放）
    def set_5g_status(self, status):
        """
        设置5G开关状态
        
        参数：
            status (bool): True开启，False关闭
        """
        self.__is_5g_enabled = status


# ==========================================================
# iPhone类：继承自Phone类（演示继承特性）
# ==========================================================
class IPhone(Phone):
    """iPhone类：继承手机基类，增加苹果设备特有功能"""
    
    # 类属性：所有iPhone实例共享的属性
    producer = "Apple"  # 生产厂商
    
    def __init__(self, imei):
        """
        初始化iPhone对象
        
        参数：
            imei (str): 设备唯一标识符
        """
        super().__init__()  # 调用父类构造方法
        self.imei = imei    # 设备唯一标识符
        self.face_id = None # 面部识别ID（初始未设置）
    
    def unlock(self):
        """通过面部识别解锁设备"""
        if self.face_id is not None:
            print("面部识别成功，解锁iPhone")
            self.set_5g_status(True)  # 解锁后自动开启5G
        else:
            print("面部识别ID未设置，无法解锁")


# ==========================================================
# 程序员专用手机类：继承自Phone类（演示功能扩展）
# ==========================================================
class ProgrammerPhone(Phone):
    """程序员专用手机：增加开发者常用功能"""
    
    def send_message(self):
        """发送短信（依赖网络检查）"""
        self._Phone__check_5g()  # 调用父类私有方法（特殊语法）
        print("正在发送短信...")
        print("短信发送成功")
    
    def nfc_read(self):
        """读取NFC标签"""
        self._Phone__check_5g()
        print("正在读取NFC标签...")
        print("NFC标签读取成功")
    
    def read_bank_card(self):
        """读取银行卡信息"""
        self._Phone__check_5g()
        print("正在读取银行卡...")
        print("银行卡读取成功")


class MyPhone(IPhone, ProgrammerPhone):  # 调整继承顺序：子类在前，父类在后
    """自定义手机类：组合IPhone和程序员手机的功能（多继承示例）"""
    
    def __init__(self, imei, face_id):
        # 1. 初始化IPhone父类（会间接初始化Phone基类）
        super(IPhone, self).__init__()  # 先初始化ProgrammerPhone的父类（Phone）
        super().__init__(imei)          # 再初始化IPhone
        
        # 2. 初始化自身属性
        self.face_id = face_id  # 直接设置面部ID，无需后续单独赋值
        print("MyPhone初始化完成：支持iPhone功能+程序员专用功能")

    # 新增：组合功能示例
    def work_and_call(self):
        """工作（发短信）+通话的组合功能"""
        self.unlock()               # 继承自IPhone的解锁功能
        self.send_message()         # 继承自ProgrammerPhone的发短信功能
        self.call_by_5g()           # 继承自Phone的5G通话功能

    # 复写父类方法示例
    def unlock(self):
        """复写IPhone的解锁方法，添加自定义逻辑"""
        if self.face_id is not None:
            print(f"使用面部ID {self.face_id} 解锁iPhone")
            self.set_5g_status(True)  # 解锁后自动开启5G
        else:
            print("面部识别ID未设置，无法解锁")


# ==========================================================
# 测试代码：验证各类功能（添加序号标注）
# ==========================================================
if __name__ == "__main__":
    # 1. 学生类测试
    print("="*50)
    print("【1】学生类测试模块")
    print("="*50)
    # 1.1 创建学生对象并访问属性
    student1 = Student("leo", 25, "DHU", "研究生")
    print(f"1.1 学生姓名：{student1.name}")
    print(f"1.2 学生年龄：{student1.age}")
    # 1.2 调用学生类普通方法
    print("1.3 调用打招呼方法：", end="")
    student1.say_hi()
    print("1.4 调用学校信息打印方法：", end="")
    student1.print_school_info("25")
    # 1.3 调用__str__方法
    print(f"1.5 学生对象完整信息：{student1}")
    
    # 1.4 学生对象比较
    stu2 = Student("lee", 26, "DHU", "研究生")
    print(f"1.6 stu2年龄大于student1：{stu2 > student1}")
    print(f"1.7 stu2年龄小于student1：{stu2 < student1}")

    # 2. 手机基类测试
    print("\n" + "="*50)
    print("【2】手机基类测试模块")
    print("="*50)
    # 2.1 创建手机对象并测试默认5G状态
    basic_phone = Phone()
    print("2.1 测试默认5G通话（未开启5G）：")
    basic_phone.call_by_5g()
    # 2.2 开启5G后再次测试
    print("2.2 开启5G后测试通话：")
    basic_phone.set_5g_status(True)
    basic_phone.call_by_5g()

    # 3. iPhone类测试
    print("\n" + "="*50)
    print("【3】iPhone类测试模块")
    print("="*50)
    # 3.1 创建iPhone对象并访问类属性
    iphone16 = IPhone("123456789012345")
    print(f"3.1 iPhone设备厂商：{iphone16.producer}")
    # 3.2 测试未设置面部ID时的解锁
    print("3.2 首次解锁（未设置面部ID）：")
    iphone16.unlock()
    # 3.3 设置面部ID后测试解锁与5G
    iphone16.face_id = "lee"
    print("3.3 设置面部ID后解锁：")
    iphone16.unlock()
    print("3.4 解锁后测试5G通话：")
    iphone16.call_by_5g()

    # 4. 程序员手机测试
    print("\n" + "="*50)
    print("【4】程序员手机测试模块")
    print("="*50)
    # 4.1 创建程序员手机对象
    dev_phone = ProgrammerPhone()
    # 4.2 测试短信发送功能
    print("4.1 测试短信发送功能：")
    dev_phone.send_message()
    # 4.3 测试NFC读取功能
    print("4.2 测试NFC标签读取功能：")
    dev_phone.nfc_read()
    # 4.4 测试银行卡读取功能
    print("4.3 测试银行卡读取功能：")
    dev_phone.read_bank_card()
    
    # 5. 多继承手机测试
    print("\n" + "="*50)
    print("【5】多继承MyPhone测试模块")
    print("="*50)
    # 5.1 创建多继承手机对象
    my_phone = MyPhone(imei="987654321012345", face_id="Lee")
    # 5.2 测试组合功能（解锁+发短信+通话）
    print("5.1 测试组合功能（work_and_call）：")
    my_phone.work_and_call()
    # 5.3 测试继承的程序员手机功能
    print("5.2 测试继承的NFC读取功能：")
    my_phone.nfc_read()
    # 5.4 测试继承的IPhone类属性
    print(f"5.3 MyPhone设备厂商（继承自IPhone）：{my_phone.producer}")

    # 6. 复写父类方法测试
    print("\n" + "="*50)
    print("【6】复写父类方法测试模块")
    print("="*50)
    # 6.1 测试复写的解锁方法（添加自定义逻辑）
    print("6.1 测试复写的解锁方法（添加自定义逻辑）：")
    my_phone.unlock()

    # 调用父类同名成员的方法
    # 方法一：使用super()调用父类方法
    # super().成员变量 / super().成员方法
    print("\n6.2 测试调用父类的unlock方法（使用super()）：")
    super(MyPhone, my_phone).unlock()

    # 方法二：直接调用父类方法
    # 父类名.成员方法(对象) / 父类名.成员变量 = 新值
    print("\n6.3 测试调用父类的unlock方法（直接调用）：")
    IPhone.unlock(my_phone)
    
