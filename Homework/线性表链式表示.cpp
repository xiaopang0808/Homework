#include<bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
using namespace std;
typedef int Status;

//������
typedef struct{
	char num[4];
	char name[8];
	int score;
}Student;

//������ṹ��
typedef struct Lnode{
	Student data;
	struct Lnode *next;     	//ָ����
}Lnode,*LinkList;

//�������ʼ��
Status InitList(LinkList &L){
 	L=new Lnode;
	L->next=NULL;
	return OK;
}

//�ж������Ƿ�Ϊ��
Status ListEmpty(LinkList L){
	if(L->next) return FALSE;    //�ǿ�
	else return OK;             //��
}

//�����������
Status DestroyList(LinkList &L){
	Lnode *p;
	while(L){
		p=L;
		L=L->next;
		delete p;
	}
	return OK;
}

//�������
Status ClearList(LinkList &L){
	Lnode *p,*q;
	p=L->next;
	while(p){
		q=p->next;
		delete p;
		p=q;
	}
	L->next=NULL;
	return OK;
}

//������ı�
int ListLength(LinkList L){
	Lnode *p;
	p=L->next;
	int cnt=0;
	while(p){
		cnt++;
		p=p->next;
	}
	return cnt;
}

//������ȡֵ
Status GetElem(LinkList L,int i,Student &e){
	Lnode *p;
	p=L->next;
	int j=1;
	while(p&&j<i){
		p=p->next;
		j++;
	}
	if(!p||j>i) return ERROR;
	e=p->data;
	return OK;
}

//��ֵ����
Lnode *locateElem(LinkList L,int e){
	Lnode *p;
	p=L->next;
	while(p&&p->data.score!=e)
		p=p->next;
	return p;
}

//����
Status ListInsert(LinkList &L,int i,Student e){
	Lnode *p,*s;p=L;int j=0;
	while(p&&j<i-1){
		p=p->next;
		j++;
	}
	if(!p||j>i-1)return ERROR;
	s->data=e;
	s->next=p->next;
	p->next=s;
	return OK;
}

//ɾ��
Status ListDelete(LinkList &L,int i,Student e){
	Lnode *p,*s;p=L;
	int j=0;
	while(p&&j<i-1){
		p=p->next;
	}
	if(!p->next||j>i-1)return ERROR;
	s=p->next;
	p->next=s->next;
	e=s->data;
	delete s;
	return OK;
	
}

//ͷ�巨��������
void CreateList_H(LinkList &L,int n){
	L->next=NULL;
	for(int i=0;i<n;i++){
		Lnode *p;
//		cin>>p->data;       //����Ԫ��ֵ
		p->next=L->next;
		L->next=p;
	}
}

//β�巨
void CreateList_R(LinkList &L,int n){
	L->next=NULL;
	Lnode *r;r=L;
	for(int i=0;i<n;i++){
		Lnode *p;
//		cin>>p->data;
		p->next=NULL;
		r->next=p;
		r=p;
	}
}


int main(){

}
