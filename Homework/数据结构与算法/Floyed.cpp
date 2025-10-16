#include <iostream>
#define MAXV 100
#define INF 32767
using namespace std;

// �������ͣ����洢������
typedef struct
{
    int no; // ������
} VertexType;

// ͼ���ڽӾ���洢�ṹ
typedef struct
{
    int edges[MAXV][MAXV];  // �ڽӾ���edges[i][j]��ʾ����i��j�ı�Ȩ��INF��ʾ��ֱ�ӱߣ�
    int n, e;               // �������ͱ���
    VertexType vexs[MAXV];  // ������洢������Ϣ��
} MGraph;


// ������ж���Ե����·����Ϣ
// ������G-ͼ�ṹ��A-�������A[i][j]��ʾi��j����̾��룩��path-·������path[i][j]��ʾi��j�����·����ǰ�����㣩
void Dispath(MGraph G, int A[MAXV][MAXV], int path[MAXV][MAXV])
{
    int n = G.n;
    int apath[MAXV];  // ��ʱ�洢·������
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != INF)  // ������ɴ�Ķ����
            {
                printf("��%d��%d�����·������Ϊ:%d\t", i, j, A[i][j]);
                int k = path[i][j], d = 0;  // kΪ��ǰ·����ǰ�����㣬dΪ·�����ȼ�����
                apath[d++] = j;  // �յ�j����·��
                while (k != i)   // ����ֱ���ҵ����i
                {
                    apath[d++] = k;
                    k = path[i][k];
                }
                apath[d++] = i;  // ���i����·��
                // �������·��������㵽�յ㣩
                for (int l = d - 1; l > 0; l--)
                {
                    printf("%d->", apath[l]);
                }
                printf("%d\n", apath[0]);
            }
        }
    }
}

// ��ʾFloyd�㷨�м䲽���·���;������
// ������G-ͼ�ṹ��A-��ǰ�������path-��ǰ·������k-��ǰ�������м䶥�㣨k=-1��ʾ��ʼ״̬��
void Dis_program_path(MGraph G, int A[MAXV][MAXV], int path[MAXV][MAXV], int k)
{
    printf("+---------------------+----------------------+\n");
    if (k >= 0)
    {
        printf("|       path(%d)       |          A(%d)        |\n", k, k);  // ��ʾ��ǰ��������
    }
    else
    {
        printf("|       path(%d)      |          A(%d)       |\n", k, k);   // ��ʼ״̬���
    }
    printf("+---------------------+----------------------+\n");
    int n = G.n;
    int apath[MAXV];  // ��ʱ�洢·������
    for (int i = 0; i < n; i++)
    {
        printf("| ");
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != INF)
            {
                int k = path[i][j], d = 0;
                apath[d++] = j;
                while (k != i)
                {
                    apath[d++] = k;
                    k = path[i][k];
                }
                apath[d++] = i;
                int space = G.n - d;  // ����ո񣨱��ֱ���ʽ��
                while (space--)
                {
                    printf(" ");
                }
                for (int l = d - 1; l >= 0; l--)
                {
                    printf("%d", apath[l]);  // ���·������
                }
                printf(" ");
            }
            else  // ���ɴ�·����ʾ����յ���
            {
                int space = G.n - 2;
                while (space--)
                {
                    printf(" ");
                }
                printf("%d%d ", i, j);
            }
        }
        printf("|  ");
        for (int j = 0; j < n; j++)  // ����������ֵ
        {
            if (A[i][j] != INF)
            {
                printf("%4d ", A[i][j]);
            }
            else
            {
                printf("  oo ");  // �������
            }
        }
        printf("|\n");
    }
    printf("+---------------------+----------------------+\n");
}

// Floyd�㷨���ģ��������ж���Ե����·��
// ������G-ͼ���ڽӾ���ṹ
void floyed(MGraph G)
{
    int A[MAXV][MAXV], path[MAXV][MAXV], n = G.n;
    // ��ʼ���������A��·������path
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = G.edges[i][j];  // A��ʼ��Ϊ�ڽӾ���
            if (G.edges[i][j] != INF)  // ����ֱ�ӱ�ʱ��ǰ��Ϊi
            {
                path[i][j] = i;
            }
            else  // ��ֱ�ӱ�ʱ��·�������ڣ����Ϊ-1��
            {
                path[i][j] = -1;
            }
        }
    }
    int w = -1;
    Dis_program_path(G, A, path, w++);  // �����ʼ״̬��k=-1��

    // ����ѭ���������·����kΪ�м䶥�㣬iΪ��㣬jΪ�յ㣩
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // ������k��·�����̣�����¾����·��
                if (A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];  // ������̾���
                    path[i][j] = path[k][j];       // ����ǰ����k��j��ǰ����
                }
            }
        }
        Dis_program_path(G, A, path, w++);  // �����ǰ����������м���
    }
    Dispath(G, A, path);  // ��������������·����Ϣ
}

int main()
{
    MGraph G;
    int data[MAXV][MAXV] = {
        {0, 1, INF, 4},
        {INF, 0, 9, 2},
        {3, 5, 0, 8},
        {INF, INF, 6, 0}};
    G.n = 4;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            G.edges[i][j] = data[i][j];
        }
    }
    floyed(G);

    return 0;
}