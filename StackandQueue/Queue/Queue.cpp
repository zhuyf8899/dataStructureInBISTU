// Queue.cpp : 定义控制台应用程序的入口点。
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
typedef int QElemType;	//这里假设数据类型是int类型的

typedef struct QNode
{
	//声明节点类型结构体
	QElemType data;
	QNode *next;
}QNode,*QueuePtr;
//这里声明了两个（其实是一种结构体），一个就是指节点，一个是指节点类型的指针，意义不大，阅读方便

typedef struct LinkQueue
{
	//声明链式队列
	QueuePtr front;
	QueuePtr rear;
};

Status InitQueue(LinkQueue &Q,QElemType elem)
{
	//初始化一个带有一个节点的链式队列
	Q.rear=Q.front=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.rear)
		return OVERFLOW;	//分配失败
	Q.front->next=NULL;
	Q.front->data=elem;
	return OK;
}

Status DestroyQueue(LinkQueue &Q)
{
	//销毁一个链式队列
	while(Q.front)
	{
		//从头至尾遍历链，直到清空节点为止
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType elem)
{
	//队尾插入一个节点
	QueuePtr temp;
	temp=(QueuePtr)malloc(sizeof(QNode));
	if (!temp)
		return OVERFLOW;//开辟空间失败
	temp->data = elem;
	temp->next = NULL;
	Q.rear->next = temp;//开始增加链的尾部
	Q.rear = temp;
	return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &elem)
{
	//弹出队列头部第一个节点
	QueuePtr temp;
	if(Q.front==Q.rear)
		return ERROR;//队列为空
	elem = Q.front->data;
	temp = Q.front;
	Q.front=Q.front->next;
	free(temp);
	return OK;
}
Status PrintQueue(LinkQueue &Q)
{
	QueuePtr temp;
	temp=Q.front;
	printf_s("现在这个队列为：");
	while(temp)
	{
		printf_s("%d ",temp->data);
		temp = temp->next;
	}
	printf_s("\n");
	return OK;
}

int main()
{
	//测试样例
	QElemType a[5]={2,3,4,5,6};
	QElemType result;
	LinkQueue queue;
	InitQueue(queue,1);
	printf_s("初始化队列...完成\n");
	PrintQueue(queue);
	//进出顺序：进三个，出两个，进两个，清空队列
	printf_s("队列进入三个元素...");
	EnQueue(queue,a[0]);
	EnQueue(queue,a[1]);
	EnQueue(queue,a[2]);
	printf_s("完成\n");
	PrintQueue(queue);
	printf_s("队列退出两个元素...");
	DeQueue(queue,result);
	DeQueue(queue,result);
	printf_s("完成\n");
	PrintQueue(queue);
	printf_s("队列进入两个元素...");
	EnQueue(queue,a[3]);
	EnQueue(queue,a[4]);
	printf_s("完成\n");
	PrintQueue(queue);
	printf_s("销毁队列...");
	DestroyQueue(queue);
	printf_s("完成\n");


}