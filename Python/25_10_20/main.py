# 面向对象编程 示例
# 数据分析，业务逻辑代码
# 实现步骤
# 1. 定义数据模型（Record类）：实现数据模型，包括属性和方法
# 2. 实现数据读取（FileReader类）：实现从文件中读取数据并转换为Record对象列表
# 3. 实现数据分析（Analysis类）：实现对Record对象列表的数据分析，包括计算总金额、按省份分组等
# 4. 实现数据可视化（Visualization类）：实现将分析结果可视化，例如绘制柱状图、折线图等



# 导入数据定义模块
from data_define import Record
from file_define import FileReader, JsonFileReader, TextFileReader

# 读取文本文件数据
text_file_reader = TextFileReader(r"D:\Learn\VSCode\Python\25_10_20\20230724.txt")
json_file_reader = JsonFileReader(r"D:\Learn\VSCode\Python\25_10_20\20230724.json")

# 读取数据
text_records = text_file_reader.read_data()
json_records = json_file_reader.read_data()

# 将2个月份数据合并为1个list来存储
all_data: list[Record] = text_records + json_records

# 开始数据分析
# {"2025-07-24": 1000000, "2025-07-25": 2000000, ...}

# 定义一个字典，用于存储每个日期的总金额
date_money_dict = {}

for record in all_data:
    # 从记录中提取日期和金额
    if record.date in date_money_dict.keys():
        date_money_dict[record.date] += int(record.money)
    else:
        date_money_dict[record.date] = int(record.money)

# 可视化分析结果
from pyecharts.charts import Bar
from pyecharts import options as opts

bar = Bar(
    init_opts=opts.InitOpts(theme = "romantic"),
)
bar.add_xaxis(list(date_money_dict.keys()))
bar.add_yaxis("Total Money", list(date_money_dict.values()))
bar.set_global_opts(title_opts=opts.TitleOpts(title="Total Money per Day"))
bar.render("total_money_per_day.html")