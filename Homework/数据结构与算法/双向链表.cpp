#include<bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
using namespace std;
typedef int Status;

typedef struct DuLnode{
	int data;
	struct DuLnode *prior, *next;
}DuLnode,*DuLinkList;

Status ListInsert(DuLinkList &L, int i, int e){
	DuLnode *s,*p;p=L;
	int j=0;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1) return ERROR;
	s->data=e;
	s->next=p->next;
	s->prior=p->next->prior;
	p->next=s;
	s->next->prior=s;
	return OK;
}

Status ListDelete(DuLinkList &L,int i){
	int j=0;
	DuLnode *p;p=L;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i) return ERROR;
	p->prior->next=p->next;
	p->next->prior=p->prior;
	delete p;
	return OK;
}





int main(){

	return 0;
}
