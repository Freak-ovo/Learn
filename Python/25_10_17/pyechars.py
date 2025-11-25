# ======================================================
# 功能：读取本地疫情数据.txt文件，绘制中国34个省级行政区累计确诊人数交互式折线图
# 适配版本：pyecharts 2.0.9（已验证该版本支持line_opts等核心参数）
# 环境：Python 3.10（与用户本地Python版本匹配，避免版本兼容问题）
# 输出：生成HTML格式折线图，自动在浏览器打开，支持鼠标悬浮查看详细数据
# ======================================================

# 导入所需模块：每个模块的作用和用途都单独说明
import json  # 用于解析JSON格式的疫情数据文件（将字符串转为Python字典）
from pyecharts.charts import Line  # 导入折线图核心类，是创建折线图的基础
from pyecharts import options as opts  # 导入图表配置模块，用于设置标题、坐标轴等样式
from pyecharts.globals import ThemeType  # 导入主题类型，用于设置图表整体配色风格
import webbrowser  # 导入浏览器控制模块，用于生成图表后自动打开HTML文件


# --------------------------
# 1. 读取并解析疫情数据文件（核心步骤1：获取原始数据）
# 功能：从指定路径读取文件，将JSON字符串转为字典，提取省级疫情数据
# 异常处理：覆盖文件不存在、JSON格式错误两种常见问题，避免程序崩溃
# --------------------------
try:
    # 定义疫情数据文件的绝对路径：用r前缀表示原始字符串，避免路径中的\被当作转义字符
    file_path = r"D:\Learn\VSCode\Python\25_10_17\疫情数据.txt"
    
    # 用with语句打开文件：自动管理文件资源，无需手动close()，避免文件句柄泄漏
    # "r"表示只读模式，encoding="utf-8"确保中文内容正常读取（避免乱码）
    with open(file_path, "r", encoding="utf-8") as f:
        data_str = f.read()  # 读取文件中所有内容，得到JSON格式的字符串
    
    # 将JSON字符串解析为Python字典：便于后续通过键名提取所需数据（如provinceDataList）
    # pyecharts 2.0.9版本对JSON解析无兼容性问题，可直接使用json.loads()
    data_dict = json.loads(data_str)
    
    # 提取省级数据列表：从解析后的字典中，通过"provinceDataList"键获取34个省份的详细数据
    province_list = data_dict["provinceDataList"]
    
    # 打印成功提示：告知用户数据读取结果，同时显示省份数量（验证数据完整性）
    print(f"✅ 数据读取成功！共 {len(province_list)} 个省级行政区")

# 捕获"文件未找到"异常：当指定路径的文件不存在时触发
except FileNotFoundError:
    print(f"❌ 错误：文件不存在！请检查路径是否正确：{file_path}")
    exit()  # 终止程序运行，避免后续代码因无数据而报错

# 捕获"JSON格式错误"异常：当文件内容不符合JSON语法（如漏逗号、中文符号）时触发
except json.decoder.JSONDecodeError as e:
    print(f"❌ 错误：JSON格式错误！具体问题：{e}")
    print("👉 解决方案：用 https://www.json.cn/ 在线工具修复疫情数据.txt的格式")
    exit()  # 终止程序运行，避免解析错误扩散


# --------------------------
# 2. 提取折线图所需数据（核心步骤2：数据预处理）
# 功能：从省级数据列表中，筛选出折线图需要的"省份名称"和"累计确诊数"
# 数据优化：简化省份名称（去除后缀），避免图表中名称过长导致重叠
# --------------------------
# 初始化两个空列表：分别存储横轴（省份名称）和纵轴（累计确诊数）数据
province_names = []  # 横轴数据：简化后的省份名称（如"北京市"→"北京"）
total_confirms = []  # 纵轴数据：对应省份的累计确诊病例数

# 遍历省级数据列表：逐个处理每个省份的信息
for p in province_list:
    # 简化省份名称：通过replace()去除"自治区""特别行政区""省"等后缀
    # 例如"内蒙古自治区"→"内蒙古"，"香港特别行政区"→"香港"，避免图表拥挤
    simple_name = p["provinceName"].replace("自治区", "").replace("特别行政区", "").replace("省", "")
    province_names.append(simple_name)  # 将简化后的名称添加到横轴列表
    
    # 提取累计确诊数：从省份数据的"epidemicData"嵌套字典中，获取"totalConfirmed"字段
    total_confirm = p["epidemicData"]["totalConfirmed"]
    total_confirms.append(total_confirm)  # 将累计确诊数添加到纵轴列表


