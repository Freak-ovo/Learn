#include <iostream>
#include <fstream>
using namespace std;
/**************************************************
 *                  文件操作
 * 1、文本文件 文本以ASCII码形式存储在计算机中
 * 2、二进制文件 文件以文本的二进制形式存储在计算机中，用户一般不能直接读懂
 * 
 * ofstream：写操作
 * ifstream：读操作
 * fstream： 读写文件
 * 
 * 1、写文件步骤
 *  1.包含头文件
 *      #include <fstream>
 *  2.创建对象流
 *      ofstream ofs
 *  3.打开文件
 *      ofs.open("文件路径"， 打开方式)
 *  4.写数据
 *      ofs << "写入数据" ;
 *  5.关闭文件
 *      ofs.close();
 * 
 * 文件打开方式
 *  ios::in     为读文件而打开文件
 *  ios::out    为写文件而打开文件
 *  ios::ate    初始位置：文件尾
 *  ios::app    追加方式写文件
 *  ios::trunc  如果文件存在先删除，再创建
 *  ios::binary 二进制方式
 * 
 */

 //文本文件写文件
void TestWrite()
{
    ofstream ofs;
    ofs.open("D:\\Learn\\VSCode\\CPP\\2025_10_01\\Test.txt", ios::out);
    ofs << "Hello World" << endl;
    ofs.close();
}

/************************
 *      读文件
 * 1、读文件步骤
 *  1.包含头文件
 *      #include <fstream>
 *  2.创建对象流
 *      ifstream ifs (input 输出 相对于计算机输出 对我我们是读)
 *  3.打开文件
 *      ifs.open("文件路径"， 打开方式)
 *  4.读数据
 *      四种方式读取
 *  5.关闭文件
 *      ifs.close();
*/
//读文件
void TestRead()
{
    ifstream ifs;
    ifs.open("D:\\Learn\\VSCode\\CPP\\2025_10_01\\Test.txt", ios::in);

    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return;
    }
    //读数据4种方法
/*     //第一种
    char buf[1024] = {0};
    while (ifs >> buf)
    {
        cout << buf << endl;
    } */

    //第二种
    char buf[1024] = {0};
    while ( ifs.getline(buf, sizeof(buf)))
    {
        cout << buf << endl;
    }

/*     //第三种
    string buf;
    while ( getline(ifs, buf))
    {
        cout << buf << endl;
    }
     */
/*     //第四种
    char c;
    while ( (c = ifs.get()) != EOF ) //EOF end of file
    {
        cout << c << endl;
    }
     */
    

    ifs.close();
    
    
}

int main()
{

    TestRead();


}
