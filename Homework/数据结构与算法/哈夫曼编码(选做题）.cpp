#include <iostream>
#define N 256               // �����������볤�ȣ�+1�� / �����Ҫ����ĸ���
							//��-128��Ӧ���ַ���127��Ӧ���ַ���256���ַ���(��Ȩֵ�ֱ�Ϊ1��2��4...ʱ����Ĺ��������볤�Ȼ�ﵽ255)
#define inf 0x7fffffff      // int�����ֵ

using namespace std;

typedef signed char ElemType;   // ����ڵ��ֵ���������� ������ʹ��signed char����Щ��������charʶ��Ϊunsigned char����
typedef int QType;      		// ����Ȩ�ص��������ͣ������Ȩ����ÿ���ַ����ֵĴ���

/* --------û���ж϶�ȡ�ļ�ʧ�ܵ����-------- */

/* ������������Ľڵ���������� ������ʵ������*/
typedef struct
{
	ElemType data;
	QType weight;
	int parent;
	int lchild, rchild;
} HTNode;

/* ���������������������ͣ��������������������ʹ�ã� */
typedef struct
{
	char cd[N];     	// �����������ɵĹ���������
	int start;          // ���������뿪ʼ��λ��
} HCode;

/* ������ܹ�������������Ľڵ���������� ������ʵ������*/
/* ����Ҳ��һ�ù�������������Ϊ�����֣�ֻ˵�Ƕ�����*/
typedef struct Node
{
	ElemType data;
	Node *lchild, *rchild;
} BTNode;

/* �½��������ڵ� */
void CreateBTNode(BTNode*& b)
{
	b = new BTNode;
	b->lchild = b->rchild = NULL;
	b->data = -1;       // ��ֵΪ-1����ʾ�Ӹ��ڵ㵽�˴�������ĳһ������������
}

/* ʹ����Ȩֵ�Ľڵ㽨���������� */
void CreateHT(HTNode ht[], int n0) /*n0 ԭʼ�ڵ������Ҳ�������յ�Ҷ�ӽڵ���� */
{
	int i, j, lnode, rnode;
	QType min1, min2;          			 // ������С��Ȩֵ
	for (i = 0; i < 2 * n0 - 1; ++i)    // ��ʼ����Ĭ�϶���Ҷ�ӽڵ㣬��û�����Һ���
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
		
	for (i = n0; i < 2 * n0 - 1; ++i)   // ��n0��ʼ��������������
	{
		min1 = min2 = inf;              // Ĭ����СֵΪ���޴�min1�洢����min�н�С���Ǹ���min1��ֵ������
		lnode = rnode = -1;             // Ĭ��û�ҵ����Һ���
		for (j = 0; j < i; ++j)         // ��������������С��ֵ
		{
			if (-1 == ht[j].parent)     // ������Ҫ����Ҷ�ӽڵ�
			{
				if (ht[j].weight < min1)    // Ȼ�����������min����Сֵ��С
				{
					min2 = min1;            // ��min1��ֵ��min2
					rnode = lnode;          // ͬʱmin1����Ľڵ�lnode����¼�Һ��ӵ�rnode
					min1 = ht[j].weight;    // min1����ֵ����Ȼ������min�н�С���Ǹ�
					lnode = j;              // ��¼�ýڵ�Ϊ����
				}
				else if (ht[j].weight < min2)   // �����if���� min1 <= ht[j].weight < min2
				{
					min2 = ht[j].weight;        // min2��������
					rnode = j;                  // �Һ���Ҳ����
				}
			}
		}
		ht[i].weight = min1 + min2;             // ����min1��min2��¼�ľ�����С������Ȩֵ
		ht[i].lchild = lnode;                   // �½ڵ�����Һ��Ӿ�������min��Ӧ�Ľڵ�
		ht[i].rchild = rnode;
		ht[lnode].parent = ht[rnode].parent = i;    // ��¼���ǵ�˫�׽ڵ�
	}
}

/* �ù���������¼���������� */
void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
	int i, f, c;
	HCode hc;
	for (i = 0; i < n0; ++i)    // 0 - n0-1 ��¼�ľ���Ҷ�ӽڵ㣬��Ҷ�ӽڵ������Ҹ��ڵ㣬ͬʱ��¼����������
	{
		hc.start = n0;          // ��ʼ����ʼλ��Ϊ���һ��λ��
		c = i;                  // c��¼��ǰ�ڵ���±�
		f = ht[i].parent;       // f��¼��ǰ�ڵ��˫�׽ڵ���±�

		while (f != -1)         // ���ýڵ㲻�Ǹ��ڵ�ʱ�������������ɺ�ֻ�и��ڵ�û��˫�׽ڵ㣩
		{
			if (ht[f].lchild == c)  // ����ýڵ�����˫�׽ڵ�����ӣ���ô�������������0
				hc.cd[hc.start--] = '0';
			else
				hc.cd[hc.start--] = '1';    // ��֮Ϊ1
			c = f; f = ht[c].parent;        // ��ǰ�ڵ�������˫�׽ڵ��λ�ã�ͬʱf����Ϊ��ǰ�ڵ��˫�׽ڵ�
		}
		++hc.start;                     // start������һ����������
		hcd[i] = hc;                    // ���յõ��Ĺ�����������ǵ�i��Ҷ�ӽڵ�Ĺ���������
	}
}

