#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*************
 * string 字符串
 * C++中提供了string类 用来表示字符串
 * string 类是一个模板类
 * string 类中重载了很多运算符
 * 
 * string 和 char* 的区别
 * 1. string 是一个类 char* 是一个指针
 * 2. string 类中重载了很多运算符  char* 没有重载运算符
 * 3. string 类中提供了很多方法  char* 没有提供方法
 * 
 * string 构造函数
 * string() //默认构造函数
 * string(const char* s) //使用字符串s初始化
 * string(const string &str) //使用字符串str初始化
 * string(size_t n, char c) //使用n个字符c初始化
 */

void Test()
{
    //1.默认构造函数
    string str1;
    /* cin >> str1; */
    cout << "str1 = " << str1 << endl;

    //2.使用字符串初始化
    const char* s = "hello world";
    string str2(s);
    cout << "str2 = " << str2 << endl;

    //3.使用字符串拷贝初始化
    string str3(str2);
    cout << "str3 = " << str3 << endl;

    //4.使用n个字符c初始化
    string str4(10, 'a');
    cout << "str4 = " << str4 << endl;
    }
/****************
 * string 赋值
 * string*operator =  (const char* s) //char*类型字符串赋值
 * string*operator =  (const string &str) //string类型字符串赋值
 * string*operator =  (char c) //字符赋值
 * string*operator =  (int n) //整数赋值
 * string*operator =  (float f) //浮点数赋值
 * string*operator =  (double d) //双精度浮点数赋值
 * string* assign(const char* s) //char*类型字符串赋值
 * string* assign(const string &str) //string类型字符串赋值
 * string* assign(size_t n, char c) //使用n个字符c赋值
 * string* assign(const char* s, int n) //使用字符串s的前n个字符赋值
 */


void Test_String()
{
    string str1;
    str1 = "hello world"; //char*类型字符串赋值
    cout << "str1函数赋值 = " << str1 << endl;

    string str2;
    str2 = str1; //string类型字符串赋值
    cout << "str2函数赋值 = " << str2 << endl;

    string str3;
    str3 = 'a'; //字符赋值
    cout << "str3函数赋值 = " << str3 << endl;

    string str4;
    str4.assign("hello Cpp"); //char*类型字符串赋值
    cout << "str4函数赋值 = " << str4 << endl;

    string str5;
    str5.assign(10,'B'); //string类型字符串赋值
    cout << "str5函数赋值 = " << str5 << endl;

}

/****************
 * string 拼接
 * string &operator += (const char* s) //char*类型字符串拼接
 * string &operator += (const string &str) //string类型字符串拼接
 * string &append(const char* s) //char*类型字符串拼接
 * string &append(const string &str) //string类型字符串拼接
 */

void Test_String_Append()
{
    string str1_append = "我";
    str1_append += "爱"; //char*类型字符串拼接
    str1_append += "C++"; //char*类型字符串拼接 
    cout << "str1_append = " << str1_append << endl;  
    
    str1_append += '!'; //字符拼接
    cout << "str1_append = " << str1_append << endl;

    string str2_append = "I";
    str2_append.append(" love"); //char*类型字符串拼接
    str1_append += str2_append; //string类型字符串拼接
    cout << "str1_append = " << str1_append << endl;

    string str3_append = " C++";
    str2_append.append(str3_append); //string类型字符串拼接
    cout << "str2_append = " << str2_append << endl;

    str3_append.append("!!!!!", 4); //char*类型字符串拼接
    cout << "str3_append = " << str3_append << endl;

    str3_append.append(str2_append, 2, 4); //string截取拼接 从第二个位置开始 截取4个字符
    cout << "str3_append = " << str3_append << endl;

}   
/*****************
 * string 查找和替换
 * int find(const char* s, int pos = 0) //查找字符串s 默认从pos位置开始查找 找到返回第一个字符的位置 否则返回-1
 * int find(const string &str, int pos = 0) //查找字符串str
 * int rfind(const char* s, int pos = npos) //从后往前查找字符串s 默认从pos位置开始查找 找到返回第一个字符的位置 否则返回-1
 * int rfind(const string &str, int pos = npos) //从后往前查找字符串str 默认从pos位置开始查找 找到返回第一个字符的位置 否则返回-1
 * string &replace(int pos, int n, const char* s) //替换从pos开始的n个字符为字符串s
 * string &replace(int pos, int n, const string &str) //替换从pos开始的n个字符为字符串str
 * 
 * find 和 rfind 区别
 * find 是从前往后查找  rfind 是从后往前查找
 * replace 是替换指定位置的字符
 */
