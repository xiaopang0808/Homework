#include<iostream>
using namespace std;

typedef struct 
{
    int rank;       //结点秩
    int parent;     //结点的双亲
}UFSTree;           //并查集树的结点类型

//初始化并查集树
void Make_Set(UFSTree s[],int n){
    for(int i=1;i<=n;i++){
        s[i].rank=0;        //秩初始化为0
        s[i].parent=i;      //双亲初始化指向自己
    }
}

//递归算法查找x的集合编号
int Find(UFSTree S[],int x){
    if(x!=S[x].parent){         //非根节点
        S[x].parent=Find(S,S[x].parent);
    }
    return S[x].parent;
}

//非递归算法查找x的集合编号
int Find2(UFSTree S[],int x){
    int rx=x;
    //先找到x的集合编号
    while (S[rx].parent!=rx){
        rx=S[rx].parent;
    }
    int y=x;
    //更改路径上结点的集合编号
    while (y!=rx){
        int temp=S[y].parent;
        S[y].parent=rx;
        y=temp;
    }   
}

//合并x和y所属子集树
void Union(UFSTree S[],int x,int y){
    int rx=Find(S,x);
    int ry=Find(S,y);
    if(rx==ry)      //x和y属于同一颗子集树
        return;
    if(S[rx].rank>S[ry].rank){          //rx结点秩大于ry结点秩
        S[ry].parent=rx;                //将ry作为rx的孩子结点
    }
    else{
        S[rx].parent=ry;                //将rx作为ry的孩子结点
        if(S[rx].rank==S[ry].rank){     //秩相同时，选任一子树作为孩子结点
            S[ry].rank++;               //秩加1
        }
    }
}

int main(){


    return 0;
}