/* ���ݹ��������빹�����ܶ����������������������ڽ��� */
/* �Ӹ��ڵ������Ϊ���������Ӷ�Ӧ�Ľڵ� */
void addNode(BTNode* b, char* s, int e)
{
	if (*s == '0')  // ������������뵱ǰλ����0��������Ҫȥ��������
	{
		if (!b->lchild) // �����������治���ڣ���������ھʹ���
			CreateBTNode(b->lchild);
		addNode(b->lchild, s+1, e); // ����������������һ��λ��
	}
	else if (*s == '1') // Ҫȥ������
	{
		if (!b->rchild)
			CreateBTNode(b->rchild);
		addNode(b->rchild, s+1, e);
	}
	else    // *s == '\0' �����ַ���ĩβ��
		b->data = e;    // Ϊ�ڵ㸳ֵ��֤���Ӹ��ڵ㵽�˽ڵ�������Ĺ��������� ������ֵe ��Ӧ���ַ�
}

/* 1. ͳ���ַ����ִ�������������������� */
void statAndCalc()
{
	int i, j;
	FILE *in, *out;
	ElemType ch;
	HTNode ht[N * 2];           // �����������Ľڵ��������ʵ�� ���Ҷ�ӽڵ��� * 2 - 1
	HCode hcd[N];				// �����256���ַ����ֱ��Ӧsigned char��-128~127�����256�ֹ���������
	int cnt[N] = {0}, cur = 0;  // cnt����ͳ��256���ַ��ĳ��ִ�����cur�������ճ��ֵ��ַ��ĸ���
	
	for (i = 0, j = -128; i < 256; ++i, ++j)    // ���ȳ�ʼ����ht[0] ���� 0-128 = -128��Ӧ�ַ���ht[255] ����127��Ӧ�ַ�
		ht[i].data = j;

	in = fopen("source.txt", "r");              // ��source�ļ�
	while ( (ch = fgetc(in)) && !feof(in) )     // һ��charһ��char�ض�
	{
		++cnt[ch+128];                          // ͬʱͳ�� -128��Ӧ����cnt[0]
	}
	fclose(in);

	for (i = 0; i < 256; ++i)               // ����cnt���飬�ҳ����ֹ����ַ�����ֵ����������������ʵ�֣���ǰ�����ڵ�
	{
		if (cnt[i])     					// cnt[i] != 0
		{
			ht[cur].data = i - 128;         // ��ԭΪsigned char����Ӧ�� -128 ~ 127
			ht[cur].weight = cnt[i];        // Ȩֵ���ǳ��ֵĴ���
			++cur;                          // cur��¼���ֹ����ַ��ĸ���
		}
	}

	CreateHT(ht, cur);                      // ������������
	CreateHCode(ht, hcd, cur);              // ���ɶ�Ӧ����������

	out = fopen("code.txt", "w");
	for (i = 0; i < cur; ++i)              	    // ����ַ������Ӧ����������
	{
		fprintf(out, "%d ", (int)ht[i].data);   // Ϊ����ֱ�۲�������Щ���ַ���ʾ����������signed char����תint����
		for (j = hcd[i].start; j <= cur; ++j)
			fprintf(out, "%c", hcd[i].cd[j]);   // �ӿ�ʼ����β��������������ÿһλ
		fprintf(out, "\n");
	}
	fclose(out);
}

