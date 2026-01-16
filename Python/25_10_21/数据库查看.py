from pymysql import Connection

# 连接数据库（不指定具体数据库，仅连接到MySQL服务器）
conn = Connection(
    host="localhost", # 本地数据库主机名，默认值为localhost或127.0.0.1
    port=3306, # 数据库端口号，默认值为3306
    user="root", # 数据库用户名，默认值为root
    password="9527", # 数据库密码，默认值为空字符串
    autocommit=True, # 是否自动提交事务，默认值为False
)
# 
print("连接成功：", conn)

# 查询数据库列表
cursor = conn.cursor()

# 选择数据库
conn.select_db("word")

#
cursor.execute("create table test_pysql (id int primary key auto_increment, name varchar(20))")


# 关闭数据库连接
conn.close()