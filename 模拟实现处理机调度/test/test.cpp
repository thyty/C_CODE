#include <windows.h>
#include<stdio.h>
#include<stdlib.h>
#define ok 1
#define y 1
struct PCB{
	char name;
	int arrtime;
	int startime;
	int needtime;
	int rt;
	int finishtime;
	int stime;
	float astime;
	int state;
	int state2;
};
typedef struct ready{
PCB data;
struct ready *next;
}ready,*linklist;
int create(linklist &L,int n)           //利用尾插法创建进程
{
 linklist p,r;
 int i;
 L=(linklist)malloc(sizeof(ready));
 L->next=NULL;
 r=L;
 if(n<=0)
 {
 printf("请输入正整数！\n");
 return ERROR;
 }
 printf("请依次输入进程名、到达时间、服务时间\n");
 for(i=0;i<n;i++)
 {
 p=(linklist)malloc(sizeof(ready));
 scanf("%s",&(p->data.name));
 scanf("%d",&(p->data.arrtime));
 scanf("%d",&(p->data.needtime));
 p->data.rt=p->data.needtime;
 p->data.state=1;
 p->data.state2=1;
 r->next=p;
 r=p;
 }
 r->next=NULL;
 return ok;
}
void renew(linklist &L)
{
linklist p;
 p=L->next;
 while(p)
 {
 p->data.state =1;
 p->data.state2=1;
 p->data.rt=p->data.needtime;
 p=p->next;
 }
}
void sort(linklist &L)  
{
 linklist p,q;
 PCB temp;
 p=L->next;
 q=L->next;
 while((p!=NULL)&&(p->next!=NULL))      
 {
 for(p=L->next;p->next!=NULL;p=p->next)
 {
 for(q=L->next;q->next!=NULL;q=q->next)
 {
 if(q->data.arrtime>q->next->data.arrtime)
 {
 temp=q->data;
 q->data=q->next->data;
 q->next->data=temp;
 }
 }
 }
 }
}
void sort2(linklist &L)  
{
 linklist p,q;
 PCB temp;
 p=L->next;
 q=L->next;
 while((p!=NULL)&&(p->next!=NULL))      
 {
 for(p=L->next;p->next!=NULL;p=p->next)
 {
 for(q=L->next;q->next!=NULL;q=q->next)
 {
	 if(q->data.needtime>q->next->data.needtime)
 {
 temp=q->data;
 q->data=q->next->data;
 q->next->data=temp;
 }
 }
 }
 }
}
void print(int time,linklist &L)
{
 linklist p;
 p=L->next;
 if(!p)
	 printf("error");
 
	while(p)
 {
  if(p->data.arrtime<=time&&p->data .state==1)
   printf("%c ",p->data.name);
  p=p->next;
	}
	printf("\n");
}
int work(linklist &L,linklist p,int time)
{
	p->data.state=0;
	p->data.finishtime=time+p->data.needtime;
	p->data.startime=time;
	p->data.stime=p->data.finishtime-p->data.arrtime;
	p->data.astime=float(p->data.needtime)/p->data.stime;
	printf("当前时间%d 正在执行的进程为:%c\n",time,p->data.name);
	printf("此时就绪队列为:");
    print(time,L);
	time=p->data.finishtime;
	return time;
}
void SJP(linklist &L,int num)
{
 renew(L);
 int i=0;
 int time=0;
 linklist p;
 p=L->next;
 while (i<num)
 {
  p=L->next; 
  while(p&&(p->data.arrtime>time||p->data.state==0))
	 { p=p->next;}
  while(p&&(p->data.arrtime<=time)&&p->data.state==1)
 { 
 time=work(L,p,time);
 i+=1;
  }
  if(!p)
	 {time=time+1;}
  printf("%d,%d",num,i);
 }
}
void FCFS(linklist &L)
{
 renew(L);
 linklist p;
 p=L->next;
 int time=p->data.arrtime;
 while(p&&(p->data.arrtime<=time))
 { 
 time=work(L,p,time);
 p=p->next;
 while(p&&p->data.arrtime>time)
	 {time+=1;}
 }
 printf("\n");
}
void show(linklist &L)           //输出当前队列中的进程的信息
{
 linklist p;
 p=L->next;
 if(!p)
 {
 printf("为空！\n");
 printf("error");
 }
 while(p)
 {
 printf("进程名 到达时间 服务时间 \n");
 printf("%c\t %d\t  %d\n",p->data.name,p->data.arrtime,p->data.needtime);
 p=p->next;
 }
}
void sort3(linklist &L)  
{
 linklist p,q;
 PCB temp;
 p=L->next;
 q=L->next;
 while((p!=NULL)&&(p->next!=NULL))      
 {
 for(p=L->next;p->next!=NULL;p=p->next)
 {
 for(q=L->next;q->next!=NULL;q=q->next)
 {
	 if(q->data.rt>q->next->data.rt)
 {
 temp=q->data;
 q->data=q->next->data;
 q->next->data=temp;
 }
 }
 }
 }
}
void print2(int time,linklist &L)
{
 linklist p;
 p=L->next;
 if(!p)
	 printf("error");
	while(p)
 {
  if(p->data.arrtime<=time&&p->data .state==1&&p->data.state2==1)
   printf("%c ",p->data.name);
  p=p->next;
	}
	printf("\n");

}
int work3(linklist &L,linklist p,int i,int time)
{
  p->data.state2=0;
  if (p->data.rt==p->data.needtime)
    p->data.startime=time;
    p->data.rt-=1;
	printf("当前时间%d 正在执行的进程为:%c\n",time,p->data.name);
	printf("此时就绪队列为:");
    print2(time,L);
  time+=1;
  if (p->data.rt==0)
	{
  p->data.state=0;
	p->data.finishtime=time;
	p->data.stime=p->data.finishtime-p->data.arrtime;
	p->data.astime=float(p->data.needtime)/p->data.stime;
  i+=1;
  }
  else
    p->data.state2=1;
	return i;
}
void QSJP(linklist &L,int num)
{
 renew(L);
 int i=0;
 int time=0;
 linklist p;
 p=L->next;
 while (i<num)
 {
  p=L->next;
  while(p&&(p->data.arrtime>time||p->data.state==0))
	 { p=p->next;}
  while(p&&(p->data.arrtime<=time)&&p->data.state==1)
 { 
 i=work3(L,p,i,time);
 sort(L);
 sort3(L);
 p=L->next;
 time+=1;
  }
  if(!p)
	 {time=time+1;}
 }
}
void showlist(linklist &L,int n)
{
 float ast=0;
 float aast=0;
 linklist p;
 p=L->next;
 printf("作业名        到达时间        服务时间        开始时间        完成时间        周转时间         带权周转时间\n");
 while(p)
 {
	 printf("%c\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\t\t\n",p->data.name,p->data.arrtime,p->data.needtime,p->data.startime,p->data.finishtime,p->data.stime,p->data.astime);
	 ast+=p->data.stime;
	 aast+=p->data.astime;
 p=p->next;
 }
 printf("平均周转时间为:%.2f\t\t",float(ast/n));
  printf("平均带权周转时间为:%.2f\n",aast/n);
}
void prt()
{
 printf("-------------------进程调度------------------\n");
 printf("                1.   创建进程                \n");
 printf("                2. 显示进程信息              \n");
 printf("                3.先来先服务算法             \n");
 printf("                4.非抢占式短作业优先算法             \n");
 printf("                5.最短剩余时间优先算法             \n");
 printf("                6.退出                       \n");
 printf("---------------------------------------------\n");
}
void main()
{
 linklist L;
 int x;
int n=0;
 prt();
 while(1)
 {
 printf("Choice:\t");
 scanf("%d",&x);
 switch(x)
 {
 case 1:
  system("cls");
  printf("请输入进程的个数：(必须为整数!!!)");
  scanf("%d",&n);
  printf("%d",n);
  create(L,n);
  sort(L);
  system("cls");
   prt();
  break;
 case 2:
 show(L);
 break;
 case 3:
 FCFS(L);
 showlist(L,n);
 break;
 case 4:
sort2(L);
SJP(L,n);
showlist(L,n);
 break;
 case 5:
sort2(L);
QSJP(L,n);
showlist(L,n);
 break;
 case 6:
 exit(0);
 }
 }
}



