#include<iostream>
using namespace std;

typedef struct 
{
    int rank;       //�����
    int parent;     //����˫��
}UFSTree;           //���鼯���Ľ������

//��ʼ�����鼯��
void Make_Set(UFSTree s[],int n){
    for(int i=1;i<=n;i++){
        s[i].rank=0;        //�ȳ�ʼ��Ϊ0
        s[i].parent=i;      //˫�׳�ʼ��ָ���Լ�
    }
}

//�ݹ��㷨����x�ļ��ϱ��
int Find(UFSTree S[],int x){
    if(x!=S[x].parent){         //�Ǹ��ڵ�
        S[x].parent=Find(S,S[x].parent);
    }
    return S[x].parent;
}

//�ǵݹ��㷨����x�ļ��ϱ��
int Find2(UFSTree S[],int x){
    int rx=x;
    //���ҵ�x�ļ��ϱ��
    while (S[rx].parent!=rx){
        rx=S[rx].parent;
    }
    int y=x;
    //����·���Ͻ��ļ��ϱ��
    while (y!=rx){
        int temp=S[y].parent;
        S[y].parent=rx;
        y=temp;
    }   
}

//�ϲ�x��y�����Ӽ���
void Union(UFSTree S[],int x,int y){
    int rx=Find(S,x);
    int ry=Find(S,y);
    if(rx==ry)      //x��y����ͬһ���Ӽ���
        return;
    if(S[rx].rank>S[ry].rank){          //rx����ȴ���ry�����
        S[ry].parent=rx;                //��ry��Ϊrx�ĺ��ӽ��
    }
    else{
        S[rx].parent=ry;                //��rx��Ϊry�ĺ��ӽ��
        if(S[rx].rank==S[ry].rank){     //����ͬʱ��ѡ��һ������Ϊ���ӽ��
            S[ry].rank++;               //�ȼ�1
        }
    }
}

int main(){


    return 0;
}