#include<iostream>
#include <Windows.h> 
#define MAXV 100
#define MAXSIZE 10000
#define INF 32767
using namespace std;

typedef struct{
    int no;         // 顶点编号
} VertexType;
typedef struct{
    int edges[MAXV][MAXV]; // 邻接矩阵
    int n, e;              // 顶点数和边数
    VertexType vexs[MAXV]; // 顶点表
} MGraph;

typedef struct ANode{
    int adjvex;            // 邻接点编号
    struct ANode *next;  // 指向下一个结点的指针
    int weight;           // 权值
} ANode;
typedef struct{
    ANode *head;          // 头指针
} VNode;
typedef struct{
    VNode adjlist[MAXV];  // 邻接表
    int n, e;             // 顶点数和边数
} AdjGraph;               // 邻接表图


void CreateAdjGraph(AdjGraph *&G,int A[MAXV][MAXV],int n,int e){

    G=new AdjGraph;
    for(int i=0;i<n;i++)
        G->adjlist[i].head=nullptr;
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){        //倒序访问，便于头插法插入
            if(A[i][j]!=0 && A[i][j]!=INF){
                ANode *p=new ANode;
                p->adjvex=j;
                p->weight=A[i][j];
                p->next=G->adjlist[i].head;
                G->adjlist[i].head=p;
            }
        }
    }
    G->e=e;
    G->n=n;
}

void AdjGraphPrintf(AdjGraph *G){
    for(int i=0;i<G->n;i++){
        ANode *p=new ANode;
        p=G->adjlist[i].head;
        cout<<"V"<<i;
        while(p!=nullptr){
            cout<<"---->"<<p->adjvex<<','<<p->weight;
            p=p->next;
        }
        cout<<'^'<<endl;
    }

}

void CreateMGraph(AdjGraph *GList,MGraph *&G){
    G->e=GList->e;
    G->n=GList->n;
    for(int i = 0; i < GList->n; i++){
        for(int j = 0; j < GList->n; j++){
            if(i == j)
                G->edges[i][j] = 0;
            else
            G->edges[i][j] = INF;
        }
        G->vexs[i].no = i;
    }
    for(int i=0;i<GList->n;i++){
        ANode *p = GList->adjlist[i].head;
        while(p!=nullptr){
            G->edges[i][p->adjvex]=p->weight;
            p=p->next;
        }
    }

}

void MGraphPrintf(MGraph *G){
    for(int i=0;i<G->n;i++){
        for(int j=0;j<G->n;j++){
            if(G->edges[i][j]==INF){
                cout<<"oo"<<'\t';
                continue;
            }
            cout<<' '<<G->edges[i][j]<<'\t';
        }
        cout<<endl;
    }
}


/*Prim算法
 *closest数组为最小生成树，需要时可作为返回值构造二叉树d*/
void Prim(MGraph G,int v){
    cout<<"+----+--------------------------------------------------------------------+-----------------------------+"<<endl;
    cout<<"|起点|                      lowcost数组保存的候选边                       |选择的边(不为0的权值中最小者)|"<<endl;
    cout<<"+----+--------------------------------------------------------------------+-----------------------------+"<<endl;

    int lowcost[MAXV],      //i结点到父节点的最小权值
        closest[MAXV],      //i结点的通过closest[i]连接到生成树
        mindist,k=v;
    for(int i=0;i<G.n;i++){
        /*刚开始时，生成树只有v结点，lowcost为v-i的权值*/
        lowcost[i]=G.edges[v][i];
        /*生成树只有v结点*/
        closest[i]=v;
    }
    for(int i=1;i<G.n;i++){
        printf("| %d  |   ",k);
        mindist=INF;
        /*遍历每条候选边*/
        for(int j=0;j<G.n;j++){
            //生成树结点closest[j]到结点j的权值为lowcost[j]
            if(lowcost[j]==INF) 
                printf("(%d;%d):oo  ",closest[j],j);
            else
                printf("(%d;%d):%d   ",closest[j],j,lowcost[j]); 

            if(lowcost[j]!=0 && lowcost[j]<mindist){                //lowcost[j]==0表示该点已在生成树上 并找出离生成树最近的边     
                //记录最小边和最小结点
                mindist=lowcost[j];
                k=j;
            }
        }
        printf("     |        边(%d,%d)权为:%d        |\n",closest[k],k,mindist);      //输出找到的边
        lowcost[k]=0;                                           //置零 避免生成环
        for(int j=0;j<G.n;j++){
            //对比刚加入的结点与原结点的最小边 并更新
            if(lowcost[j]!=0 && G.edges[k][j]<lowcost[j]){
                lowcost[j]=G.edges[k][j];
                closest[j]=k;
            }
        }
    }
}