void Test_String_Find()
{
    string str1_find = "hello world";
    int pos = str1_find.find("world"); //查找字符串world
    if (pos == -1)
    {
        cout << "未找到" << endl;
    }
    else
    {
        cout << "world的位置为：" << pos << endl;
    }
}

void Test_String_Replace()
{
    string str1_replace = "hello world";
    cout << "替换前str1_replace = " << str1_replace << endl;
    str1_replace.replace(6, 5, "C++"); //替换从6位置开始的5个字符为字符串C++
    cout << "替换后str1_replace = " << str1_replace << endl;
}

/**********
 * string 字符串比较
 * 字符之间的比较方式 是 ASCII 码值的比较
 * 返回值 = 0 表示相等 =
 * 返回值 = 1 表示大于 >
 * 返回值 = -1 表示小于 <
 * 比较函数 compare
 * int compare(const string &str) //比较当前字符串与str
 * int compare(int pos, int n, const string &str) //比较当前字符串从pos位置开始的n个字符与str
 * int compare(int pos, int n, const string &str, int pos2, int n2) //比较当前字符串从pos位置开始的n个字符与str从pos2位置开始的n2个字符
 * 
 */
void Test_String_Compare()
{
    string str1_compare = "hello";
    string str2_compare = "world";
    int ret = str1_compare.compare(str2_compare);
    if (ret == 0)
    {
        cout << "str1_compare 等于 str2_compare" << endl;
    }
    else if (ret > 0)
    {
        cout << "str1_compare 大于 str2_compare" << endl;
    }
    else
    {
        cout << "str1_compare 小于 str2_compare" << endl;
    }
}

/**********
 * string 字符存取
 * char &operator [] (int pos) //返回pos位置的字符
 * char &at(int pos) //返回pos位置的字符
 */

void Test_String_Char_Access()
{
    string str1_char_access = "hello world";
    for (int i = 0; i < str1_char_access.size(); i++)//size()返回字符串的长度
    {
        cout << str1_char_access[i] << " "; //使用[]访问字符
    }
    cout << endl;

    for (int i = 0; i < str1_char_access.size(); i++)
    {
        cout << str1_char_access.at(i) << " "; //使用at()访问字符
    }
    cout << endl;

    //修改单个字符
    str1_char_access[0] = 'H'; //修改第一个字符为H
    cout << "1.str1_char_access = " << str1_char_access << endl;

    str1_char_access.at(6) = 'W'; //修改第二个字符为W
    cout << "2.str1_char_access = " << str1_char_access << endl;
    //修改多个字符
    str1_char_access.replace(6, 5, "C++"); //替换从6位置开始的5个字符为字符串C++
    cout << "3.str1_char_access = " << str1_char_access << endl;

    str1_char_access.at(6) = 'C'; //替换第6位字符为C
    str1_char_access.at(7) = 'p'; //替换第7位字符为p
    str1_char_access.at(8) = 'p'; //替换第8位字符为p

    cout << "4.str1_char_access = " << str1_char_access << endl;
}

/***********************
 * string 插入和删除
 * string &insert(int pos, const char* s) //在pos位置插入字符串s
 * string &insert(int pos, const string &str) //在pos位置插入字符串 str
 * string &insert(int pos, int n, char c) //在pos位置插入   n个字符c
 * string &erase(int pos, int n = npos) //删除从pos位置开始的n个字符 默认删除到字符串结束
 * string &clear() //清空字符串
 * string &pop_back() //删除字符串最后一个字符
 * string &push_back(char c) //在字符串末尾添加一个字符c
 * string &append(const char* s) //在字符串末尾添加字符串s
 * 
 * 
 ************************/

void Test_String_Insert()   
{
    string str1_insert = "hello world";
    cout << "插入前str1_insert = " << str1_insert << endl;
    str1_insert.insert(5, ","); //在5位置插入字符串,
    cout << "插入后str1_insert = " << str1_insert << endl;

    str1_insert.insert(6, " C++"); //在6位置插入字符串 C++
    cout << "插入后str1_insert = " << str1_insert << endl;
    str1_insert.erase(10, 6); //删除从10位置开始的6个字符    
    cout << "删除后str1_insert = " << str1_insert << endl;
    str1_insert.insert(0, 3, '*'); //在0位置插入3个字符*
    cout << "插入后str1_insert = " << str1_insert << endl;

}
void Test_String_Erase()
{
    string str1_erase = "hello world";
    cout << "1.删除前str1_erase = " << str1_erase << endl;
    str1_erase.erase(5, 1); //删除从5位置开始的1个字符
    cout << "2.删除后str1_erase = " << str1_erase << endl;
}

