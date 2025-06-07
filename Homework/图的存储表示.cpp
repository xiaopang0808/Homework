#include<iostream>
#define MAXV 100
#define INF 32767
using namespace std;

typedef struct{
    int no;         // ������
} VertexType;
typedef struct{
    int edges[MAXV][MAXV]; // �ڽӾ���
    int n, e;              // �������ͱ���
    VertexType vexs[MAXV]; // �����
} MGraph;

typedef struct ANode{
    int adjvex;            // �ڽӵ���
    struct ANode *next;  // ָ����һ������ָ��
    int weight;           // Ȩֵ
} ANode;
typedef struct{
    ANode *head;          // ͷָ��
} VNode;
typedef struct{
    VNode adjlist[MAXV];  // �ڽӱ�
    int n, e;             // �������ͱ���
} AdjGraph;               // �ڽӱ�ͼ


void CreateAdjGraph(AdjGraph *&G,int A[MAXV][MAXV],int n,int e){
    
    G=new AdjGraph;
    for(int i=0;i<n;i++)
        G->adjlist[i].head=nullptr;
    for(int i=0;i<n;i++){
        for(int j=n-1;j>=0;j--){        //������ʣ�����ͷ�巨����
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

int main(){
    //����һ���ڽӾ���ͼ
    MGraph G1;
    G1.n = 6;
    G1.e = 9;
    for(int i = 0; i < G1.n; i++){
        for(int j = 0; j < G1.n; j++){
            if(i == j)
                G1.edges[i][j] = 0;
            else
            G1.edges[i][j] = INF;
        }
        G1.vexs[i].no = i;
    }
    int data[6][6] = {
        {0, 5, INF, 7, INF, INF},
        {INF, 0, 4, INF, INF, INF},
        {8, INF, 0, INF, INF, 9},
        {INF, INF, 5, 0, INF, 6},
        {INF, INF, INF, 5, 0, INF},
        {3, INF, INF, INF, 1, 0}
    };
    for(int i = 0; i < G1.n; i++) {
        for(int j = 0; j < G1.n; j++) {
            G1.edges[i][j] = data[i][j];
        }
    }
    cout<<"G1:"<<endl;
    MGraphPrintf(&G1);
    AdjGraph *GList;
    CreateAdjGraph(GList,G1.edges,G1.n,G1.e);
    cout<<"�ڽӱ�:"<<endl;
    AdjGraphPrintf(GList);
    MGraph *G2=new MGraph;
    CreateMGraph(GList,G2);
    cout<<"G2:"<<endl;
    MGraphPrintf(G2);
    return 0;
}
