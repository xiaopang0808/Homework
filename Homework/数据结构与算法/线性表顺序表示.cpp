#include<bits/stdc++.h>
#define MAX_LENGTH 1000
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;



//����˳���ṹ��
typedef struct{
//	int data[MAX_LENGTH];   //��̬�����ʾ
	int *data;              //��̬�����ʾ
	int length;
}SqList;


//��ʼ��˳���
Status Initlist(SqList &L){
	L.length=0;
//	L.data=(int*)malloc(sizeof(int)*MAX_LENGTH);
	L.data=new int[MAX_LENGTH];
	if(!L.data) exit(OVERFLOW);    //�洢����ʧ��,�˳�����
	return OK;
}

//�������Ա�
void DestroyList(SqList &L){
	if(L.data) delete L.data;       //�ͷŴ洢�ռ�
}

//������Ա�
void ClearList(SqList &L){
	L.length=0;     //�߼����
}

//�����Ա���
int GetLength(SqList &L){
	return L.length;
}

//�ж����Ա��Ƿ�Ϊ��
Status IsEmpty(SqList &L){
	if(L.length==0) return TRUE;
	else return FALSE;
}

//��ȡ���Ա��е�Ԫ��
Status GetElem(SqList &L,int i,int &e){
	if(i<1||i>L.length) return ERROR;   //�ж�iֵ�Ƿ����
	e=L.data[i-1];
	return OK;
}

//����Ԫ��
int LocateElem(SqList L,int e){
	for(int i=0;i<L.length;i++)
		if(L.data[i]==e) return i+1;    //�������
	return 0;   //����ʧ��
}

//����Ԫ��
Status ListInsert(SqList &L,int i,int e){
	if(i<1||i>L.length+1||L.length==MAX_LENGTH) //�жϺϷ���
		return ERROR;
	for(int j=L.length-1;j>=i-1;j--)    //����λ�ü�֮���Ԫ�غ���
		L.data[j+1]=L.data[j];
	L.data[i]=e;
	L.length++;
	return OK;
	
}

//ɾ��Ԫ��
Status ListDelete(SqList &L, int i){
	if(i<1||i>L.length)
		return ERROR;
	for(int j=i;j<=L.length-1;j++)
		L.data[j-1]=L.data[j];
	L.length--;
	return OK;
}


int main(){

}
