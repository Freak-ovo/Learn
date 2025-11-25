from pyecharts import options as opts
from pyecharts.charts import Map
from pyecharts.options import TitleOpts, VisualMapOpts
# 创建一个Map实例，用于绘制地图
map = Map()

# 1. 准备数据：地图需要的是一个包含区域名称和对应数值的列表
data = [
    ("北京", 100),
    ("上海", 200),
    ("广州", 300),
    ("深圳", 400),
    ("成都", 500),
    ("杭州", 600),
    ("苏州", 700),
    ("武汉", 800),
    ("长沙", 900),
    ("西安", 1000),
]

# 2. 配置地图：设置地图类型、标题、颜色等
map.set_global_opts(
    # 设置地图的标题
    title_opts=opts.TitleOpts(title="中国地图示例"),
    # 设置视觉映射组件，用于根据数据值显示不同颜色
    visualmap_opts=opts.VisualMapOpts(
        is_show=True,
        max_=1000,
        is_piecewise=True),
)

map.add(
    # 系列名称，用于在图例和 tooltip 中显示
    series_name="测试",
    # 数据对，包含区域名称和对应数值
    data_pair=data,
    # 指定地图类型为中国地图
    maptype="china",
)

# 3. 渲染图表：将图表渲染为HTML文件或在Jupyter Notebook中显示
map.render("中国地图.html")

import webbrowser
output_path = "中国地图.html"
webbrowser.open(output_path)
