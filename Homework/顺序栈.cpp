

typedef struct{
	int *base;      //ջ��ָ��
	int *top;       //ջ��ָ��
	int stacksize;  //�����������
}SqStack;

//��ʼ��
Status InitStack(SqStack &S){
	S.base=new int [MAXSIZE];
	if(!S.base) exit(OVERFLOW);
	S.top=S.base;
	S.stacksize=MAXSIZE;
	return OK;
}

//�ж��Ƿ�Ϊ��
Status StackEmpty(SqStack S){
	if(S.top==S.base) return TRUE;
	else return FALSE;
}

//�󳤶�
int StackLength(SqStack S){
	return S.top-S.base;
}

//���ջ
void ClearStack(SqStack &S){
	S.top=S.base;
}

//����ջ
Status DestroyStack(SqStack &S){
	if(S.base){
		delete S.base;      //�ͷ�baseָ��ָ����ڴ棬��base��ָ��ԭ��ַ
		S.stacksize=0;
		S.base=S.top=NULL;  //��ָ���ÿ�
	}
	return OK;
}

//��ջ
Status Push(SqStack &S, int e){
	if(S.top-S.base==S.stacksize)
		return ERROR;           //ջ��
	*S.top++=e;
	return OK;
}

//��ջ
Status Pop(SqStack &S,int &e){
	if(StackEmpty(S)) return ERROR;
	e=*--S.top;
	return OK;
}



int main(){










	return 0;
}
