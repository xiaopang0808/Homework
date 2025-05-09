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

typedef struct StackNode{
	int data;
	struct StackNode *next;
}StackNode,*LinkStack;

//初始化
void InitStack(LinkStack &S){
	S=NULL;
}

//判断是否为空
Status StackEmpty(LinkStack S){
	if(S==NULL) return TRUE;
	else return FALSE;
}

//入栈
Status Push(LinkStack &S, int e){
	StackNode *p;
	p->data=e;
	p->next=S;
	S=p;
	return OK;
}

//出栈
Status Pop(LinkStack &S,int &e){
	if(S==NULL)return ERROR;
	StackNode *p;
	e=p->data;
	p=S;
	S=S->next;
	delete p;
	return OK;
}

//取栈顶元素
int GetTop(LinkStack S){
	if(S!=NULL) return S->data;
}



int main(){







	return 0;;
}
