// Expression.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//�����ṹ��˳��ջ
	int *base;//��ַ
	int *top;//ջ��ָ��
	int stackSize;//����ջ�����ɵĵ�Ԫ������
};
typedef struct SqStack_char
{
	//�����ṹ��˳��ջ
	char *base;//��ַ
	char *top;//ջ��ָ��
	int stackSize;//����ջ�����ɵĵ�Ԫ������
};

Status InitStack_int(SqStack_int &S)
{
	//��������ջ��ʼ��
	//��ʼ��һ����ջ
	S.base = (int*)malloc(STACKINITSIZE*sizeof(int));
	if(!S.base)
		return OVERFLOW;	//���ٿռ�ʧ��
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

Status InitStack_char(SqStack_char &S)
{
	//�ַ��͵�ջ��ʼ��
	//��ʼ��һ����ջ
	S.base = (char*)malloc(STACKINITSIZE*sizeof(char));
	if(!S.base)
		return OVERFLOW;	//���ٿռ�ʧ��
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

int GetTop(SqStack_int &S)//may be have a error here
{
	//����ջ�����Ԫ��
	if(S.top==S.base)
		return ERROR;//ջ�գ����ش���
	return *(S.top-1);//����ջ��ָ��ǰһ��λ������Ӧ��Ԫ�ظ�elem����ʱջ��ָ����ָ��һ��δ��ֵ�ĵ�ַ
}

char GetTop(SqStack_char &S)
{
	//����ջ�����Ԫ��
	if(S.top==S.base)
		return ERROR;//ջ�գ����ش���
	return *(S.top-1);//����ջ��ָ��ǰһ��λ������Ӧ��Ԫ�ظ�elem����ʱջ��ָ����ָ��һ��δ��ֵ�ĵ�ַ
}

Status Push_int(SqStack_int &S,int elem)
{
	//ѹջ����
	if(S.top-S.base >= STACKINITSIZE)
	{
		//ջ����׷�ӿռ�
		S.base = (int *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(int));
		if(!S.base)
			return ERROR;					//׷��ʧ�ܣ����ش���
		S.top = S.base+S.stackSize;			//��ջ��ָ�밲����ԭ�ռ��β����׷�ӿռ��ͷ��
		S.stackSize += STACKINCREASEMENT;	//ջ�Ĵ��Ԫ�ظ�����Ӧ����
	}
	*S.top = elem;	//��elemֵ����ջ��ָ���Ӧ�ĵ�ַ����
	S.top++;		//ջ��ָ������
	return OK;
}

Status Push_char(SqStack_char &S,char elem)
{
	//ѹջ����
	if(S.top-S.base >= STACKINITSIZE)
	{
		//ջ����׷�ӿռ�
		S.base = (char *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(char));
		if(!S.base)
			return ERROR;					//׷��ʧ�ܣ����ش���
		S.top = S.base+S.stackSize;			//��ջ��ָ�밲����ԭ�ռ��β����׷�ӿռ��ͷ��
		S.stackSize += STACKINCREASEMENT;	//ջ�Ĵ��Ԫ�ظ�����Ӧ����
	}
	*S.top = elem;	//��elemֵ����ջ��ָ���Ӧ�ĵ�ַ����
	S.top++;		//ջ��ָ������
	return OK;
}

Status Pop_int(SqStack_int &S,int &elem)
{
	//��ջ����
	if(S.base ==S.top)
		return ERROR;	//ջ�գ����ش���
	elem = *--S.top;	//ջ��ָ��������һλ��Ȼ��Ѷ�Ӧ��ַ�����ݸ���elem
	return OK;
}

Status Pop_char(SqStack_char &S,char &elem)
{
	//��ջ����
	if(S.base ==S.top)
		return ERROR;	//ջ�գ����ش���
	elem = *--S.top;	//ջ��ָ��������һλ��Ȼ��Ѷ�Ӧ��ַ�����ݸ���elem
	return OK;
}

char Precede(char elem,char c)
{
	//�Ƚ����ȼ������ء�>��,"<","="���ֽ����>��Ϊ���ȼ����ȡ�
	//���ժ�Կα�
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
	//�ԼӼ��˳��������㣬a��b��Ϊ��������thetaΪ�ַ��͵��������Ҫ����theta���ؽ����������������
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
	//�ж�c�Ƿ���һ���������
	if ( c=='+' || c =='-'|| c=='*'|| c=='/'|| c=='('|| c==')'|| c=='#')
		return true;
	else 
		return false;
}

int EvalueExpression()
{
	char c,x,theta;
	int a,b,temp=0;
	SqStack_int OPND;		//������ջ
	SqStack_char OPTR;		//�����ջ
	InitStack_char(OPTR);
	Push_char(OPTR,'#');	//��ʼ�������ջ��ջ�����ȸ�һ��#
	InitStack_int(OPND);	
	c=getchar();			//��ȡ�׸���ʼ�ַ�
	while( c!='#'|| GetTop(OPTR)!='#')
	{
		//ѭ������������Ĳ���#���߷���ջ����Ǹ�����#
		if(!In(c))
		{
			//�Բ��������д���
			temp=c-48;				//tempΪ����c��ascll��ת��Ϊ�����������ֵ
			Push_int(OPND,temp);	//ѹ��temp������c
			c=getchar();
		}
		else
		{
			//����������д���
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
	//�������ݣ����EvalueExpression�ķ���ֵ
	printf_s("%d\n",EvalueExpression());
	return 0;
}