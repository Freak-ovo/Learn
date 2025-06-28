#include<iostream>
#include<malloc.h>
using namespace std;

// 函数结果状态码 
#define OK 1    //成功标识
#define ERROR 0 //失败标识

#define MAXSIZE 100  //线性表存储空间的初始分配量

typedef int Status;	//Status是函数的类型，其值是函数结果状态代码，如OK等

typedef int ElemType;   //ElemType的类型根据实际情况而定，这里假定为int

//顺序表数据结构
typedef struct
    {
    ElemType *elem;/    /存储空间的基地址
    int length;     //多项式当前的个数
    }SqList;
