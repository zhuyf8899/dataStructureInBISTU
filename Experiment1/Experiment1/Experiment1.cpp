// Experiment1.cpp : 定义控制台应用程序的入口点。
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
	//节点
	int data;//储存的数据，这里就是它的序号，唯一。
	struct _Node *next;
};
typedef struct _LinkList
{
	//环链
	_Node *p_head;//头指针
	_Node *p_end;//尾指针
	int length;//环链的长度
}Linklist;

static _Node *Init_Node(int i)
{
	//初始化一个节点并返回它的地址
	_Node *node_temp;
	node_temp = ( _Node * )malloc( sizeof( _Node ) ); 
	if(!node_temp)
		exit (OVERFLOW);//溢出后操作
	node_temp->data=i;//为该节点添加数据
	node_temp->next=NULL;
	return node_temp;
}

int Init_List(Linklist *list)
{
	//初始化环形链表，并加入第一个元素
	_Node *p_node;
	p_node=Init_Node(1);
	list->p_head=p_node;
	list->p_end=p_node;//形成环链
	p_node->next=list->p_head;
	list->length=1;
	return OK;
}

static int Insert_List(Linklist *list,int number)
{
	//添加number个元素进入一个环链表
	_Node *node_new;
	for(int i=2;i<=number;i++)
	{
		//每次添加一个元素进入环链
		node_new=Init_Node(i);
		list->p_end->next=node_new;//每次将元素放置在链尾（其实环链实际上是没有尾巴的，只不过是因为有尾指针在那里吧啊喂(╯‵□′)╯︵┻━┻
		list->p_end=node_new;//修改尾指针位置至新添元素之后
		node_new->next=list->p_head;//后继是链表第一个元素
		(list->length)++;//长度+1
	}
	return OK;
}

int Round(Linklist *list,int call)
{
	//执行约瑟夫环每次弹出
	_Node *node_current,*node_pre;//node_current为弹出的那个元素，node_pre 为他的前驱
	node_current=list->p_head;//初始化两个指针的位置
	node_pre=list->p_end;
	while(list->length!=1)//当元素只剩下一个的时候就结束
	{
		int i=0;
		while(i<call-1)
		{
			//根据指令寻找要弹出元素的前驱
			node_pre=node_pre->next;
			i++;
		}
		//接下来弹出元素，即执行链表的元素删除
		node_current=node_pre->next;
		node_pre->next=node_current->next;
		printf_s("push out No.%d\n",node_current->data);
		free(node_current);
		(list->length)--;//长度减一
	}
	printf_s("The last one is No.%d\n",node_pre->data);//终止标志
	return OK;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int number,call;
	printf_s("请输入约瑟夫环的长度：");
	scanf_s("%d",&number);
	printf_s("请输入每次弹出的序号：");
	scanf_s("%d",&call);
	printf_s("本环共计长度为%d,每次弹出从上一次开始第%d个成员，将要弹出%d次。\n",number,call,number-1);
	Linklist linklist;
	Init_List(&linklist);
	Insert_List(&linklist,number);
	Round(&linklist,call);
	return OK;
}