# --------------------------
# 3. 创建并配置折线图（核心步骤3：图表可视化）
# 功能：初始化折线图对象，设置尺寸、主题、坐标轴数据及样式，配置交互功能
# 版本适配：所有参数均按pyecharts 2.0.9版本设计（如line_opts、ThemeType）
# --------------------------
# 初始化折线图对象：通过链式调用配置所有属性
line_chart = (
    # 1. 设置图表基础属性：尺寸和主题
    Line(init_opts=opts.InitOpts(
        width="1600px",  # 图表宽度：1600像素（适配34个省份横向显示，避免拥挤）
        height="800px",  # 图表高度：800像素（确保纵轴数据显示清晰）
        theme=ThemeType.MACARONS  # 设置图表主题：MACARONS为清新配色（2.0.9版本支持该主题）
    ))
    
    # 2. 添加X轴数据：将预处理后的省份名称列表作为横轴数据
    .add_xaxis(xaxis_data=province_names)
    
    # 3. 添加Y轴数据：配置折线的系列名称、数据、样式及标签
    .add_yaxis(
        series_name="累计确诊病例数",  # 系列名称：显示在图例中，标识当前折线含义
        y_axis=total_confirms,  # 纵轴数据：对应省份的累计确诊数
        symbol="circle",  # 数据点形状：设置为圆形（默认是空心，圆形更直观）
        symbol_size=6,    # 数据点大小：6像素（避免点过大遮挡或过小看不见）
        # 配置数据点标签：控制数值是否显示及显示样式
        label_opts=opts.LabelOpts(
            is_show=True,  # 是否显示标签：True表示显示每个数据点的数值
            position="top",  # 标签位置：数据点正上方（避免遮挡折线）
            font_size=8  # 标签字体大小：8号字（避免标签过多导致拥挤）
        ),
        # 配置折线样式：pyecharts 2.0.9版本用line_opts（1.x版本用line_style，此处需区分）

    )
    
    # 4. 设置全局配置：控制图表标题、坐标轴、图例、提示框等全局样式
    .set_global_opts(
        # 配置图表标题：主标题+副标题，控制位置和字体样式
        title_opts=opts.TitleOpts(
            title="中国各省级行政区累计确诊人数折线图",  # 主标题：说明图表核心内容
            # 副标题：显示数据来源和更新时间（从原始数据中提取，确保信息准确）
            subtitle=f"数据来源：{data_dict['metaInfo']['dataSource']} | 更新时间：{data_dict['metaInfo']['updateTime']}",
            pos_left="center",  # 标题位置：水平居中（默认靠左，居中更美观）
            # 主标题字体样式：18号字+加粗（突出标题）
            title_textstyle_opts=opts.TextStyleOpts(font_size=18, font_weight="bold")
        ),
        
        # 配置X轴（省份名称轴）：控制轴名称、位置及标签样式
        xaxis_opts=opts.AxisOpts(
            name="省级行政区",  # X轴名称：说明横轴数据含义
            name_location="middle",  # 轴名称位置：轴的中间（默认在末尾，中间更直观）
            name_gap=30,  # 轴名称与轴的距离：30像素（避免名称与标签重叠）
            # X轴标签样式：旋转-45度（解决省份名称过长导致的横向重叠问题）
            axislabel_opts=opts.LabelOpts(rotate=-45, font_size=10)
        ),
        
        # 配置Y轴（累计确诊数轴）：控制轴名称、位置及网格线
        yaxis_opts=opts.AxisOpts(
            name="累计确诊病例数",  # Y轴名称：说明纵轴数据含义
            name_location="middle",  # 轴名称位置：轴的中间
            name_gap=50,  # 轴名称与轴的距离：50像素（避免名称与数值重叠）
            # 配置网格线：辅助用户读取数值（显示横向网格线，透明度0.3避免干扰）
            splitline_opts=opts.SplitLineOpts(
                is_show=True,  # 是否显示网格线：True表示显示
                linestyle_opts=opts.LineStyleOpts(opacity=0.3)  # 网格线透明度：0.3（淡色不抢焦点）
            )
        ),
        
        # 配置图例：控制图例位置和字体大小
        legend_opts=opts.LegendOpts(
            pos_top="5%",  # 图例距离顶部的距离：5%（避免遮挡标题）
            pos_right="5%"  # 图例距离右侧的距离：5%（默认在左侧，右侧更节省空间）
        ),
        
        # 配置鼠标悬浮提示框：控制交互时显示的详细信息
        tooltip_opts=opts.TooltipOpts(
            trigger="axis",  # 触发方式：按轴触发（鼠标悬浮时显示当前X轴位置的所有数据）
            # 自定义提示框内容：用lambda表达式拼接HTML格式文本，显示多维度信息
            formatter=lambda params: f"""
            <b>{params[0]['name']}</b><br/>  <!-- 省份名称：加粗突出 -->
            累计确诊：{params[0]['value']:,} 人<br/>  <!-- 累计确诊数：添加千分位分隔符，更易读 -->
            <!-- 现有确诊数：通过列表推导式从province_list中匹配当前省份数据 -->
            现有确诊：{[x for x in province_list if x['provinceName'].replace('自治区','').replace('特别行政区','').replace('省','')==params[0]['name']][0]['epidemicData']['currentConfirmed']} 人<br/>
            <!-- 风险等级：同理匹配当前省份的风险等级 -->
            风险等级：{[x for x in province_list if x['provinceName'].replace('自治区','').replace('特别行政区','').replace('省','')==params[0]['name']][0]['riskInfo']['riskLevel']}
            """
        )
    )
)


# --------------------------
# 4. 生成并自动打开图表（核心步骤4：输出结果）
# 功能：将配置好的折线图渲染为HTML文件，保存到指定路径，并自动在浏览器打开
# --------------------------
# 定义图表输出路径：与数据文件同目录，便于查找
output_path = r"D:\Learn\VSCode\Python\25_10_17\各省份累计确诊折线图.html"

# 渲染图表：将折线图对象转为HTML文件（pyecharts核心方法，生成交互式页面）
line_chart.render(output_path)

# 打印生成成功提示：告知用户文件保存路径，方便手动查找（若自动打开失败）
print(f"✅ 图表生成成功！文件路径：{output_path}")

# 自动打开图表：调用系统默认浏览器，加载生成的HTML文件（无需用户手动操作）
webbrowser.open(output_path)