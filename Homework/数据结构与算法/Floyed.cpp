#include <iostream>
#define MAXV 100
#define INF 32767
using namespace std;

// 顶点类型，仅存储顶点编号
typedef struct
{
    int no; // 顶点编号
} VertexType;

// 图的邻接矩阵存储结构
typedef struct
{
    int edges[MAXV][MAXV];  // 邻接矩阵，edges[i][j]表示顶点i到j的边权（INF表示无直接边）
    int n, e;               // 顶点数和边数
    VertexType vexs[MAXV];  // 顶点表（存储顶点信息）
} MGraph;


// 输出所有顶点对的最短路径信息
// 参数：G-图结构，A-距离矩阵（A[i][j]表示i到j的最短距离），path-路径矩阵（path[i][j]表示i到j的最短路径的前驱顶点）
void Dispath(MGraph G, int A[MAXV][MAXV], int path[MAXV][MAXV])
{
    int n = G.n;
    int apath[MAXV];  // 临时存储路径顶点
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (A[i][j] != INF)  // 仅处理可达的顶点对
            {
                printf("从%d到%d的最短路径长度为:%d\t", i, j, A[i][j]);
                int k = path[i][j], d = 0;  // k为当前路径的前驱顶点，d为路径长度计数器
                apath[d++] = j;  // 终点j加入路径
                while (k != i)   // 回溯直到找到起点i
                {
                    apath[d++] = k;
                    k = path[i][k];
                }
                apath[d++] = i;  // 起点i加入路径
                // 逆序输出路径（从起点到终点）
                for (int l = d - 1; l > 0; l--)
                {
                    printf("%d->", apath[l]);
                }
                printf("%d\n", apath[0]);
            }
        }
    }
}

// 显示Floyd算法中间步骤的路径和距离矩阵
// 参数：G-图结构，A-当前距离矩阵，path-当前路径矩阵，k-当前迭代的中间顶点（k=-1表示初始状态）
void Dis_program_path(MGraph G, int A[MAXV][MAXV], int path[MAXV][MAXV], int k)
{
    printf("+---------------------+----------------------+\n");
    if (k >= 0)
    {
        printf("|       path(%d)       |          A(%d)        |\n", k, k);  // 显示当前迭代步骤
    }
    else
    {
        printf("|       path(%d)      |          A(%d)       |\n", k, k);   // 初始状态标记
    }
    printf("+---------------------+----------------------+\n");
    int n = G.n;
    int apath[MAXV];  // 临时存储路径顶点
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
                int space = G.n - d;  // 对齐空格（保持表格格式）
                while (space--)
                {
                    printf(" ");
                }
                for (int l = d - 1; l >= 0; l--)
                {
                    printf("%d", apath[l]);  // 输出路径顶点
                }
                printf(" ");
            }
            else  // 不可达路径显示起点终点编号
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
        for (int j = 0; j < n; j++)  // 输出距离矩阵值
        {
            if (A[i][j] != INF)
            {
                printf("%4d ", A[i][j]);
            }
            else
            {
                printf("  oo ");  // 无穷大标记
            }
        }
        printf("|\n");
    }
    printf("+---------------------+----------------------+\n");
}

// Floyd算法核心：计算所有顶点对的最短路径
// 参数：G-图的邻接矩阵结构
void floyed(MGraph G)
{
    int A[MAXV][MAXV], path[MAXV][MAXV], n = G.n;
    // 初始化距离矩阵A和路径矩阵path
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = G.edges[i][j];  // A初始化为邻接矩阵
            if (G.edges[i][j] != INF)  // 存在直接边时，前驱为i
            {
                path[i][j] = i;
            }
            else  // 无直接边时，路径不存在（标记为-1）
            {
                path[i][j] = -1;
            }
        }
    }
    int w = -1;
    Dis_program_path(G, A, path, w++);  // 输出初始状态（k=-1）

    // 三重循环更新最短路径（k为中间顶点，i为起点，j为终点）
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // 若经过k的路径更短，则更新距离和路径
                if (A[i][k] + A[k][j] < A[i][j])
                {
                    A[i][j] = A[i][k] + A[k][j];  // 更新最短距离
                    path[i][j] = path[k][j];       // 更新前驱（k到j的前驱）
                }
            }
        }
        Dis_program_path(G, A, path, w++);  // 输出当前迭代步骤的中间结果
    }
    Dispath(G, A, path);  // 最终输出所有最短路径信息
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