/* 2. ����code.txt��source.txt���� */
void encrypt()
{
	char code[N][N];    // �������������Ķ�ά���飬��code[200] 200-128=72����Ӧ���ַ� ����Ӧ�Ĺ��������� �� �ַ���
	int t;
	FILE *in, *out;
	ElemType ch;
	
	in = fopen("code.txt", "r");
	
	while (fscanf(in, "%d", &t) != EOF)     // ��code.txt�ж�ȡ����ֵ��ַ��Ĺ��������룬���浽code��ά������
		fscanf(in, "%s", code[t+128]);      // �ַ� + 128 ���ܶ�Ӧ�������±�0-255
		
	fclose(in);


	in = fopen("source.txt", "r");     
	out = fopen("encrypt.txt", "w");
	
	while ( (ch=fgetc(in)) && !feof(in))    // ���ݶ�ȡ���Ĺ��������룬��source.txt�ж�ȡԭ�ģ���������
		fprintf(out, "%s", code[ch+128]);   // �����source�ж�ȡ�����ַ� ��Ӧ�Ĺ��������� �� �ַ���
		
	fclose(in); fclose(out);
}

/* 3.���� */
void unencrypt()
{
	int t;
	BTNode *bt, *p; CreateBTNode(bt);   // ��ʼ��һ�ö������������ǹ���������
	FILE *in, *out;
	ElemType ch;
	char tmp[N];      					// ������ʱ�洢����������
	
	in = fopen("code.txt", "r");        
	
	while (fscanf(in, "%d", &t) != EOF)		// ��code.txt�ж�ȡÿһ���ַ������ɶ�Ӧ�Ľڵ�
	{
		fscanf(in, "%s", tmp);
		addNode(bt, tmp, t);            // �ù��������룬�ڶ������в��Ͽ���/Ѱ�ҽڵ㣬�����ҵ���Ӧ��Ҷ�ӽڵ㲢��ֵ
	}
	
	fclose(in);
	

	in = fopen("encrypt.txt", "r");
	out = fopen("unencrypt.txt", "w");

	p = bt;                                 // pָ��ǰ�ڵ㣬һ��ʼָ����ڵ�
	while ( (ch=fgetc(in)) && !feof(in))    // �������ɵĶ���������������������ȡ���ģ�Ѱ�Ҷ�ӦҶ�ӽڵ�
	{
		p = (ch == '0') ? p->lchild : p->rchild;    // ��ȡ������'0'���ǵĻ�����ǰ�ڵ�pָ��������
		                                            // ���ǵĻ�����ȡ���ľ���'1'�ˣ�����ǰ�ڵ�ָ�����Һ���
		if (p->data != -1)                          // �����ǰ�ڵ���ֵ
		{
			fprintf(out, "%c", p->data);            // �������ֵ����char�������������Ǻ��ֵ�һ����Ҳû��ϵ���������ֻ�ϳ�һ�����֣�
			p = bt;                                 // ��ǰ�ڵ��������»ص����ĸ��ڵ�
		}
	}
	fclose(in); fclose(out);
}

int main()
{
	char ch;
	cout << "��������Ҫ�Ĳ���" << endl;
	cout << "0�����ν���1��2��3" << endl;
	cout << "1: ������ĵ���ÿ���ַ����ֵ�Ƶ�ʣ�����ÿ���ַ����ɶ�Ӧ�Ĺ��������룬���������code.txt��" << endl;
	cout << "2: ��Դ��source.txt�е�ÿ���ַ��ù����������滻��������encrypt.txt�ĵ�" << endl;
	cout << "3��������encrypt.txt����code.txt�ı������ԭ������unencrypt.txt�ĵ�" << endl;
	
	cin >> ch;
	switch(ch)
	{
		case '0': statAndCalc(); encrypt(); unencrypt(); break;
		case '1': statAndCalc(); break;
		case '2': encrypt(); break;
		case '3': unencrypt(); break;
		default: cout << "���������г���" << endl; return 0;
	}
	
	cout << "�����ɹ�" << endl;
	return 0;
}
