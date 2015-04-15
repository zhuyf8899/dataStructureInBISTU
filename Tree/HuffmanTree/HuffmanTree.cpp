// HuffmanTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#define M 10
#define MAX 100

typedef  struct
{
    int data;
    int pa,lc,rc;
}JD;

void huffman(int n,int w[],JD t[])
{  int i,j,k,x1,x2,m1,m2;
   for(i=1;i<(2*n);i++)
   {  
		t[i].pa=t[i].lc=t[i].rc=0;
		if(i<=n)
			t[i].data=w[i-1];
		else
			t[i].data=0;
   }
   for(i=1;i<n;i++)
   {  
		m1=m2=MAX;
		x1=x2=0;
      for(j=1;j<(n+i);j++)
      {  
		  if((t[j].data<m1)&&(t[j].pa==0))
     {  m2=m1;  x2=x1;
        m1=t[j].data;  x1=j;
     }
     else if((t[j].data<m2)&&(t[j].pa==0))
     {  m2=t[j].data; x2=j; }
      }
      k=n+i;
      t[x1].pa=t[x2].pa=k;
      t[k].data=m1+m2;
      t[k].lc=x1;
      t[k].rc=x2;
   }
}

void main()
{  int i,j,n=4;
   static int w[]={7,5,2,4};
   JD t[M];
   huffman(n,w,t);
   for(i=1;i<=2*n-1;i++)
      printf("%d ,%d ,%d ,%d \n",t[i].lc,t[i].data,t[i].rc,t[i].pa);
   printf("\n\n");
   getchar();
}