# 1. 正确导入所有模块
from pymysql import Connection
from pymysql.cursors import DictCursor  # 正确导入DictCursor
from datetime import date
import json

# 2. 初始化连接（此时连接未关闭）
conn = Connection(
    host="localhost",
    port=3306,
    user="root",
    password="9527",
    autocommit=True
)
# 定义 JSON 保存路径（可自定义目录，例如 D盘的 Python 文件夹下）
# 注意：路径中的反斜杠用双反斜杠（\\）或加 r 表示原始字符串
json_save_path = r"D:\Learn\VSCode\Python\25_10_21\orders_data.json"

# 3. 核心逻辑：在连接关闭前创建游标、执行操作
try:
    # 选择数据库
    conn.select_db("py_sql")
    
    # 正确创建游标（用导入的DictCursor，且在连接关闭前）
    cursor = conn.cursor(cursor=DictCursor)
    
    # 执行查询
    sql = "SELECT order_date, order_id, money, province FROM orders;"
    cursor.execute(sql)
    results = cursor.fetchall()
    
    # 处理日期类型
    processed_data = []
    for item in results:
        if isinstance(item["order_date"], date):
            item["order_date"] = item["order_date"].strftime("%Y-%m-%d")
        processed_data.append(item)
    
    # 输出JSON
    json_data = json.dumps(processed_data, ensure_ascii=False, indent=4)
    print("JSON结果：")
    print(json_data)
     
    # ----------------------
    # 2. 将 JSON 数据保存到文件
    # ----------------------
    # 打开文件："w" 表示写入模式，encoding="utf-8" 避免中文乱码
    with open(json_save_path, "w", encoding="utf-8") as json_file:
        # 写入 JSON 数据：ensure_ascii=False 保留中文，indent=4 格式化显示
        json.dump(processed_data, json_file, ensure_ascii=False, indent=4)
    
    print(f"JSON 数据已成功保存到：{json_save_path}")

except Exception as e:
    print(f"执行出错：{e}")

finally:
    # 4. 最后关闭资源（先关游标，再关连接）
    if 'cursor' in locals():  # 确保游标已创建再关闭
        cursor.close()
    conn.close()
    print("\n数据库连接已关闭")