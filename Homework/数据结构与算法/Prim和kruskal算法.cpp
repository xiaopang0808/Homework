#include<iostream>
#include <Windows.h> 
#define MAXV 100
#define MAXSIZE 10000
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


/*Prim�㷨
 *closest����Ϊ��С����������Ҫʱ����Ϊ����ֵ���������d*/
void Prim(MGraph G,int v){
    cout<<"+----+--------------------------------------------------------------------+-----------------------------+"<<endl;
    cout<<"|���|                      lowcost���鱣��ĺ�ѡ��                       |ѡ��ı�(��Ϊ0��Ȩֵ����С��)|"<<endl;
    cout<<"+----+--------------------------------------------------------------------+-----------------------------+"<<endl;

    int lowcost[MAXV],      //i��㵽���ڵ����СȨֵ
        closest[MAXV],      //i����ͨ��closest[i]���ӵ�������
        mindist,k=v;
    for(int i=0;i<G.n;i++){
        /*�տ�ʼʱ��������ֻ��v��㣬lowcostΪv-i��Ȩֵ*/
        lowcost[i]=G.edges[v][i];
        /*������ֻ��v���*/
        closest[i]=v;
    }
    for(int i=1;i<G.n;i++){
        printf("| %d  |   ",k);
        mindist=INF;
        /*����ÿ����ѡ��*/
        for(int j=0;j<G.n;j++){
            //���������closest[j]�����j��ȨֵΪlowcost[j]
            if(lowcost[j]==INF) 
                printf("(%d;%d):oo  ",closest[j],j);
            else
                printf("(%d;%d):%d   ",closest[j],j,lowcost[j]); 

            if(lowcost[j]!=0 && lowcost[j]<mindist){                //lowcost[j]==0��ʾ�õ������������� ���ҳ�������������ı�     
                //��¼��С�ߺ���С���
                mindist=lowcost[j];
                k=j;
            }
        }
        printf("     |        ��(%d,%d)ȨΪ:%d        |\n",closest[k],k,mindist);      //����ҵ��ı�
        lowcost[k]=0;                                           //���� �������ɻ�
        for(int j=0;j<G.n;j++){
            //�Աȸռ���Ľ����ԭ������С�� ������
            if(lowcost[j]!=0 && G.edges[k][j]<lowcost[j]){
                lowcost[j]=G.edges[k][j];
                closest[j]=k;
            }
        }
    }
}

typedef struct
{
    int u;      //��ʼ���
    int v;      //��ֹ���
    int w;      //Ȩֵ
}Edge;

// ���������������ߵ�Ȩֵ��С��������
void InsertSort(Edge E[], int n) {
    int i, j;
    Edge temp;
    for (i = 1; i < n; i++) {
        temp = E[i];  // ȡ����ǰ������ı�
        j = i - 1;
        // Ѱ�Ҳ���λ�ò����ƽϴ�Ԫ��
        while (j >= 0 && E[j].w > temp.w) {
            E[j + 1] = E[j];
            j--;
        }
        E[j + 1] = temp;  // ���뵽��ȷλ��
    }
}


/*Kruskal�㷨*/
void Kruskal(MGraph G){
    int i,j,ul,vl,sn1,sn2,k;
    int vset[MAXV];
    Edge E[MAXSIZE];
    int ESize=0;
    //��G�����бߴ����E������
    for(i=0;i<G.n;i++){
        for(j=0;j<G.n;j++){
            if(G.edges[i][j]!=0 && G.edges[i][j]!=INF){
                E[ESize].u=i;E[ESize].v=j;E[ESize].w=G.edges[i][j];
                ESize++;
            }
        }

    }
    InsertSort(E,ESize);            //��������
    printf("+- ----+------+------+----------+--------------------+\n");
    printf("| ��� | �յ� | Ȩֵ | �Ƿ�ѡ�� | ���Ϻ�:");
    for(i=0;i<G.n;i++){
        vset[i]=i;                  //��ʼ��ʱ������Ԫ�ض������Լ��ļ���
        cout<<vset[i]<<' ';
    }
    cout<<'|'<<endl;
    printf("+- ----+------+------+----------+--------------------+\n");
    
    
    k=1;j=0;
    while(k<G.n){                   //ֻ����n-1���ߣ�������1���߾ͻ��γɻ�
        ul=E[j].u;vl=E[j].v;
        sn1=vset[ul];
        sn2=vset[vl];               //�õ���������ļ��ϱ��
        if(sn1!=sn2){               //������ͬһ������
            printf("|   %d  |   %d  |   %d  | ��       | ���Ϻ�:",ul,vl,E[j].w);
            k++;
            for(i=0;i<G.n;i++){     //ͳһ���ϱ��
                if(vset[i]==sn2){
                    vset[i]=sn1;
                }
                cout<<vset[i]<<' ';
            }
            cout<<'|'<<endl;
        }
        else{
            printf("|   %d  |   %d  |   %d  |   ��     | ���Ϻ�:            |\n",ul,vl,E[j].w);
        }
        j++;
    }
    printf("+- ----+------+------+----------+--------------------+\n");
}


int main(){
    //����һ���ڽӾ���ͼ
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