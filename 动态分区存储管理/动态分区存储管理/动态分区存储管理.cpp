#include<stdio.h>
#include<stdlib.h>
struct freelink
{
	int len;
	int address;
	struct freelink* next;
};
struct busylink {
	char name;
	int len;
	int address;
	struct busylink* next;
};
struct freelink* free_head = NULL;         
struct busylink* busy_head = NULL;                    
struct busylink* busy_tail = NULL;   
void start(){     /*��ʼ��*/
	int a,b;
	printf("������ϵͳ�����ڴ�:");
	scanf("%d",&a);
	printf("���������ϵͳռ��ϵͳ���ڴ�:");
	scanf("%d",&b);
	system("cls");
	free_head = (struct freelink*)malloc(sizeof(struct freelink));         
	busy_head =busy_tail=(struct busylink*)malloc(sizeof(struct busylink));
	struct freelink* p=(struct freelink*)malloc(sizeof(struct freelink));
	p->address=b;                                                              /*����ϵͳռ���ڴ�Ϊ64k*/
	p->len=a-b;                                                               /*���ڴ�Ϊ640k*/ 
	p->next=NULL;
	free_head->next=p;
}
void past(int time){
	printf("������%d��\n",time);
}
void  requireMemo(char  name, int  require)
{
	struct freelink * w, * u, * v;
	struct busylink *p;
	if (free_head->next->len >= require)
	{
		p = (struct busylink*)malloc(sizeof(struct busylink));
		p->name = name;
		p->address = free_head->next->address;
		p->len = require;
		p->next = NULL;
		busy_tail->next = p;
		busy_tail = p;
	}
	else
		printf("Can't allocate");
	w = free_head->next;
	free_head->next = w->next;
	if (w->len == require)
	{
		free(w);
	}
	else
	{
		w->address = w->address + require;
		w->len = w->len - require;
	u = free_head;
	v = free_head->next;
	}
	while ((v != NULL) && (v->len > w->len))
	{
		u = v;
		v = v->next;
	}
	u->next = w;
	w->next = v;
}
void  printfreelink() 
{
	struct freelink * p;
	p = (struct freelink*)malloc(sizeof(struct freelink));
	p = free_head->next;
	if (p==NULL)
		printf("�޿�����");
    int i=0;
	while (p != NULL)
	{
		
		printf("��%d���ڴ����ʼ��ַΪ%5d\t�ڴ�Ĵ�С%5d:\n",++i,p->address, p->len);
		p = p->next;
	}
}
void printbusylink(){
	struct busylink*head2 = busy_head->next;
	if (!head2)
		printf("û����ҵռ���ڴ�\n");
	while (head2){
		printf("%c��ҵռ���ڴ泤��Ϊ%dk,��ʼ��ַΪ%d\n", head2->name, head2->len, head2->address);
		head2 = head2->next;
	}
	printf("\n");
}
void freeMemo(char name){
	struct busylink*q = busy_head;
	struct busylink*p = busy_head->next;
	while (p != NULL&&p->name != name){
		q = p;
		p = p->next;
	}
	if (p){
		if (p == busy_tail)
			busy_tail = q;
		q->next = p->next;
		int len = p->len;
		int adress = p->address;
		free(p);
		struct freelink*w = (struct freelink*)malloc(sizeof(struct freelink));
		w->len = len;
		w->address = adress;
		struct freelink*u = free_head;
		struct freelink*v = free_head->next;
		while (v != NULL&&v->len > len){
			u = v;
			v = v->next;
		}
		u->next = w;
		w->next = v;
	}
	else
		printf("%c is not exist\n", name);
}
void main()
{    
	 int t1=1,t2=2,t3=3,t4=4;
	 start();
	 past(t1);
     requireMemo('A',8);
     requireMemo('B',16); 
     requireMemo('C',64);
     requireMemo('D',124);
	 printfreelink();
	 printbusylink();
     past(t2);
     freeMemo('C');
     printfreelink();
     printbusylink();
     past(t3);
     requireMemo('E',50);
     printfreelink();
     printbusylink();
     past(t4);
     freeMemo('D' );
     printfreelink();
     printbusylink();
}