/**************************
 *  对vector 中数据的存取操作
 * at(int idx) //返回索引index位置的元素
 * operator [] (int idx) //返回索引index位置的元素
 * front() //返回第一个元素
 * back() //返回最后一个元素
 * data() //返回指向第一个元素的指针
 * 
 */
void Test_Vector_Access()
{
    vector<int> v;
    for (int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }

    //使用at()访问元素
    for (int i = 0; i < v.size(); i++)
    {
        cout << v.at(i) << " ";
    }
    cout << endl;

    //使用[]访问元素
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    cout << endl;

    //访问第一个元素
    cout << "第一个元素为：" << v.front() << endl;

    //访问最后一个元素
    cout << "最后一个元素为：" << v.back() << endl;

    //访问第一个元素的指针
    int* p = v.data();
    for (int i = 0; i < v.size(); i++)
    {
        cout << *(p + i) << " ";
    }
    cout << endl;   

}

/***********
 * vector 容器的互换
 * swap(vec) //将vec与本身的元素互换
 */

void Test_Vector_Swap()
{
    vector<int> v1;
    for (int i = 10; i < 20; i++)
    {
        v1.push_back(i);
    }
    

    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;

    vector<int> v2;
    for (int i = 20; i < 30; i++)
    {
        v2.push_back(i);
    }
    

    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << " ";
    }
    cout << endl;
    v1.swap(v2); //将v1与v2的元素互换
    cout << "v1.swap(v2)后：" << endl;
    for (int i = 0; i < v1.size(); i++)
    {
        cout << v1[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < v2.size(); i++)
    {
        cout << v2[i] << " ";
    }
    cout << endl;

    /* Swap 函数的作用 
        1.回收内存 */
    vector<int> v3;
    for (int i = 0; i < 10000; i++)
    {
        v3.push_back(i);
    }
    cout << "v3的容量为：" << v3.capacity() << endl; //capacity()返回容器的容量
    cout << "v3的大小为：" << v3.size() << endl; //size()返回容器的大小
    v3.resize(100); //resize()改变容器的大小
    cout << "v3的容量为：" << v3.capacity() << endl; //
    cout << "v3的大小为：" << v3.size() << endl; //size()返回容器的大小
    vector<int>(v3).swap(v3); //将v3与一个临时的空容器互换
    cout << "v3的容量为：" << v3.capacity() << endl; //         
    cout << "v3的大小为：" << v3.size() << endl; //size()返回容器的大小
}


/*************
 * vector 预留空间
 * vector::reserve(int len) //预留len个元素的空间   
 * reserve()函数的作用
 * 1.减少vector在动态扩展容量时的扩展次数
 * 2.可以提前预留好空间，避免多次动态扩展导致的性能问题
 * 3.预留空间并不会改变vector的大小
 * 4.预留空间会改变vector的容量
 * 5.预留空间的大小不能小于当前的大小
 *************/

void Test_Vector_Reserve()
{
    vector<int> v4;
    int num = 0;
    int capacity = v4.capacity(); //capacity()返回容器的容量
    cout << "预留空间前v4的容量为：" << capacity << endl;
    for (int i = 0; i < 100; i++)
    {
        v4.push_back(i);
        if (capacity != v4.capacity()) //如果容量发生变化
        {
            capacity = v4.capacity();
            cout << "扩展了" << ++num << "次容量，当前容量为：" << capacity << endl;
        }
    }

    vector<int> v5;
    v5.reserve(100); //预留100个元素的空间
    capacity = v5.capacity();
    cout << "预留空间后v5的容量为：" << capacity << endl;
    num = 0;
    for (int i = 0; i < 100; i++)
    {
        v5.push_back(i);
        if (capacity != v5.capacity()) //如果容量发生变化
        {
            capacity = v5.capacity();
            cout << "扩展了" << ++num << "次容量，当前容量为：" << capacity << endl;
        }
    }
}
int main()
{
    // 这组测试函数调用展示了C++中string和vector容器的各种操作
    Test();                           // 测试string的构造函数
    Test_String();                    // 测试string的赋值操作
    Test_String_Append();             // 测试string的拼接操作
    Test_Vector_Reserve();            // 测试vector的预留空间操作
    Test_String_Find();               // 测试string的查找操作
    Test_String_Replace();            // 测试string的替换操作
    Test_String_Compare();            // 测试string的比较操作
    Test_String_Char_Access();        // 测试string的字符存取操作
    Test_String_Insert();             // 测试string的插入操作
    Test_String_Erase();              // 测试string的删除操作
    Test_Vector_Access();             // 测试vector的元素访问操作
    Test_Vector_Swap();               // 测试vector的互换操作
    Test_Vector_Reserve();            // 测试vector的预留空间操作
    return 0;
}