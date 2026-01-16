from data_define import Record
import json


class FileReader:
    """文件读取器基类，定义抽象方法和统一管理文件路径"""
    def __init__(self, file_path: str):
        self.file_path = file_path  # 所有子类共享的文件路径

    def read_data(self) -> list[Record]:
        """抽象方法：读取数据并返回Record列表（子类必须实现）"""
        raise NotImplementedError("子类必须实现read_data方法")


class TextFileReader(FileReader):
    """文本文件读取器（处理逗号分隔的TXT/CSV）"""
    def read_data(self) -> list[Record]:
        records = []
        with open(self.file_path, "r", encoding="utf-8") as f:
            for line in f:
                line = line.strip()
                if not line:
                    continue  # 跳过空行
                data_list = line.split(",")
                # 严格匹配TXT格式：日期,订单号,金额,省份
                if len(data_list) != 4:
                    raise ValueError(f"无效的文本格式：{line}（需4个字段）")
                record = Record(
                    date=data_list[0],
                    order_id=data_list[1],
                    money=int(data_list[2]),
                    province=data_list[3]
                )
                records.append(record)
        return records


class JsonFileReader(FileReader):
    """JSON文件读取器（处理包含date/order_id/money/province的JSON数组）"""
    def read_data(self) -> list[Record]:
        records = []
        with open(self.file_path, "r", encoding="utf-8") as f:
            data = json.load(f)  # 加载JSON数组
            for item in data:
                # 严格匹配JSON字段名（与TXT字段对应）
                record = Record(
                    date=item["date"],
                    order_id=item["order_id"],
                    money=int(item["money"]),  # JSON中money是字符串，转int
                    province=item["province"]
                )
                records.append(record)
        return records


# 测试代码
if __name__ == "__main__":
    try:
        # 测试文本文件读取（使用之前生成的20230724.txt）
        text_reader = TextFileReader(r"D:\Learn\VSCode\Python\25_10_21\20230724.txt")
        text_records = text_reader.read_data()
        print("文本文件数据（前2条）：")
        for r in text_records[:2]:
            print(f"{r.date} | {r.order_id} | {r.money} | {r.province}")

        # 测试JSON文件读取（使用之前生成的25_10_20\20230724.json）
        json_reader = JsonFileReader(r"D:\Learn\VSCode\Python\25_10_21\20230724.json")
        json_records = json_reader.read_data()
        print("\nJSON文件数据（前2条）：")
        for r in json_records[:2]:
            print(f"{r.date} | {r.order_id} | {r.money} | {r.province}")

    except Exception as e:
        print(f"测试失败：{e}")