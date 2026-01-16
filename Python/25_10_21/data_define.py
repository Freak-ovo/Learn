class Record:
    """数据记录模型，包含交易核心字段"""
    def __init__(self, date: str, order_id: str, money: int, province: str):
        self.date = date          # 交易日期（如：2023-07-24）
        self.order_id = order_id  # 订单号（如：ORDER001）
        self.money = money        # 交易金额（整数）
        self.province = province  # 省份（如：广东省）

    def __str__(self):
        return f"Record({self.date}, {self.order_id}, {self.money}, {self.province})"
    
    def __repr__(self):
        return self.__str__()