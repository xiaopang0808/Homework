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
	int rear;       //指向队尾的下一个元素
}SqQueue;

//初始化
Status InitQueue(SqQueue &Q){
	Q.base=new int[MAXSIZE];
	if(!Q.base) exit(OVERFLOW);
	Q.front=Q.rear=0;
	return OK;
}

//求长度
int QueueLength(SqQueue Q){
	return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

//入队
Status EnQueue(SqQueue &Q,int e){
	if((Q.rear+1)%MAXSIZE==Q.front) return ERROR;   //队满
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXSIZE;
	return OK;
}

//出队
Status DeQueue(SqQueue &Q, int &e){
	if(Q.front==Q.rear) return ERROR;               //队空
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXSIZE;
	return OK;
}

//取队头元素
int GetHead(SqQueue Q){
	if(Q.front!=Q.rear)
		return Q.base[Q.front];
}



int main(){








}
