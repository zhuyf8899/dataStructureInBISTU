// Experiment1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
#define OK 1
#define ERROR 0

struct _Node
{
	//�ڵ�
	int data;//��������ݣ��������������ţ�Ψһ��
	struct _Node *next;
};
typedef struct _LinkList
{
	//����
	_Node *p_head;//ͷָ��
	_Node *p_end;//βָ��
	int length;//�����ĳ���
}Linklist;

static _Node *Init_Node(int i)
{
	//��ʼ��һ���ڵ㲢�������ĵ�ַ
	_Node *node_temp;
	node_temp = ( _Node * )malloc( sizeof( _Node ) ); 
	if(!node_temp)
		exit (OVERFLOW);//��������
	node_temp->data=i;//Ϊ�ýڵ��������
	node_temp->next=NULL;
	return node_temp;
}

int Init_List(Linklist *list)
{
	//��ʼ�����������������һ��Ԫ��
	_Node *p_node;
	p_node=Init_Node(1);
	list->p_head=p_node;
	list->p_end=p_node;//�γɻ���
	p_node->next=list->p_head;
	list->length=1;
	return OK;
}

static int Insert_List(Linklist *list,int number)
{
	//���number��Ԫ�ؽ���һ��������
	_Node *node_new;
	for(int i=2;i<=number;i++)
	{
		//ÿ�����һ��Ԫ�ؽ��뻷��
		node_new=Init_Node(i);
		list->p_end->next=node_new;//ÿ�ν�Ԫ�ط�������β����ʵ����ʵ������û��β�͵ģ�ֻ��������Ϊ��βָ��������ɰ�ι(�s�F����)�s��ߩ���
		list->p_end=node_new;//�޸�βָ��λ��������Ԫ��֮��
		node_new->next=list->p_head;//����������һ��Ԫ��
		(list->length)++;//����+1
	}
	return OK;
}

int Round(Linklist *list,int call)
{
	//ִ��Լɪ��ÿ�ε���
	_Node *node_current,*node_pre;//node_currentΪ�������Ǹ�Ԫ�أ�node_pre Ϊ����ǰ��
	node_current=list->p_head;//��ʼ������ָ���λ��
	node_pre=list->p_end;
	while(list->length!=1)//��Ԫ��ֻʣ��һ����ʱ��ͽ���
	{
		int i=0;
		while(i<call-1)
		{
			//����ָ��Ѱ��Ҫ����Ԫ�ص�ǰ��
			node_pre=node_pre->next;
			i++;
		}
		//����������Ԫ�أ���ִ�������Ԫ��ɾ��
		node_current=node_pre->next;
		node_pre->next=node_current->next;
		printf_s("push out No.%d\n",node_current->data);
		free(node_current);
		(list->length)--;//���ȼ�һ
	}
	printf_s("The last one is No.%d\n",node_pre->data);//��ֹ��־
	return OK;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int number,call;
	printf_s("������Լɪ�򻷵ĳ��ȣ�");
	scanf_s("%d",&number);
	printf_s("������ÿ�ε�������ţ�");
	scanf_s("%d",&call);
	printf_s("�������Ƴ���Ϊ%d,ÿ�ε�������һ�ο�ʼ��%d����Ա����Ҫ����%d�Ρ�\n",number,call,number-1);
	Linklist linklist;
	Init_List(&linklist);
	Insert_List(&linklist,number);
	Round(&linklist,call);
	return OK;
}



