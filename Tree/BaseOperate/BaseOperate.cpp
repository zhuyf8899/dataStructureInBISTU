// BaseOperate.cpp : �������̨Ӧ�ó������ڵ㡣
//@pragma 
//	author: zhuyifan
//	last changed:2013/11/20

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct BiTNode
{
	//������������dataΪchar����
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;//����BiTNode�ǽṹ�壬BiTree��ָ�룬 ����ָ����ڵ�

BiTree Create_BiTree_NoTraverse()
{
	//�ǵݹ鴴����������������ȫ�������ĸ�ʽ
	BiTNode *T=NULL ,*p, *s[100];		//sΪ�������ַ��һ��ջ
	char ch;
	int i,j;
	while(1)
	{
		 scanf_s("%d", &i);				//�ȶ���һ������Ϊ��ȫ��������α��
		 if(i==0)						//��ֹΪ0
		 {
			 break;
		 }
		 else
		 {
			scanf_s("%c", &ch);			//�����Ϊ0�����Ŷ���һ���ַ�����˸�ʽΪ1a��2b...
			p=(BiTNode *)malloc(sizeof(BiTNode)) ;
			p->data=ch ;
			p->lchild = NULL;			//����һ��Ҫ��ʼ�������������ݣ���ʹΪ��ҲҪд��
			p->rchild = NULL;
			s[i]=p;						//��s�м�¼���ֵ
			if(i==1)					//�Ը��ڵ�Ĵ��ã����Ǻ�����󷵻�����
			{
				T=p;
			}
			else
			{
				//�ԷǸ��ڵ�Ĵ���
				j=i/2;					//�ȼ�����ýڵ��˫�׽ڵ㣨��ʵ���ǳ���2ȡ����
				if (i%2==0)
				{
					s[j]->lchild=p ;	//���i�Ƿ�Ϊż�����ǵĻ��Ͱ���˫�׽ڵ�����ڵ㣨�����������нڵ㣩
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
	//�ݹ鴴��������
    char p;
	BiTree T;
    scanf_s("%c",&p);						//ÿ�ζ�ȡһ���ַ�
    if(p=='!')
	{
		T = NULL;							//����Ϊ��ʱ����������ͷ��ؿգ�������ڵ�Ϊ�գ�
	}
    else
    {
        T=(BiTNode *)malloc(sizeof(BiTNode));//Ϊ��㿪�ٿռ�
        T->data=p;							
        T->lchild=CreateBiTree();			//��ʼ�ݹ飬�ȹ���ڵ�������Ȼ����������
        T->rchild=CreateBiTree();
    }
    return (T);								//��������T����ַ����NULL��
}

void PreOrder(BiTree T)
{
	//�ݹ��������
   if(T!=NULL)
   {
	   //��Ҫ��ǰ�ڵ㲻Ϊ�գ���һֱ�ݹ���ȥ
       printf("%c",T->data);//���������ǰ�ڵ㣨ʹ����Ľ��ʼ�ձ����м�����ǰ�棩
	   PreOrder(T->lchild);	//���ȵݹ���ڵ�
       PreOrder(T->rchild);
      
    }
}

void InOrder(BiTree T)
{
	//�ݹ��������
   if(T!=NULL)
   {
	   //�㷨ͬ����
       InOrder(T->lchild);
       printf("%c",T->data);	//����ڵ㶼���ݹ����˲Ŵ��·���������ڵ㣬���������м���ʼ���������ӽڵ��м�
       InOrder(T->rchild);
      
    }
}

void PostOrder(BiTree T)
{
	//�ݹ�������
   if(T!=NULL)
    {
		//�㷨ͬ����
       PostOrder(T->lchild);
       PostOrder(T->rchild);
       printf("%c",T->data);	//�ݹ����ҽڵ�ŴӺ���ǰ����������м��������ҽڵ�ĺ󷽡�
    }
}

void PreOrder_NoTraaverse(BiTNode *bt)
{
	//�ǵݹ��������
	int top=-1;						//��ʾ����-1��ʼ������ջs�Ĺ���
	BiTNode *s[100];				//ջs��һ������ʵ�֣�C++�ṩstack������ʣ��������C��
	/*
	 *	����Ҫ˵��һ�£��ڱ����Ĺ������м������ܣ�
	 *	1.bt��㲻Ϊ�գ�top=-1����˵���ոտ�ʼ�������ߣ������Ѿ����е����ڵ��������������ɣ����ص����ڵ���
	 *	2.bt���Ϊ�գ�top��=-1����˵����������һ����Ҷ���ӽڵ㣻
	 *	3.bt��㲻Ϊ�գ�top!=-1����˵��������һ����ͨ�Ľ���ϣ�
	 *	4.btΪ�գ�top=-1���������˸��ڵ��������������ѭ����
	 */
	
	while(bt!=NULL||top!=-1)
	{
		while(bt!=NULL)
		{
			//������ͨ�ڵ�
			//�������Ҫ������������˵Ľ��
			printf("%c",bt->data);
			s[++top]=bt;			//��ջ
			bt=bt->lchild;			//һֱ�����߽���������
		}
		if(top!=-1)
		{
			//���ڿյĽ���Ӧ��
			/*
			 *	����ȡ��һ�ڵ㣨����֮ǰ���������Ľ�㣩����������ͬʱ��ջ
			 *	����������ִ��ڼ�����վ������
			 *	�������������ڱ�����֮ǰ��ջ��ԭ�����������ϸ��������ظ��˲���
			*/
			bt=s[top--];
			bt=bt->rchild;
		}
	}
}

void InOrder_NoTraaverse(BiTree bt) 
{  
	//�ǵݹ��������������
	BiTNode *stack[100];            //����ջ
	int top=0;                      //���������ʾ������0
	stack[top]=bt; 
	while(top>=0)
	{  
		while(stack[top]!=NULL)		//������ڵ㣬������ջ
		{   
			top=top+1; 
			stack[top]=stack[top-1]->lchild; 
		} 
		top=top-1;					//��ڵ�������ܣ���ʼ��ջ
		if(top>=0)					//�ж�ջ�Ƿ�Ϊ�գ�Ϊ�յ�Ӧ��
		{   
			printf("%c",stack[top]->data);          //������
			stack[top]=stack[top]->rchild;          //Ȼ����ͼ����������
		} 
	}
} 

struct Element
{
	//����Element���ͣ����ڷǵݹ�ĺ������
	BiTNode *ptr;   
	int flag;					//����Ҫ����һ����ʾ��flag��1Ϊ��һ�η��ʣ�2Ϊ�ڶ���
};

void PostOrder_NoTraaverse(BiTNode *bt)
{
	Element s[100];				//�����ջ����Element��������
	int top=-1;					//������Ǳ�ʾ��
	while(bt!=NULL||top!=-1)
	{
		/*
		*	�м��������
		*	1.bt��Ϊ�գ��͸�flagΪ1���������Է�����ڵ�
		*	2.btΪ�գ��͸���һ������flagΪ2���������Է�����һ�����ҽڵ�
		*	3.���flagΪ2����ʱ����ýڵ��ֵ��������һ�ڵ���flag����˷���
		*	4.������bt!=NULL && s[top+1].flag==2&&top==-1ʱ����Ϊ��ֹ��������������˸��ڵ��������������������
		*/
		if(bt!=NULL && s[top+1].flag==2&&top==-1)	//����˳�����
		{
			break;
		}
		while(bt!=NULL)								//����һ����Ĳ���
		{
			top++;
			s[top].ptr=bt;
			s[top].flag=1;
			bt=bt->lchild;
		}
		while(top!=-1&&s[top].flag==2)				//���ʵ��սڵ�����һ�ڵ���ڵ��Ѿ�������ɵĴ���
		{
			bt=s[top--].ptr;
			printf("%c",bt->data);
		}
		if(top!=-1)									//���ʵ��սڵ㵫��һ�ڵ��ҽڵ�δ���ʵĴ���
		{
			s[top].flag=2;
			bt=s[top].ptr->rchild;
		}
	}
}

void main()
{
	//����������������
     BiTree Ta,Tb;
	 printf_s("�ݹ��ʼ����Ta����ʽΪ�����������Ҫ������������Ϊ�յ������\n");
     Ta=CreateBiTree();
     printf("�������:");
     printf("\n");
     PreOrder(Ta);
     printf("\n");
     printf("�������:");
     printf("\n");
     InOrder(Ta);
     printf("\n");
     printf("�������:");
     printf("\n");
     PostOrder(Ta);
     printf("\n");
	 printf("�ǵݹ��ʼ����Tb����ʽΪ��ȫ��������ʽ��һ�����ֽ���һ���ַ�������0Ϊ��ֹ��\n");
	 Tb=Create_BiTree_NoTraverse();
	 printf("�ǵݹ��������Ϊ��");
	 PreOrder_NoTraaverse(Tb);
	 printf("\n");
	 printf("�ǵݹ��������Ϊ��");
	 InOrder_NoTraaverse(Tb);
	 printf("\n");
	 printf("�ǵݹ�������Ϊ��");
	 PostOrder_NoTraaverse(Tb);
	 printf("\n");
}
