// Expression.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
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

typedef struct SqStack_int
{
	//声明结构体顺序栈
	int *base;//基址
	int *top;//栈顶指针
	int stackSize;//整个栈可容纳的的元素数量
};
typedef struct SqStack_char
{
	//声明结构体顺序栈
	char *base;//基址
	char *top;//栈顶指针
	int stackSize;//整个栈可容纳的的元素数量
};

Status InitStack_int(SqStack_int &S)
{
	//整型数的栈初始化
	//初始化一个空栈
	S.base = (int*)malloc(STACKINITSIZE*sizeof(int));
	if(!S.base)
		return OVERFLOW;	//开辟空间失败
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

Status InitStack_char(SqStack_char &S)
{
	//字符型的栈初始化
	//初始化一个空栈
	S.base = (char*)malloc(STACKINITSIZE*sizeof(char));
	if(!S.base)
		return OVERFLOW;	//开辟空间失败
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

int GetTop(SqStack_int &S)//may be have a error here
{
	//返回栈的最顶端元素
	if(S.top==S.base)
		return ERROR;//栈空，返回错误
	return *(S.top-1);//返回栈顶指针前一个位置所对应的元素给elem（此时栈顶指针是指向一个未赋值的地址
}

char GetTop(SqStack_char &S)
{
	//返回栈的最顶端元素
	if(S.top==S.base)
		return ERROR;//栈空，返回错误
	return *(S.top-1);//返回栈顶指针前一个位置所对应的元素给elem（此时栈顶指针是指向一个未赋值的地址
}

Status Push_int(SqStack_int &S,int elem)
{
	//压栈操作
	if(S.top-S.base >= STACKINITSIZE)
	{
		//栈满，追加空间
		S.base = (int *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(int));
		if(!S.base)
			return ERROR;					//追加失败，返回错误
		S.top = S.base+S.stackSize;			//将栈顶指针安放在原空间的尾部即追加空间的头部
		S.stackSize += STACKINCREASEMENT;	//栈的存放元素个数相应增加
	}
	*S.top = elem;	//将elem值赋给栈顶指针对应的地址内容
	S.top++;		//栈顶指针上移
	return OK;
}

Status Push_char(SqStack_char &S,char elem)
{
	//压栈操作
	if(S.top-S.base >= STACKINITSIZE)
	{
		//栈满，追加空间
		S.base = (char *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(char));
		if(!S.base)
			return ERROR;					//追加失败，返回错误
		S.top = S.base+S.stackSize;			//将栈顶指针安放在原空间的尾部即追加空间的头部
		S.stackSize += STACKINCREASEMENT;	//栈的存放元素个数相应增加
	}
	*S.top = elem;	//将elem值赋给栈顶指针对应的地址内容
	S.top++;		//栈顶指针上移
	return OK;
}

Status Pop_int(SqStack_int &S,int &elem)
{
	//弹栈操作
	if(S.base ==S.top)
		return ERROR;	//栈空，返回错误
	elem = *--S.top;	//栈顶指针先下移一位，然后把对应地址的内容赋给elem
	return OK;
}

Status Pop_char(SqStack_char &S,char &elem)
{
	//弹栈操作
	if(S.base ==S.top)
		return ERROR;	//栈空，返回错误
	elem = *--S.top;	//栈顶指针先下移一位，然后把对应地址的内容赋给elem
	return OK;
}

char Precede(char elem,char c)
{
	//比较优先级，返回“>”,"<","="三种结果，>则为优先级优先。
	//表格摘自课本
	if (elem=='+')
	{
		switch (c)
		{
		case '+':return '>';break;
		case '-':return '>';break;
		case '*':return '<';break;
		case '/':return '<';break;
		case '(':return '<';break;
		case ')':return '>';break;
		case '#':return '>';break;
		}
	}
	if (elem=='-')
	{
		switch (c)
		{
		case '+':return '>';break;
		case '-':return '>';break;
		case '*':return '<';break;
		case '/':return '<';break;
		case '(':return '<';break;
		case ')':return '>';break;
		case '#':return '>';break;
		}
	}
	if (elem=='*')
	{
		switch (c)
		{
		case '+':return '>';break;
		case '-':return '>';break;
		case '*':return '>';break;
		case '/':return '>';break;
		case '(':return '<';break;
		case ')':return '>';break;
		case '#':return '>';break;
		}
	}
	if (elem=='/')
	{
		switch (c)
		{
		case '+':return '>';break;
		case '-':return '>';break;
		case '*':return '>';break;
		case '/':return '>';break;
		case '(':return '<';break;
		case ')':return '>';break;
		case '#':return '>';break;
		}
	}
	if (elem=='(')
	{
		switch (c)
		{
		case '+':return '<';break;
		case '-':return '<';break;
		case '*':return '<';break;
		case '/':return '<';break;
		case '(':return '<';break;
		case ')':return '=';break;
		case '#':return 'F';break;
		}
	}
	if (elem==')')
	{
		switch (c)
		{
		case '+':return '>';break;
		case '-':return '>';break;
		case '*':return '>';break;
		case '/':return '>';break;
		case '(':return 'F';break;
		case ')':return '>';break;
		case '#':return '>';break;
		}
	}
	if (elem=='#')
	{
		switch (c)
		{
		case '+':return '<';break;
		case '-':return '<';break;
		case '*':return '<';break;
		case '/':return '<';break;
		case '(':return '<';break;
		case ')':return 'F';break;
		case '#':return '=';break;
		}
	}
}

int operate(int a,char theta,int b)
{
	//对加减乘除进行运算，a，b均为操作数，theta为字符型的运算符，要分析theta返回结果，返回运算结果。
	switch(theta)
	{
	case '+':
		return (a+b);break;
	case '-':
		return (a-b);break;
	case'*':
		return (a*b);break;
	case'/':
		return (a/b);break;
	}
}

bool In(char c)
{
	//判断c是否是一个运算符号
	if ( c=='+' || c =='-'|| c=='*'|| c=='/'|| c=='('|| c==')'|| c=='#')
		return true;
	else 
		return false;
}

int EvalueExpression()
{
	char c,x,theta;
	int a,b,temp=0;
	SqStack_int OPND;		//操作数栈
	SqStack_char OPTR;		//运算符栈
	InitStack_char(OPTR);
	Push_char(OPTR,'#');	//初始化运算符栈，栈中首先给一个#
	InitStack_int(OPND);	
	c=getchar();			//获取首个起始字符
	while( c!='#'|| GetTop(OPTR)!='#')
	{
		//循环条件：输入的不是#或者符号栈最顶层那个不是#
		if(!In(c))
		{
			//对操作数进行处理
			temp=c-48;				//temp为读入c的ascll码转换为正常整数后的值
			Push_int(OPND,temp);	//压入temp而不是c
			c=getchar();
		}
		else
		{
			//对运算符进行处理
			switch(Precede(GetTop(OPTR),c))
			{
			case '<':
				Push_char(OPTR,c);c=getchar();break;
			case '=':
				Pop_char(OPTR,x);c=getchar();break;
			case'>':
				Pop_char(OPTR,theta);
				Pop_int(OPND,b);
				Pop_int(OPND,a);
				Push_int(OPND,operate(a,theta,b));
				break;
			}
		}
		
	}
	return GetTop(OPND);
}

int main()
{
	//测试数据，输出EvalueExpression的返回值
	printf_s("%d\n",EvalueExpression());
	return 0;
}