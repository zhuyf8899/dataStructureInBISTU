// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
/*


int _tmain(int argc, _TCHAR* argv[])
{
	return 0;
}
*/

#include <stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

#define STACKINITSIZE 100
#define STACKINCREASEMENT 10
typedef int Status;		
typedef int SElemType;	//这里假设数据类型是int类型的

typedef struct SqStack
{
	//声明结构体顺序栈
	SElemType *base;//基址
	SElemType *top;//栈顶指针
	int stackSize;//整个栈可容纳的的元素数量
};

Status InitStack(SqStack &S)
{
	//初始化一个空栈
	S.base = (SElemType*)malloc(STACKINITSIZE*sizeof(SElemType));
	if(!S.base)
		return OVERFLOW;	//开辟空间失败
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

Status GetTop(SqStack &S,SElemType &elem)
{
	//返回栈的最顶端元素
	if(S.top==S.base)
		return ERROR;//栈空，返回错误
	elem = *(S.top-1);//返回栈顶指针前一个位置所对应的元素给elem（此时栈顶指针是指向一个未赋值的地址）
	return OK;
}

Status Push(SqStack &S,SElemType elem)
{
	//压栈操作
	if(S.top-S.base >= STACKINITSIZE)
	{
		//栈满，追加空间
		S.base = (SElemType *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(SElemType));
		if(!S.base)
			return ERROR;					//追加失败，返回错误
		S.top = S.base+S.stackSize;			//将栈顶指针安放在原空间的尾部即追加空间的头部
		S.stackSize += STACKINCREASEMENT;	//栈的存放元素个数相应增加
	}
	*S.top = elem;	//将elem值赋给栈顶指针对应的地址内容
	S.top++;		//栈顶指针上移
	return OK;
}

Status Pop(SqStack &S,SElemType &elem)
{
	//弹栈操作
	if(S.base ==S.top)
		return ERROR;	//栈空，返回错误
	elem = *--S.top;	//栈顶指针先下移一位，然后把对应地址的内容赋给elem
	return OK;
}

int main()
{
	//测试样例
	SElemType a[5]={1,2,3,4,5};
	SElemType result;
	SqStack stack;
	printf_s("初始化栈...完成\n");
	InitStack(stack);
	//压栈顺序：压三个弹两个压两个弹三个
	printf_s("压栈顺序：压三个弹两个压两个弹三个\n");
	Push(stack,a[0]);
	Push(stack,a[1]);
	Push(stack,a[2]);
	GetTop(stack,result);
	printf("压栈三次以后，现在栈顶的元素是:%d\n",result);//答案是3
	Pop(stack,result);
	Pop(stack,result);
	GetTop(stack,result);
	printf("弹栈两次以后，现在栈顶的元素是:%d\n",result);//答案是1
	Push(stack,a[3]);
	Push(stack,a[4]);
	GetTop(stack,result);
	printf("再压两次次以后，现在栈顶的元素是:%d\n",result);//答案是5
	while(stack.top != stack.base)
		Pop(stack,result);
	return 0;
}