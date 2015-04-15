// BaseOperate.cpp : 定义控制台应用程序的入口点。
//@pragma 
//	author: zhuyifan
//	last changed:2013/11/20

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
	//定义树结点假设data为char类型
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;//这里BiTNode是结构体，BiTree是指针， 用于指向根节点

BiTree Create_BiTree_NoTraverse()
{
	//非递归创建二叉树，按照完全二叉树的格式
	BiTNode *T=NULL ,*p, *s[100];		//s为储存结点地址的一个栈
	char ch;
	int i,j;
	while(1)
	{
		 scanf_s("%d", &i);				//先读入一个数字为完全二叉树层次编号
		 if(i==0)						//终止为0
		 {
			 break;
		 }
		 else
		 {
			scanf_s("%c", &ch);			//如果不为0，接着读下一个字符，因此格式为1a，2b...
			p=(BiTNode *)malloc(sizeof(BiTNode)) ;
			p->data=ch ;
			p->lchild = NULL;			//这里一定要初始化结点的所有内容，即使为空也要写上
			p->rchild = NULL;
			s[i]=p;						//在s中记录这个值
			if(i==1)					//对根节点的处置（就是函数最后返回他）
			{
				T=p;
			}
			else
			{
				//对非根节点的处置
				j=i/2;					//先计算出该节点的双亲节点（其实就是除以2取整）
				if (i%2==0)
				{
					s[j]->lchild=p ;	//检查i是否为偶数，是的话就安排双亲节点在左节点（奇数安排在有节点）
				}
				else 
				{
					s[j]->rchild=p ;
				}
			}
	     }
	}
	return(T);
}

BiTree CreateBiTree()
{
	//递归创建二叉树
    char p;
	BiTree T;
    scanf_s("%c",&p);						//每次读取一个字符
    if(p=='!')
	{
		T = NULL;							//输入为！时，这个函数就返回空（即这个节点为空）
	}
    else
    {
        T=(BiTNode *)malloc(sizeof(BiTNode));//为结点开辟空间
        T->data=p;							
        T->lchild=CreateBiTree();			//开始递归，先构造节点左子树然后是右子树
        T->rchild=CreateBiTree();
    }
    return (T);								//函数返回T（地址或者NULL）
}

void PreOrder(BiTree T)
{
	//递归先序遍历
   if(T!=NULL)
   {
	   //这要当前节点不为空，就一直递归下去
       printf("%c",T->data);//优先输出当前节点（使输出的结果始终保持中间结点在前面）
	   PreOrder(T->lchild);	//优先递归左节点
       PreOrder(T->rchild);
      
    }
}

void InOrder(BiTree T)
{
	//递归中序遍历
   if(T!=NULL)
   {
	   //算法同先序
       InOrder(T->lchild);
       printf("%c",T->data);	//在左节点都被递归完了才从下方网上输出节点，这样保持中间结点始终在左右子节点中间
       InOrder(T->rchild);
      
    }
}

void PostOrder(BiTree T)
{
	//递归后序遍历
   if(T!=NULL)
    {
		//算法同先序
       PostOrder(T->lchild);
       PostOrder(T->rchild);
       printf("%c",T->data);	//递归完右节点才从后往前输出，保持中间结点在左右节点的后方。
    }
}

void PreOrder_NoTraaverse(BiTNode *bt)
{
	//非递归先序遍历
	int top=-1;						//标示符从-1开始，用于栈s的构建
	BiTNode *s[100];				//栈s用一个数组实现（C++提供stack这个合适，但这个是C）
	/*
	 *	这里要说明一下：在遍历的过程中有几个可能：
	 *	1.bt结点不为空，top=-1：这说明刚刚开始遍历或者；遍历已经进行到根节点的左子树遍历完成，返回到根节点了
	 *	2.bt结点为空，top！=-1：这说明遍历到了一个树叶的子节点；
	 *	3.bt结点不为空，top!=-1：这说明遍历在一个普通的结点上；
	 *	4.bt为空，top=-1：遍历完了根节点的右子树，跳出循环。
	 */
	
	while(bt!=NULL||top!=-1)
	{
		while(bt!=NULL)
		{
			//对于普通节点
			//先序遍历要先输出遍历到了的结点
			printf("%c",bt->data);
			s[++top]=bt;			//入栈
			bt=bt->lchild;			//一直尝试走结点的左子树
		}
		if(top!=-1)
		{
			//对于空的结点的应对
			/*
			 *	首先取上一节点（就是之前最后有意义的结点）的右子树，同时出栈
			 *	如果右子树又存在继续入站遍历，
			 *	若右子树不存在便由于之前出栈的原因跳到了上上个结点继续重复此操作
			*/
			bt=s[top--];
			bt=bt->rchild;
		}
	}
}

