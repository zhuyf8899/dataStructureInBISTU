// dfs.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_VEX  30     /*  ��󶥵���  */
typedef int VexType;
typedef int InfoType;
bool  Visited[MAX_VEX] ;
//typedef enum {DG, AG, WDG,WAG} GraphKind ;
typedef struct LinkNode
{
	int adjvex;			// �ڽӵ���ͷ��������е�λ��(�±�)
	InfoType info;		// ��߻���ص���Ϣ, ��Ȩֵ
	struct LinkNode  *nextarc;     // ָ����һ������
}LinkNode;					/*  �������Ͷ���   */
typedef struct VexNode
{
	VexType data;			// ������Ϣ
	int  degree;			//  ����Ķ�, ����ͼ����Ȼ���Ȼ�û�� 
	LinkNode  *firstarc ;    // ָ���һ������
}VexNode;					 /*  ���������Ͷ���   */
typedef struct ArcType
{  
	VexType vex1,vex2;		 /*  ��������������������� */
	InfoType info;			 // ��߻���ص���Ϣ, ��Ȩֵ
}ArcType;					 /*  ����ߵĽṹ����  */
typedef struct
{  
	//GraphKind kind ;       /*  ͼ�������־   */
	int vexnum ;
	VexNode AdjList[MAX_VEX] ;
}ALGraph ;					 /*  ͼ�Ľṹ����   */


ALGraph *Create_Graph(ALGraph * G)
{   //printf("������ͼ�������־��") ;
	//cin>>(G->kind);
	G->vexnum=0 ;       /*  ��ʼ���������  */
	return(G) ; 
}

int  LocateVex(ALGraph *G , VexType *vp) 
{  
	int  k ;
	for (k=0 ; k<G->vexnum ; k++)
		if (G->AdjList[k].data==*vp)  
			return(k) ;
	return(-1) ;     /*  ͼ���޴˶���  */
}

int  AddVertex(ALGraph *G , VexType *vp) 
{  
	int  k ;
	if  (G->vexnum>=MAX_VEX)
	{  
		printf("Vertex Overflow !\n");  
		return(-1); 
	}
	if  (LocateVex(G , vp)!=-1)
	{  
		printf("Vertex has existed !\n");
		return(-1);
	}
	G->AdjList[G->vexnum].data=*vp ;
	G->AdjList[G->vexnum].degree=0 ;
	G->AdjList[G->vexnum].firstarc=NULL ;
	k=++G->vexnum ; 
	return(k) ;  
}

int AddArc(ALGraph *G , ArcType *arc) 
{  
	int k,j;
	LinkNode *p ,*q;
	k=LocateVex(G , &arc->vex1);
	j=LocateVex(G , &arc->vex2);
	if (k==-1||j==-1) 
	{
		printf("Arc��s Vertex do not existed !\n"); 
		return(-1); 
	}
	p=(LinkNode *)malloc(sizeof(LinkNode));
	p->adjvex=arc->vex1;
	p->info=arc->info;
	p->nextarc=NULL;   /*  �ߵ���ʼ���㸳ֵ   */
	q=(LinkNode *)malloc(sizeof(LinkNode));
	q->adjvex=arc->vex2;
	q->info=arc->info;
	q->nextarc=NULL;   /*  �ߵ�ĩβ���㸳ֵ   */
	q->nextarc=G->AdjList[k].firstarc;
	G->AdjList[k].firstarc=q;
	p->nextarc=G->AdjList[j].firstarc;
	G->AdjList[j].firstarc=p;
	
	
	return(1);
}

void DFS(ALGraph *G , int v)
{
	LinkNode  *p ;
	Visited[v]=true;			/*  �÷��ʱ�־�����ʶ���v  */ 
	printf("%d",G->AdjList[v].data);
	p=G->AdjList[v].firstarc;   /*  ����ĵ�һ�����  */
	while (p!=NULL)
	{
		if(!Visited[p->adjvex])
			DFS(G, p->adjvex) ;	/*  ��v��δ���ʹ����ڽӶ�����������������   */
		p=p->nextarc ;
	}   
}

void DFS_traverse_Graph(ALGraph *G)
{
	int v ;
	LinkNode *p;
	for (v=0 ; v<G->vexnum ; v++)
		Visited[v]=false ;    /*  ���ʱ�־��ʼ��  */ 
	p=G->AdjList[v].firstarc ;
	for (v=0 ; v<G->vexnum ; v++)
		if (!Visited[v])
			DFS(G , v);
}
typedef struct Queue
{ 
	int elem[MAX_VEX] ;
	int front,rear ;
}Queue;     /*   ����һ�����б��潫Ҫ���ʶ���  */
void BFS_traverse_Grapg(ALGraph *G) //�ǵݹ��㷨
{  
	int k,v,w;
	LinkNode *p; 
	Queue *Q;
	Q=(Queue *)malloc(sizeof(Queue));
	Q->front=Q->rear=0;					/*  �����ն��в���ʼ��  */
	for (k=0 ; k<G->vexnum ; k++)
		Visited[k]=false;				/*  ���ʱ�־��ʼ��  */
	for (k=0 ; k<G->vexnum ; k++)
	{
		v=G->AdjList[k].data;			/*  �������ͷ����  */
		if (!Visited[v])				/*   v��δ����   */
		{
			Q->elem[++Q->rear]=v;		/*   v���   */
			while (Q->front!=Q->rear )
			{
				w=Q->elem[++Q->front];
				Visited[w]=true;		/*  �÷��ʱ�־  */
				printf("%d",G->AdjList[w].data);     /*  ���ʶ���Ԫ��  */
				p=G->AdjList[w].firstarc;
				while (p!=NULL)
                {  
					if (!Visited[p->adjvex])
					{
						Visited[p->adjvex]=true;
						Q->elem[++Q->rear]=p->adjvex;
					}
                    p=p->nextarc;
                }
			}
		}
	}
}



int _tmain(int argc, _TCHAR* argv[])
{
	ALGraph example;
	Create_Graph(&example);
	for(int i=0;i<5;i++)
	{
		AddVertex(&example,&i);
	}
	/*
	ArcType arc;
	arc.info=1;
	arc.vex1=0;
	arc.vex2=1;
	AddArc(&example,&arc);
	arc.vex1=3;
	arc.vex2=0;
	AddArc(&example,&arc);
	arc.vex1=1;
	arc.vex2=2;
	AddArc(&example,&arc);
	arc.vex1=2;
	arc.vex2=3;
	AddArc(&example,&arc);
	cout<<"��ȱ���:"<<endl;
	DFS_traverse_Graph(&example);
	cout<<endl<<"��ȱ���:"<<endl;
	BFS_traverse_Grapg(&example);
	cout<<endl;
	*/
	ArcType arc;
	arc.info=1;
	arc.vex1=0;
	arc.vex2=2;
	AddArc(&example,&arc);
	arc.vex1=0;
	arc.vex2=1;
	AddArc(&example,&arc);
	arc.vex1=1;
	arc.vex2=4;
	AddArc(&example,&arc);
	arc.vex1=1;
	arc.vex2=3;
	AddArc(&example,&arc);
	cout<<"��ȱ���:"<<endl;
	DFS_traverse_Graph(&example);
	cout<<endl<<"��ȱ���:"<<endl;
	BFS_traverse_Grapg(&example);
	cout<<endl;
	return 0;
}

