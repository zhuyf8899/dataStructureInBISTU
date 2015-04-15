// Queue.cpp : �������̨Ӧ�ó������ڵ㡣
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
typedef int QElemType;	//�����������������int���͵�

typedef struct QNode
{
	//�����ڵ����ͽṹ��
	QElemType data;
	QNode *next;
}QNode,*QueuePtr;
//������������������ʵ��һ�ֽṹ�壩��һ������ָ�ڵ㣬һ����ָ�ڵ����͵�ָ�룬���岻���Ķ�����

typedef struct LinkQueue
{
	//������ʽ����
	QueuePtr front;
	QueuePtr rear;
};

Status InitQueue(LinkQueue &Q,QElemType elem)
{
	//��ʼ��һ������һ���ڵ����ʽ����
	Q.rear=Q.front=(QueuePtr)malloc(sizeof(QNode));
	if(!Q.rear)
		return OVERFLOW;	//����ʧ��
	Q.front->next=NULL;
	Q.front->data=elem;
	return OK;
}

Status DestroyQueue(LinkQueue &Q)
{
	//����һ����ʽ����
	while(Q.front)
	{
		//��ͷ��β��������ֱ����սڵ�Ϊֹ
		Q.rear=Q.front->next;
		free(Q.front);
		Q.front=Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue &Q,QElemType elem)
{
	//��β����һ���ڵ�
	QueuePtr temp;
	temp=(QueuePtr)malloc(sizeof(QNode));
	if (!temp)
		return OVERFLOW;//���ٿռ�ʧ��
	temp->data = elem;
	temp->next = NULL;
	Q.rear->next = temp;//��ʼ��������β��
	Q.rear = temp;
	return OK;
}

Status DeQueue(LinkQueue &Q,QElemType &elem)
{
	//��������ͷ����һ���ڵ�
	QueuePtr temp;
	if(Q.front==Q.rear)
		return ERROR;//����Ϊ��
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
	printf_s("�����������Ϊ��");
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
	//��������
	QElemType a[5]={2,3,4,5,6};
	QElemType result;
	LinkQueue queue;
	InitQueue(queue,1);
	printf_s("��ʼ������...���\n");
	PrintQueue(queue);
	//����˳�򣺽�������������������������ն���
	printf_s("���н�������Ԫ��...");
	EnQueue(queue,a[0]);
	EnQueue(queue,a[1]);
	EnQueue(queue,a[2]);
	printf_s("���\n");
	PrintQueue(queue);
	printf_s("�����˳�����Ԫ��...");
	DeQueue(queue,result);
	DeQueue(queue,result);
	printf_s("���\n");
	PrintQueue(queue);
	printf_s("���н�������Ԫ��...");
	EnQueue(queue,a[3]);
	EnQueue(queue,a[4]);
	printf_s("���\n");
	PrintQueue(queue);
	printf_s("���ٶ���...");
	DestroyQueue(queue);
	printf_s("���\n");


}