typedef struct
{
    int u;      //起始结点
    int v;      //终止结点
    int w;      //权值
}Edge;

// 插入排序函数，按边的权值从小到大排序
void InsertSort(Edge E[], int n) {
    int i, j;
    Edge temp;
    for (i = 1; i < n; i++) {
        temp = E[i];  // 取出当前待插入的边
        j = i - 1;
        // 寻找插入位置并后移较大元素
        while (j >= 0 && E[j].w > temp.w) {
            E[j + 1] = E[j];
            j--;
        }
        E[j + 1] = temp;  // 插入到正确位置
    }
}


/*Kruskal算法*/
void Kruskal(MGraph G){
    int i,j,ul,vl,sn1,sn2,k;
    int vset[MAXV];
    Edge E[MAXSIZE];
    int ESize=0;
    //将G中所有边存放在E数组中
    for(i=0;i<G.n;i++){
        for(j=0;j<G.n;j++){
            if(G.edges[i][j]!=0 && G.edges[i][j]!=INF){
                E[ESize].u=i;E[ESize].v=j;E[ESize].w=G.edges[i][j];
                ESize++;
            }
        }

    }
    InsertSort(E,ESize);            //插入排序
    printf("+- ----+------+------+----------+--------------------+\n");
    printf("| 起点 | 终点 | 权值 | 是否选择 | 集合号:");
    for(i=0;i<G.n;i++){
        vset[i]=i;                  //初始化时，所有元素都属于自己的集合
        cout<<vset[i]<<' ';
    }
    cout<<'|'<<endl;
    printf("+- ----+------+------+----------+--------------------+\n");
    
    
    k=1;j=0;
    while(k<G.n){                   //只生成n-1条边，再生成1条边就会形成环
        ul=E[j].u;vl=E[j].v;
        sn1=vset[ul];
        sn2=vset[vl];               //得到两个顶点的集合编号
        if(sn1!=sn2){               //不属于同一个集合
            printf("|   %d  |   %d  |   %d  | 是       | 集合号:",ul,vl,E[j].w);
            k++;
            for(i=0;i<G.n;i++){     //统一集合编号
                if(vset[i]==sn2){
                    vset[i]=sn1;
                }
                cout<<vset[i]<<' ';
            }
            cout<<'|'<<endl;
        }
        else{
            printf("|   %d  |   %d  |   %d  |   否     | 集合号:            |\n",ul,vl,E[j].w);
        }
        j++;
    }
    printf("+- ----+------+------+----------+--------------------+\n");
}


int main(){
    //定义一个邻接矩阵图
    MGraph G;
    G.n = 6;
    for(int i = 0; i < G.n; i++){
        for(int j = 0; j < G.n; j++){
            if(i == j)
                G.edges[i][j] = 0;
            else
            G.edges[i][j] = INF;
        }
        G.vexs[i].no = i;
    }
    int data[][6] = {
        {0,6,1,5,INF,INF},
        {6,0,5,INF,3,INF},
        {1,5,0,5,6,4},
        {5,INF,5,0,INF,2},
        {INF,3,6,INF,0,6},
        {INF,INF,4,2,6,0}
    };
    for(int i = 0; i < G.n; i++) {
        for(int j = 0; j < G.n; j++) {
            G.edges[i][j] = data[i][j];
        }
    }
    for(int i=0;i<G.n;i++){
        Prim(G,i);
    }
    cout<<"+----+--------------------------------------------------------------------+-----------------------------+"<<endl;

    Kruskal(G);

    return 0;
}