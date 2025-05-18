#include<iostream>
#define MAXV 100
#define INF 32767
using namespace std;

typedef struct{
    int no;         // 顶点编号
} VertexType;
typedef struct{
    int edges[MAXV][MAXV]; // 邻接矩阵
    int n;              // 顶点数
    VertexType vexs[MAXV]; // 顶点表
} MGraph;

typedef struct ANode{
    int adjvex;            // 邻接点编号
    struct ANode *next;  // 指向下一个结点的指针
} ANode;
typedef struct{
    ANode *head;          // 头指针
} VNode;
typedef struct{
    VNode adjlist[MAXV];  // 邻接表
    int n;             // 顶点数
} AdjGraph;               // 邻接表图


void CreateAdjGraph(AdjGraph *&G,int A[MAXV][MAXV],int n){
    G=new AdjGraph;
    G->n=n;
    for(int i=0;i<n;i++)
        G->adjlist[i].head=nullptr;
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){        //倒序访问，便于头插法插入
            if(A[i][j]!=0 && A[i][j]!=INF){
                ANode *p=new ANode;
                p->adjvex=j;
                p->next=G->adjlist[i].head;
                G->adjlist[i].head=p;
            }
        }
    }
}

void AdjGraphPrintf(AdjGraph *G){
    for(int i=0;i<G->n;i++){
        ANode *p=new ANode;
        p=G->adjlist[i].head;
        cout<<"V"<<i;
        while(p!=nullptr){
            cout<<"---->"<<p->adjvex;
            p=p->next;
        }
        cout<<'^'<<endl;
    }

}

void CreateMGraph(AdjGraph *GList,MGraph *&G){
    G->n=GList->n;
    for(int i = 0; i < GList->n; i++){
        for(int j = 0; j < GList->n; j++){
            G->edges[i][j] = 0;
        }
        G->vexs[i].no = i;
    }
    for(int i=0;i<GList->n;i++){
        ANode *p = GList->adjlist[i].head;
        while(p!=nullptr){
            G->edges[i][p->adjvex] = 1;
            p=p->next;
        }
    }
    
}

void MGraphPrintf(MGraph *G){
    for(int i=0;i<G->n;i++){
        for(int j=0;j<G->n;j++){
            cout<<' '<<G->edges[i][j]<<' ';
        }
        cout<<endl;
    }
}

int visited[MAXV] = {0};
void Graph_DFS(AdjGraph *G, int v) {
    cout << v << " ";
    visited[v] = 1;
    ANode *p = G->adjlist[v].head;
    while (p != nullptr) {
        int w = p->adjvex;
        if (visited[w]==0) {
            Graph_DFS(G, w);
        }
        p = p->next;
    }
}

int visited1[MAXV] = {0};
typedef struct queue {
    int data[MAXV];       
    int front, rear;    
} Queue;

void Graph_BFS(AdjGraph *G, int v) {
    Queue q;
    q.front = q.rear = 0;
    visited1[v] = 1;
    cout << v << " ";
    q.data[q.rear++] = v;
    while (q.front != q.rear) {
        int current = q.data[q.front++]; 
        ANode *p = G->adjlist[current].head;
        while (p != nullptr) {
            int w = p->adjvex;
            if (!visited1[w]) {
                visited1[w] = 1;         
                cout << w << " ";
                q.data[q.rear++] = w;
            }
            p = p->next;
        }
    }
    cout << endl;
}



int main(){
    int A[MAXV][MAXV]={
        {0,1,1,1,0,0,0,0,0,0,0},    //0
        {1,0,0,0,1,1,0,0,0,0,0},    //1
        {1,0,0,1,0,1,1,0,0,0,0},    //2
        {1,0,1,0,0,0,0,1,0,0,0},    //3
        {0,1,0,0,0,0,0,0,0,0,0},    //4
        {0,1,1,0,0,0,0,0,0,0,0},    //5
        {0,0,1,0,0,0,0,1,1,1,0},    //6
        {0,0,0,1,0,0,1,0,0,0,1},    //7
        {0,0,0,0,0,0,1,0,0,0,0},    //8
        {0,0,0,0,0,0,1,0,0,0,0},    //9
        {0,0,0,0,0,0,0,1,0,0,0}     //10
    };
    AdjGraph *GList1;
    CreateAdjGraph(GList1,A,11);
    MGraph *G=new MGraph;
    CreateMGraph(GList1,G);
    cout<<"无向不带权图G的邻接矩阵:"<<endl;
    MGraphPrintf(G);
    AdjGraph *GList2;
    CreateAdjGraph(GList2,G->edges,G->n);
    cout<<"G的邻接矩阵转换成邻接表:"<<endl;
    AdjGraphPrintf(GList2);  
    
    int start;
    cout<<"请输入起点:";cin>>start;
    cout<<"以"<<start<<"为起点的深度优先遍历序列:";
    Graph_DFS(GList2,start);cout<<endl;
    cout<<"以"<<start<<"为起点的广度优先遍历序列:";
    Graph_BFS(GList2,start);  
    return 0;
}