// dfs.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAX_VEX  30     /*  最大顶点数  */
typedef int VexType;
typedef int InfoType;
bool  Visited[MAX_VEX] ;
//typedef enum {DG, AG, WDG,WAG} GraphKind ;
typedef struct LinkNode
{
	int adjvex;			// 邻接点在头结点数组中的位置(下标)
	InfoType info;		// 与边或弧相关的信息, 如权值
	struct LinkNode  *nextarc;     // 指向下一个表结点
}LinkNode;					/*  表结点类型定义   */
typedef struct VexNode
{
	VexType data;			// 顶点信息
	int  degree;			//  顶点的度, 有向图是入度或出度或没有 
	LinkNode  *firstarc ;    // 指向第一个表结点
}VexNode;					 /*  顶点结点类型定义   */
typedef struct ArcType
{  
	VexType vex1,vex2;		 /*  弧或边所依附的两个顶点 */
	InfoType info;			 // 与边或弧相关的信息, 如权值
}ArcType;					 /*  弧或边的结构定义  */
typedef struct
{  
	//GraphKind kind ;       /*  图的种类标志   */
	int vexnum ;
	VexNode AdjList[MAX_VEX] ;
}ALGraph ;					 /*  图的结构定义   */


ALGraph *Create_Graph(ALGraph * G)
{   //printf("请输入图的种类标志：") ;
	//cin>>(G->kind);
	G->vexnum=0 ;       /*  初始化顶点个数  */
	return(G) ; 
}

int  LocateVex(ALGraph *G , VexType *vp) 
{  
	int  k ;
	for (k=0 ; k<G->vexnum ; k++)
		if (G->AdjList[k].data==*vp)  
			return(k) ;
	return(-1) ;     /*  图中无此顶点  */
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
		printf("Arc’s Vertex do not existed !\n"); 
		return(-1); 
	}
	p=(LinkNode *)malloc(sizeof(LinkNode));
	p->adjvex=arc->vex1;
	p->info=arc->info;
	p->nextarc=NULL;   /*  边的起始表结点赋值   */
	q=(LinkNode *)malloc(sizeof(LinkNode));
	q->adjvex=arc->vex2;
	q->info=arc->info;
	q->nextarc=NULL;   /*  边的末尾表结点赋值   */
	q->nextarc=G->AdjList[k].firstarc;
	G->AdjList[k].firstarc=q;
	p->nextarc=G->AdjList[j].firstarc;
	G->AdjList[j].firstarc=p;
	
	
	return(1);
}

void DFS(ALGraph *G , int v)
{
	LinkNode  *p ;
	Visited[v]=true;			/*  置访问标志，访问顶点v  */ 
	printf("%d",G->AdjList[v].data);
	p=G->AdjList[v].firstarc;   /*  链表的第一个结点  */
	while (p!=NULL)
	{
		if(!Visited[p->adjvex])
			DFS(G, p->adjvex) ;	/*  从v的未访问过的邻接顶点出发深度优先搜索   */
		p=p->nextarc ;
	}   
}

void DFS_traverse_Graph(ALGraph *G)
{
	int v ;
	LinkNode *p;
	for (v=0 ; v<G->vexnum ; v++)
		Visited[v]=false ;    /*  访问标志初始化  */ 
	p=G->AdjList[v].firstarc ;
	for (v=0 ; v<G->vexnum ; v++)
		if (!Visited[v])
			DFS(G , v);
}
typedef struct Queue
{ 
	int elem[MAX_VEX] ;
	int front,rear ;
}Queue;     /*   定义一个队列保存将要访问顶点  */
void BFS_traverse_Grapg(ALGraph *G) //非递归算法
{  
	int k,v,w;
	LinkNode *p; 
	Queue *Q;
	Q=(Queue *)malloc(sizeof(Queue));
	Q->front=Q->rear=0;					/*  建立空队列并初始化  */
	for (k=0 ; k<G->vexnum ; k++)
		Visited[k]=false;				/*  访问标志初始化  */
	for (k=0 ; k<G->vexnum ; k++)
	{
		v=G->AdjList[k].data;			/*  单链表的头顶点  */
		if (!Visited[v])				/*   v尚未访问   */
		{
			Q->elem[++Q->rear]=v;		/*   v入队   */
			while (Q->front!=Q->rear )
			{
				w=Q->elem[++Q->front];
				Visited[w]=true;		/*  置访问标志  */
				printf("%d",G->AdjList[w].data);     /*  访问队首元素  */
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
	cout<<"深度遍历:"<<endl;
	DFS_traverse_Graph(&example);
	cout<<endl<<"广度遍历:"<<endl;
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
	cout<<"深度遍历:"<<endl;
	DFS_traverse_Graph(&example);
	cout<<endl<<"广度遍历:"<<endl;
	BFS_traverse_Grapg(&example);
	cout<<endl;
	return 0;
}

