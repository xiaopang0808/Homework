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
	QueuePtr front;     //ͷָ�룬ָ��ͷ���
	QueuePtr rear;      //βָ�룬ָ���β
}LinkQueue;

//��ʼ��
Status InitQueue(LinkQueue &Q){
	Q.front=Q.rear=new Qnode;
	if(!Q.front) exit(OVERFLOW);
	Q.front->next=NULL;
	return OK;
}

//����
Status DestroyQueue(LinkQueue &Q){
	while(Q.front){
		QueuePtr p;
		p=Q.front->next;
		delete Q.front;
		Q.front=p;
	}
	return OK;
}

//���
Status EnQueue(LinkQueue &Q,int e){
	QueuePtr p;
	p->data=e;
	p->next=NULL;
	Q.rear->next=p;
	Q.rear=p;
	return OK;
}

//�����Ԫ��
Status GetHead(LinkQueue Q,int &e){
	if(Q.front==Q.rear) return ERROR;
	e=Q.front->next->data;
	return OK;
}

//����
Status DeQueue(LinkQueue &Q,int &e){
	if(Q.front==Q.rear) return ERROR;
	QueuePtr p;
	p=Q.front->next;        			//ָ��ͷ���ָ��Ķ���Ԫ��
	e=p->data;
	Q.front->next=p->next;
	if(Q.rear==p) Q.rear=Q.front;       //����βԪ�س��ӣ���Ϊָ��ָ��ͷ���
	delete p;
	return OK;

}





int main(){






}
