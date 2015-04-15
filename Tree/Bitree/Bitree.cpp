// Bitree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
//#include<iostream>
//using namespace std;
struct BiNode
{
	char data;
	BiNode *lchild,*rchild;
};

void InitBinTree(BiNode *bt)				 // 操作结果：构造空二叉树T
{
   bt=NULL;
}
void CreateBinTree(BiNode *bt) //1.按照先序遍历次序递建立二叉树。
{     
	char ch; 
	scanf_s("%c",&ch);
	getchar(); 
	if (ch=='!')  
		bt=NULL; 
	else 
	{   bt=(BiNode *)malloc(sizeof(BiNode)); 
		bt->data=ch; //生成根结点 
		CreateBinTree(bt->lchild);          //构造左子树 
		CreateBinTree(bt->rchild);           //构造右子树 
	} 
} 
void preOrder(BiNode *bt)
{
	if(bt==NULL)
		return;
	else
	{
		printf("%c",bt->data);
		preOrder(bt->lchild);
		preOrder(bt->rchild);
	}
}

void Pre(BiNode *bt)
{
	int top=-1;
	BiNode *s[100];
	while(bt!=NULL||top!=-1)
	{
		while(bt!=NULL)
		{
			printf("%c",bt->data);
			s[++top]=bt;   //入栈
			bt=bt->lchild;
		}
		if(top!=-1)
		{
			bt=s[top--];
			bt=bt->rchild;
		}
	}
}

void In(BiNode *bt)
{
	int top=-1;
	BiNode *s[100];
	while(bt!=NULL||top!=-1)
	{
		while(bt!=NULL)
		{
			s[++top]=bt;
			bt=bt->lchild;
		}
		while(top!=1)
		{
			bt=s[top--];
			printf("%c",bt->data);
			bt=bt->rchild;
		}
	}
}

struct Element
{
	BiNode *ptr;   
	int flag;
};
void Post(BiNode *bt)
{
	Element s[100];
	int top=-1;
	while(bt!=NULL||top!=-1)
	{
		while(bt!=NULL)
		{
			top++;
			s[top].ptr=bt;
			s[top].flag=1;
			bt=bt->lchild;
		}
		while(top!=-1&&s[top].flag==2)
		{
			bt=s[top--].ptr;
			printf("%c",bt->data);
		}
		if(top!=-1)
		{
			s[top].flag=2;
			bt=s[top].ptr->lchild;
		}
	}
}


void main()
{
	BiNode *bt;
	bt=(BiNode *)malloc(sizeof(BiNode)); 

	InitBinTree(bt);
    CreateBinTree(bt);
	preOrder(bt);
    printf("非递归先序遍历为：");
	//Pre(bt);
	printf("\n");
	printf("非递归中序遍历为：");
	//In(bt);
	printf("\n");
	printf("非递归后序遍历为：");
	//Post(bt);
	printf("\n");

}
