// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
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
typedef int SElemType;	//�����������������int���͵�

typedef struct SqStack
{
	//�����ṹ��˳��ջ
	SElemType *base;//��ַ
	SElemType *top;//ջ��ָ��
	int stackSize;//����ջ�����ɵĵ�Ԫ������
};

Status InitStack(SqStack &S)
{
	//��ʼ��һ����ջ
	S.base = (SElemType*)malloc(STACKINITSIZE*sizeof(SElemType));
	if(!S.base)
		return OVERFLOW;	//���ٿռ�ʧ��
	S.top = S.base;
	S.stackSize = STACKINITSIZE;
	return OK;
}

Status GetTop(SqStack &S,SElemType &elem)
{
	//����ջ�����Ԫ��
	if(S.top==S.base)
		return ERROR;//ջ�գ����ش���
	elem = *(S.top-1);//����ջ��ָ��ǰһ��λ������Ӧ��Ԫ�ظ�elem����ʱջ��ָ����ָ��һ��δ��ֵ�ĵ�ַ��
	return OK;
}

Status Push(SqStack &S,SElemType elem)
{
	//ѹջ����
	if(S.top-S.base >= STACKINITSIZE)
	{
		//ջ����׷�ӿռ�
		S.base = (SElemType *)realloc(S.base,(STACKINITSIZE + STACKINCREASEMENT) * sizeof(SElemType));
		if(!S.base)
			return ERROR;					//׷��ʧ�ܣ����ش���
		S.top = S.base+S.stackSize;			//��ջ��ָ�밲����ԭ�ռ��β����׷�ӿռ��ͷ��
		S.stackSize += STACKINCREASEMENT;	//ջ�Ĵ��Ԫ�ظ�����Ӧ����
	}
	*S.top = elem;	//��elemֵ����ջ��ָ���Ӧ�ĵ�ַ����
	S.top++;		//ջ��ָ������
	return OK;
}

Status Pop(SqStack &S,SElemType &elem)
{
	//��ջ����
	if(S.base ==S.top)
		return ERROR;	//ջ�գ����ش���
	elem = *--S.top;	//ջ��ָ��������һλ��Ȼ��Ѷ�Ӧ��ַ�����ݸ���elem
	return OK;
}

int main()
{
	//��������
	SElemType a[5]={1,2,3,4,5};
	SElemType result;
	SqStack stack;
	printf_s("��ʼ��ջ...���\n");
	InitStack(stack);
	//ѹջ˳��ѹ����������ѹ����������
	printf_s("ѹջ˳��ѹ����������ѹ����������\n");
	Push(stack,a[0]);
	Push(stack,a[1]);
	Push(stack,a[2]);
	GetTop(stack,result);
	printf("ѹջ�����Ժ�����ջ����Ԫ����:%d\n",result);//����3
	Pop(stack,result);
	Pop(stack,result);
	GetTop(stack,result);
	printf("��ջ�����Ժ�����ջ����Ԫ����:%d\n",result);//����1
	Push(stack,a[3]);
	Push(stack,a[4]);
	GetTop(stack,result);
	printf("��ѹ���δ��Ժ�����ջ����Ԫ����:%d\n",result);//����5
	while(stack.top != stack.base)
		Pop(stack,result);
	return 0;
}