# 面向对象编程 示例
# 数据分析，业务逻辑代码
# 实现步骤
# 1. 定义数据模型（Record类）：实现数据模型，包括属性和方法
# 2. 实现数据读取（FileReader类）：实现从文件中读取数据并转换为Record对象列表
# 3. 实现数据分析（Analysis类）：实现对Record对象列表的数据分析，包括计算总金额、按省份分组等
# 4. 实现数据可视化（Visualization类）：实现将分析结果可视化，例如绘制柱状图、折线图等



# 导入数据定义模块
from calendar import c
from winsound import MB_ICONQUESTION
from data_define import Record
from file_define import FileReader, JsonFileReader, TextFileReader

# 读取文本文件数据
text_file_reader = TextFileReader(r"D:\Learn\VSCode\Python\25_10_21\20230724.txt")
json_file_reader = JsonFileReader(r"D:\Learn\VSCode\Python\25_10_21\20230724.json")

# 读取数据
text_records = text_file_reader.read_data()
json_records = json_file_reader.read_data()

# 将2个月份数据合并为1个list来存储
all_data: list[Record] = text_records + json_records

# 构建mysql数据库
from pymysql import Connection

# 连接数据库（不指定具体数据库，仅连接到MySQL服务器）
conn = Connection(
    host="localhost", # 本地数据库主机名，默认值为localhost或127.0.0.1
    port=3306, # 数据库端口号，默认值为3306
    user="root", # 数据库用户名，默认值为root
    password="9527", # 数据库密码，默认值为空字符串
    autocommit=True, # 是否自动提交事务，默认值为False
)

# 创建游标
cursor = conn.cursor()

# 选择数据库
conn.select_db("py_sql")

# 插入数据
for record in all_data:
    sql = f" insert into orders(order_date, order_id, money, province)" \
    f"values ('{record.date}', '{record.order_id}', {record.money}, '{record.province}')"
    cursor.execute(sql)

cursor.close()
conn.close()
