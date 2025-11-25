import random
print("方法一：")

# 1. 创建一个员工列表
employees = []
for i in range(1, 21):
    employee = "员工" + str(i)
    employees.append(employee)
    
    # 2. 创建员工绩效
    performance = random.randint(1, 10)
    employees[i-1] += " 绩效：" + str(performance)  # 使用i-1作为索引，因为列表从0开始
    
    # 3. 打印员工信息
    print(employees[i-1])

print("\n" + "="*50 + "\n")

# 4. 发工资
wage = 10000  # 将工资变量放在发放工资部分更合理
for i in range(20):
    # 提取绩效值（注意：这里用中文冒号分割）
    performance = int(employees[i].split("：")[1])
    
    if performance >= 5:
        # 5. 计算工资
        print(employees[i] + " 绩效符合要求，发放工资")
        if wage > 0:
            wage -= 5000  # 每次发放5000
            print(f"{employees[i]} 工资：5000 余额：{wage}\n")
        else:
            print(f"{employees[i]} 工资：余额不足\n")
    else:
        print(f"{employees[i]} 绩效不符合要求，不发放工资\n")


print("方法二：")

# 定义账号余额
money = 10000

# for循环对员工发工资
for i in range(1,21):
    score = random.randint(1, 10)
    
    if score < 5:
        print("员工" + str(i) + " 绩效不符合要求，不发放工资")
        continue
    
    # 判断余额是否充足
    if money >= 1000:
        money -= 1000
        print("员工" + str(i) + " 绩效符合要求，发放工资 工资：" + str(5000) + " 余额：" + str(money))
    else:
        print("员工" + str(i) + " 绩效符合要求，发放工资 余额不足")
        break