void InOrder_NoTraaverse(BiTree bt) 
{  
	//非递归中序遍历二叉树
	BiTNode *stack[100];            //定义栈
	int top=0;                      //这里调整标示符，从0
	stack[top]=bt; 
	while(top>=0)
	{  
		while(stack[top]!=NULL)		//遍历左节点，依次入栈
		{   
			top=top+1; 
			stack[top]=stack[top-1]->lchild; 
		} 
		top=top-1;					//左节点遍历不能，开始退栈
		if(top>=0)					//判断栈是否为空，为空的应对
		{   
			printf("%c",stack[top]->data);          //输出结点
			stack[top]=stack[top]->rchild;          //然后试图访问右子树
		} 
	}
} 

struct Element
{
	//定义Element类型，用于非递归的后序遍历
	BiTNode *ptr;   
	int flag;					//这里要增加一个标示符flag：1为第一次访问，2为第二次
};

void PostOrder_NoTraaverse(BiTNode *bt)
{
	Element s[100];				//这里的栈就是Element的类型了
	int top=-1;					//这个还是标示符
	while(bt!=NULL||top!=-1)
	{
		/*
		*	有几种情况：
		*	1.bt不为空，就给flag为1，继续尝试访问左节点
		*	2.bt为空，就给上一个结点的flag为2，继续尝试访问上一结点的右节点
		*	3.结点flag为2，此时输出该节点的值，返回上一节点检查flag，如此反复
		*	4.当满足bt!=NULL && s[top+1].flag==2&&top==-1时，即为终止条件满足访问完了根节点的所有左右子树，跳出
		*/
		if(bt!=NULL && s[top+1].flag==2&&top==-1)	//检查退出条件
		{
			break;
		}
		while(bt!=NULL)								//访问一般结点的操作
		{
			top++;
			s[top].ptr=bt;
			s[top].flag=1;
			bt=bt->lchild;
		}
		while(top!=-1&&s[top].flag==2)				//访问到空节点且上一节点左节点已经遍历完成的处理
		{
			bt=s[top--].ptr;
			printf("%c",bt->data);
		}
		if(top!=-1)									//访问到空节点但上一节点右节点未访问的处理
		{
			s[top].flag=2;
			bt=s[top].ptr->rchild;
		}
	}
}

void main()
{
	//主函数，测试数据
     BiTree Ta,Tb;
	 printf_s("递归初始化树Ta，格式为先序遍历但是要加入左右子树为空的情况：\n");
     Ta=CreateBiTree();
     printf("先序遍历:");
     printf("\n");
     PreOrder(Ta);
     printf("\n");
     printf("中序遍历:");
     printf("\n");
     InOrder(Ta);
     printf("\n");
     printf("后序遍历:");
     printf("\n");
     PostOrder(Ta);
     printf("\n");
	 printf("非递归初始化树Tb，格式为完全二叉树形式，一个数字接着一个字符，输入0为终止：\n");
	 Tb=Create_BiTree_NoTraverse();
	 printf("非递归先序遍历为：");
	 PreOrder_NoTraaverse(Tb);
	 printf("\n");
	 printf("非递归中序遍历为：");
	 InOrder_NoTraaverse(Tb);
	 printf("\n");
	 printf("非递归后序遍历为：");
	 PostOrder_NoTraaverse(Tb);
	 printf("\n");
}
