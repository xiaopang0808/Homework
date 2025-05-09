

typedef struct{
	int *base;      //栈底指针
	int *top;       //栈顶指针
	int stacksize;  //可用最大容量
}SqStack;

//初始化
Status InitStack(SqStack &S){
	S.base=new int [MAXSIZE];
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=MAXSIZE;
	return OK;
}

//判断是否为空
Status StackEmpty(SqStack S){
	if(S.top==S.base) return TRUE;
	else return FALSE;
}

//求长度
int StackLength(SqStack S){
	return S.top-S.base;
}

//清空栈
void ClearStack(SqStack &S){
	S.top=S.base;
}

//销毁栈
Status DestroyStack(SqStack &S){
	if(S.base){
		delete S.base;      //释放base指针指向的内存，但base仍指向原地址
		S.stacksize=0;
		S.base=S.top=NULL;  //将指针置空
	}
	return OK;
}

//入栈
Status Push(SqStack &S, int e){
	if(S.top-S.base==S.stacksize)
		return ERROR;           //栈满
	*S.top++=e;
	return OK;
}

//出栈
Status Pop(SqStack &S,int &e){
	if(StackEmpty(S)) return ERROR;
	e=*--S.top;
	return OK;
}



int main(){










	return 0;
}
