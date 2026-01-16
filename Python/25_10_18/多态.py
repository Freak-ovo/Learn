# 多态：不同对象对同一方法有不同的实现
# 使用多态可以让我们编写更通用的代码，能够处理不同类型的对象
# 同样的行为（函数调用），传入不同的对象，得到不同的状态
# 示例1：动物叫声
class Animal:
    def sound(self):
        pass

class Dog(Animal):
    def sound(self):
        return "汪汪汪"

class Cat(Animal):
    def sound(self):
        return "喵喵喵"
    
# 示例2：不同对象对同一方法有不同的实现
def make_animal_sound(animal: Animal):
    print(animal.sound())

# 调用示例
dog = Dog()
cat = Cat()

make_animal_sound(dog)  # 输出：汪汪汪
make_animal_sound(cat)  # 输出：喵喵喵

class Car:
    def sound(self):
        return "哔哔哔"
    
car = Car()
make_animal_sound(car)  # 输出：哔哔哔


# 定义一个父类
class AirConditioner:
    def turn_on(self):
        pass
    
    def turn_off(self):
        pass
    
    def cool_wind(self):
        pass

    def heat_wind(self):
        pass

    def set_temperature(self, temperature: int):
        pass
    def set_humidity(self, humidity: int):
        pass

class MideaAirConditioner(AirConditioner):
    def set_temperature(self, temperature: int):
        print(f"设置温度为：{temperature}度")
    def set_humidity(self, humidity: int):
        print(f"设置湿度为：{humidity}%")   

class GreeAirConditioner(AirConditioner):
    def set_temperature(self, temperature: int):
        print(f"设置温度为：{temperature}度")
    def set_humidity(self, humidity: int):
        print(f"设置湿度为：{humidity}%")   

def make_air_conditioner_work(ac: AirConditioner):
    ac.turn_on()
    ac.set_temperature(25)
    ac.set_humidity(50)
    ac.cool_wind()
    ac.turn_off()

print("Midea Air Conditioner:")
make_air_conditioner_work(MideaAirConditioner())

print("Gree Air Conditioner:")
make_air_conditioner_work(GreeAirConditioner())