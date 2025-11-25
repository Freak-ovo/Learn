
# 计算函数字符长度

str1 = "itheima"
str2 = "itcast"
str3 = "python"
count1 = 0
for i in str1:
    count1 += 1

print(count1)

#  可以使用函数优化过程
def My_len(data):
    count = 0
    for i in data:
        count += 1
    return count

print("str1 长度为：" + str(My_len(str1)))
print("str2 长度为：" + str(My_len(str2)))
print("str3 长度为：" + str(My_len(str3)))
