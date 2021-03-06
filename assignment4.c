//BT20CSE002 Maneesh
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define size 100
// using linked list to implement allocate node
typedef struct allocate
{
	char name[size];
	int address;
	int memory;
	struct allocate *next;
}allocate_n;
// using linked list to implement free node
typedef struct free
{	int start_address;
	int end_address;
	int memory;
	struct free *next;
}free_n;
//forward declaration
allocate_n* create_allocate(int a,int m,char c[size]);
allocate_n* inserta(allocate_n* al,int a,int m,char* c);
free_n* insertf(free_n* f,int s_a,int e_a,int m);
free_n* insertf(free_n* f,int s_a,int e_a,int m);
allocate_n* freeup(allocate_n *aptr,free_n **fptr,char f[10]);
void printa(allocate_n *lptr);
void printfr(free_n *lptr);
void mergefree(free_n* f);
void remove_free(free_n* f,free_n** h);
int main()
{
	allocate_n *a;
	free_n *f;
	int choice;
	char A[] = "a";
	printf(" 1000 UNITS OF HEAP MEMORY ARE ASSUMED  \n");

	a=NULL;
	f=NULL;
	a=inserta(a,0,100,A);
	f=insertf(f,600,1000,400);
	f=insertf(f,201,401,200);
	f=insertf(f,100,200,100);
	do
	{	printf("What procedure do you wish to carry out? \n");
		printf("1.Memory allocation \n");
		printf("2.Free up the memory \n");
		printf("3.Show the memory that has been allotted\n");
		printf("4.Show the free memory\n");
		printf("5.Exit \n");
		printf("Enter the number associated with the procedure you wish to carry out\n");
		
		scanf("%d",&choice);
		if(choice==1)
		{ 
			int memory,add;
		    char name[10];
		    printf("How much memory do you wish to allocate, as well as the addresses and names?\n");
			scanf("%d %d ",&memory,&add);
			scanf("%s",name);
			a = inserta(a,add,memory,name);
			printf("allocation completed\n");
		}
	    if(choice==2)
		{
			char free_name[10];
		    printa(a);
			printf("enter the name of the allocated space you want to free\n");
			scanf("%s",free_name);
			a = freeup(a,&f,free_name);
			printf("freeing up is completed\n");
		}
		if(choice==3)
		{
			printa(a);
		}
		if(choice==4)
		{
			mergefree(f);
			printfr(f);
		}

	}while(choice!=5);
	    return 0;
}
//creating allocated list
allocate_n* create_allocate(int a,int m,char c[size])
{
	allocate_n *n=(allocate_n*)malloc(sizeof(allocate_n));
	strcpy(n->name,c);
	n->address=a;
	n->memory=m;
	n->next=NULL;
	return n;
}
//insert at the start of the allocated list
allocate_n* inserta(allocate_n* al,int a,int m,char* c)
{
	allocate_n *i=create_allocate(a,m,c);
	i->next=al;
	al=i;
	return al;
}
//creating free list
free_n* create_free(int s_a,int e_a,int m)
{
	free_n* n=(free_n*)malloc(sizeof(free_n));
	n->start_address=s_a;
	n->end_address=e_a;
	n->memory=m;
	n->next=NULL;
	return n;
}
//insert at the start of the free list
free_n* insertf(free_n* f,int s_a,int e_a,int m)
{
	free_n *i=create_free(s_a,e_a,m);
    i->next=f;
	f=i;
	return f;
}
//free up memory 
allocate_n* freeup(allocate_n *a,free_n **f,char c[10])
{
	allocate_n *p,*s,*prev,*n;
	free_n *q,*o;
	int start_address,end_address,memory_alloc,found = 0;
	q = *f;
	p = a;
	prev = NULL;
	while((p != NULL)&&(found == 0))
	{
		if(!strcmp(p->name,c))
		{
			start_address = p->address;
			end_address = (p->address) + (p->memory);
			memory_alloc = p->memory;
			found = 1;
			if(p == a)
			{
				n = p;
				p = p->next;
				free(n);
				a = p;
			}	
			else
			{
				prev->next = p->next;
				free(p);
			}
		}
		else
		{	prev = p;
			p = p->next;
		}
	}
	found = 0;
	while((q != NULL)&&(found == 0))
	{
		if(q->start_address == end_address)
		{
			q->start_address = start_address;
			q->memory = (q->memory) + (memory_alloc);
			found = 1;
		}
		else if(q->end_address == start_address)
		{
			q->end_address = end_address;
			q->memory = (q->memory) + (memory_alloc);
			found = 1;
		}
		q = q->next;
	}

	if(found == 0)
	{
		*f = insertf(*f,start_address,end_address,memory_alloc);
	}
	return a;
}		
//allocated list
void printa(allocate_n *a)
{	printf("This is the allocated list:\n");
	printf("Name\taddr\tmemory\n");
	while(a != NULL)
	{	printf("%s\t",a->name);
		printf("%d\t",a->address);
		printf("%d\t",a->memory);
		a=a->next;
		printf("\n");
	}
}
//free list 
void printfr(free_n *lptr)
{	printf("This is the FreeList:\n");
	printf("start_addr\tEnd_addr\tmemory\n");
	while(lptr != NULL)
	{
		printf("%d\t",lptr->start_address);
		printf("%d\t",lptr->end_address);
		printf("%d\t",lptr->memory);
		lptr = lptr->next;
		printf("\n");
	}
}
//merge function 
void mergefree(free_n* f)
{
	free_n* temp=f;
	while(temp!=NULL)
	{
		free_n* nextnode=temp->next;
		while(nextnode!=NULL)
		{
			int x=abs((temp->end_address)-(nextnode->start_address));
			if(x==1)
			{
				temp->memory=temp->memory+nextnode->memory;
				remove_free(nextnode,&temp);
			}
			nextnode=nextnode->next;
		}
		temp=temp->next;
	}
}
void remove_free(free_n* f,free_n** h)
{
	if(*h==NULL)
	{
		return;
	}
	free_n* temp=*h;
	free_n* prev=NULL;
	while(temp!=f)
	{
		prev=temp;
		temp=temp->next;
	}
	if(prev!=NULL)
	{
		prev->next=temp->next;
	}
	else
	{
		*h=temp->next;
	}
}