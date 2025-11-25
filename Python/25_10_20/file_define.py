from data_define import Record  # 修改了导入路径，因为Record类在data_define.py中

class FileReader:
    def read_data(self) -> list[Record]:  # 修复了语法错误
        pass

class TextFileReader(FileReader):
    def __init__(self, file_path: str) -> None:
        self.file_path = file_path

    # 复写（实现抽象方法）父类的方法
    def read_data(self) -> list[Record]:
        """
        从文本文件中读取数据并转换为Record对象列表
        
        返回:
            list[Record]: 包含从文件中读取的所有记录的列表
        """
        # 初始化记录列表用于存储读取到的所有记录
        records = []
        
        # 以只读模式打开文件，使用utf-8编码
        with open(self.file_path, "r", encoding="utf-8") as f:
            # 逐行读取文件内容
            for line in f:
                # 去除每行首尾的空白字符（如换行符、空格等）
                line = line.strip()
                
                # 跳过空行
                if line:
                    # 按逗号分割行内容，获取日期、金额和描述
                    date, amount, description = line.split(",")
                    
                    # 创建Record对象，注意将金额转换为整数类型
                    record = Record(date, int(amount), description)
                    
                    # 将创建的记录添加到记录列表中
                    records.append(record)
        
        # 返回包含所有记录的列表
        return records