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

typedef struct{
	int *base;
	int front;
	int rear;       //ָ���β����һ��Ԫ��
}SqQueue;

//��ʼ��
Status InitQueue(SqQueue &Q){
	Q.base=new int[MAXSIZE];
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

//�󳤶�
int QueueLength(SqQueue Q){
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

//���
Status EnQueue(SqQueue &Q,int e){
	if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;   //����
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}

//����
Status DeQueue(SqQueue &Q, int &e){
	if(Q.front==Q.rear) return ERROR;               //�ӿ�
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}

//ȡ��ͷԪ��
int GetHead(SqQueue Q){
	if(Q.front!=Q.rear)
		return Q.base[Q.front];
}



int main(){








}
