#include<bits/stdc++.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
using namespace std;
typedef int Status;

//数据域
typedef struct{
	char num[4];
	char name[8];
	int score;
}Student;

//链表结点结构体
typedef struct Lnode{
	Student data;
	struct Lnode *next;     	//指针域
}Lnode,*LinkList;

//单链表初始化
Status InitList(LinkList &L){
 	L=new Lnode;
	L->next=NULL;
	return OK;
}

//判断链表是否为空
Status ListEmpty(LinkList L){
	if(L->next) return FALSE;    //非空
	else return OK;             //空
}

//单链表的销毁
Status DestroyList(LinkList &L){
	Lnode *p;
	while(L){
		p=L;
		L=L->next;
		delete p;
	}
	return OK;
}

//清空链表
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

//求单链表的表长
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

//单链表取值
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

//按值查找
Lnode *locateElem(LinkList L,int e){
	Lnode *p;
	p=L->next;
	while(p&&p->data.score!=e)
		p=p->next;
	return p;
}

//插入
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

//删除
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

//头插法创建链表
void CreateList_H(LinkList &L,int n){
	L->next=NULL;
	for(int i=0;i<n;i++){
		Lnode *p;
//		cin>>p->data;       //输入元素值
		p->next=L->next;
		L->next=p;
	}
}

//尾插法
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
