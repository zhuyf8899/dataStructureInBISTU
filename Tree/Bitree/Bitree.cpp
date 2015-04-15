// Bitree.cpp : �������̨Ӧ�ó������ڵ㡣
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

void InitBinTree(BiNode *bt)				 // �������������ն�����T
{
   bt=NULL;
}
void CreateBinTree(BiNode *bt) //1.���������������ݽ�����������
{     
	char ch; 
	scanf_s("%c",&ch);
	getchar(); 
	if (ch=='!')  
		bt=NULL; 
	else 
	{   bt=(BiNode *)malloc(sizeof(BiNode)); 
		bt->data=ch; //���ɸ���� 
		CreateBinTree(bt->lchild);          //���������� 
		CreateBinTree(bt->rchild);           //���������� 
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
			s[++top]=bt;   //��ջ
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
    printf("�ǵݹ��������Ϊ��");
	//Pre(bt);
	printf("\n");
	printf("�ǵݹ��������Ϊ��");
	//In(bt);
	printf("\n");
	printf("�ǵݹ�������Ϊ��");
	//Post(bt);
	printf("\n");

}
