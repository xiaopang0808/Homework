#include<bits/stdc++.h>
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
using namespace std;

typedef struct Qnode{
	int data;
	struct Qnode *next;
}Qnode,*QueuePtr;

typedef struct{
	QueuePtr front;     //头指针，指向头结点
	QueuePtr rear;      //尾指针，指向队尾
}LinkQueue;

//初始化
Status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=new Qnode;
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

//销毁
Status DestroyQueue(LinkQueue &Q){
	while(Q.front){
		QueuePtr p;
		p=Q.front->next;
		delete Q.front;
		Q.front=p;
	}
	return OK;
}

//入队
Status EnQueue(LinkQueue &Q,int e){
	QueuePtr p;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}

//求队首元素
Status GetHead(LinkQueue Q,int &e){
	if(Q.front==Q.rear) return ERROR;
	e=Q.front->next->data;
	return OK;
}

//出队
Status DeQueue(LinkQueue &Q,int &e){
	if(Q.front==Q.rear) return ERROR;
	QueuePtr p;
	p=Q.front->next;        			//指向头结点指向的队首元素
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;       //若队尾元素出队，将为指针指向头结点
	delete p;
	return OK;

}





int main(){






}
