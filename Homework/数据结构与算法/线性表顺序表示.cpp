#include<bits/stdc++.h>
#define MAX_LENGTH 1000
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;



//定义顺序表结构体
typedef struct{
//	int data[MAX_LENGTH];   //静态数组表示
	int *data;              //动态数组表示
	int length;
}SqList;


//初始化顺序表
Status Initlist(SqList &L){
	L.length=0;
//	L.data=(int*)malloc(sizeof(int)*MAX_LENGTH);
	L.data=new int[MAX_LENGTH];
	if(!L.data) exit(OVERFLOW);    //存储分配失败,退出程序
	return OK;
}

//销毁线性表
void DestroyList(SqList &L){
	if(L.data) delete L.data;       //释放存储空间
}

//清空线性表
void ClearList(SqList &L){
	L.length=0;     //逻辑清空
}

//求线性表长度
int GetLength(SqList &L){
	return L.length;
}

//判断线性表是否为空
Status IsEmpty(SqList &L){
	if(L.length==0) return TRUE;
	else return FALSE;
}

//获取线性表中的元素
Status GetElem(SqList &L,int i,int &e){
	if(i<1||i>L.length) return ERROR;   //判断i值是否合理
	e=L.data[i-1];
	return OK;
}

//查找元素
int LocateElem(SqList L,int e){
	for(int i=0;i<L.length;i++)
		if(L.data[i]==e) return i+1;    //返回序号
	return 0;   //查找失败
}

//插入元素
Status ListInsert(SqList &L,int i,int e){
	if(i<1||i>L.length+1||L.length==MAX_LENGTH) //判断合法性
		return ERROR;
	for(int j=L.length-1;j>=i-1;j--)    //插入位置及之后的元素后移
		L.data[j+1]=L.data[j];
	L.data[i]=e;
	L.length++;
	return OK;
	
}

//删除元素
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
