#include <iostream>
#define N 256               // 最大哈夫曼编码长度（+1） / 最大需要编码的个数
							//（-128对应的字符到127对应的字符共256个字符）(当权值分别为1、2、4...时，最长的哈夫曼编码长度会达到255)
#define inf 0x7fffffff      // int的最大值

using namespace std;

typedef signed char ElemType;   // 定义节点的值的数据类型 （这里使用signed char（有些编译器把char识别为unsigned char））
typedef int QType;      		// 定义权重的数据类型，这里的权重是每个字符出现的次数

/* --------没有判断读取文件失败的情况-------- */

/* 定义哈夫曼树的节点的数据类型 （数组实现树）*/
typedef struct
{
	ElemType data;
	QType weight;
	int parent;
	int lchild, rchild;
} HTNode;

/* 定义哈夫曼编码的数据类型（产生哈夫曼编码过程中使用） */
typedef struct
{
	char cd[N];     	// 用来保存生成的哈夫曼编码
	int start;          // 哈夫曼编码开始的位置
} HCode;

/* 定义解密哈夫曼编码的树的节点的数据类型 （链表实现树）*/
/* 本质也是一棵哈夫曼树，这里为了区分，只说是二叉树*/
typedef struct Node
{
	ElemType data;
	Node *lchild, *rchild;
} BTNode;

/* 新建二叉树节点 */
void CreateBTNode(BTNode*& b)
{
	b = new BTNode;
	b->lchild = b->rchild = NULL;
	b->data = -1;       // 赋值为-1，表示从根节点到此处不代表某一个哈夫曼编码
}

/* 使用有权值的节点建立哈夫曼树 */
void CreateHT(HTNode ht[], int n0) /*n0 原始节点个数，也就是最终的叶子节点个数 */
{
	int i, j, lnode, rnode;
	QType min1, min2;          			 // 两个最小的权值
	for (i = 0; i < 2 * n0 - 1; ++i)    // 初始化，默认都是叶子节点，都没有左右孩子
		ht[i].parent = ht[i].lchild = ht[i].rchild = -1;
		
	for (i = n0; i < 2 * n0 - 1; ++i)   // 从n0开始，构建哈夫曼树
	{
		min1 = min2 = inf;              // 默认最小值为无限大，min1存储两个min中较小的那个，min1的值给左孩子
		lnode = rnode = -1;             // 默认没找到左右孩子
		for (j = 0; j < i; ++j)         // 从左到右找两个最小的值
		{
			if (-1 == ht[j].parent)     // 首先需要它是叶子节点
			{
				if (ht[j].weight < min1)    // 然后如果比两个min的最小值还小
				{
					min2 = min1;            // 则min1的值给min2
					rnode = lnode;          // 同时min1代表的节点lnode给记录右孩子的rnode
					min1 = ht[j].weight;    // min1赋新值，仍然是两个min中较小的那个
					lnode = j;              // 记录该节点为左孩子
				}
				else if (ht[j].weight < min2)   // 进这个if代表 min1 <= ht[j].weight < min2
				{
					min2 = ht[j].weight;        // min2换掉即可
					rnode = j;                  // 右孩子也换掉
				}
			}
		}
		ht[i].weight = min1 + min2;             // 最终min1和min2记录的就是最小的两个权值
		ht[i].lchild = lnode;                   // 新节点的左右孩子就是两个min对应的节点
		ht[i].rchild = rnode;
		ht[lnode].parent = ht[rnode].parent = i;    // 记录它们的双亲节点
	}
}

/* 用哈夫曼树记录哈夫曼编码 */
void CreateHCode(HTNode ht[], HCode hcd[], int n0)
{
	int i, f, c;
	HCode hc;
	for (i = 0; i < n0; ++i)    // 0 - n0-1 记录的就是叶子节点，从叶子节点往上找根节点，同时记录哈夫曼编码
	{
		hc.start = n0;          // 初始化开始位置为最后一个位置
		c = i;                  // c记录当前节点的下标
		f = ht[i].parent;       // f记录当前节点的双亲节点的下标

		while (f != -1)         // 当该节点不是根节点时（哈夫曼树建成后只有根节点没有双亲节点）
		{
			if (ht[f].lchild == c)  // 如果该节点是其双亲节点的左孩子，那么哈夫曼编码就是0
				hc.cd[hc.start--] = '0';
			else
				hc.cd[hc.start--] = '1';    // 反之为1
			c = f; f = ht[c].parent;        // 当前节点来到其双亲节点的位置，同时f更新为当前节点的双亲节点
		}
		++hc.start;                     // start多退了一个，往右移
		hcd[i] = hc;                    // 最终得到的哈夫曼编码就是第i个叶子节点的哈夫曼编码
	}
}

/* 根据哈夫曼编码构建解密二叉树（哈夫曼树），用于解码 */
/* 从根节点出发，为二叉树增加对应的节点 */
void addNode(BTNode* b, char* s, int e)
{
	if (*s == '0')  // 如果哈夫曼编码当前位置是0，代表它要去到左子树
	{
		if (!b->lchild) // 看看左子树存不存在，如果不存在就创建
			CreateBTNode(b->lchild);
		addNode(b->lchild, s+1, e); // 到左子树，继续下一个位置
	}
	else if (*s == '1') // 要去右子树
	{
		if (!b->rchild)
			CreateBTNode(b->rchild);
		addNode(b->rchild, s+1, e);
	}
	else    // *s == '\0' 到达字符串末尾了
		b->data = e;    // 为节点赋值，证明从根节点到此节点所代表的哈夫曼编码 代表数值e 对应的字符
}

/* 1. 统计字符出现次数，并计算哈夫曼编码 */
void statAndCalc()
{
	int i, j;
	FILE *in, *out;
	ElemType ch;
	HTNode ht[N * 2];           // 最大哈夫曼树的节点个数，其实是 最大叶子节点数 * 2 - 1
	HCode hcd[N];				// 最多有256个字符，分别对应signed char的-128~127，最多256种哈夫曼编码
	int cnt[N] = {0}, cur = 0;  // cnt数组统计256个字符的出现次数，cur代表最终出现的字符的个数
	
	for (i = 0, j = -128; i < 256; ++i, ++j)    // 首先初始化，ht[0] 代表 0-128 = -128对应字符，ht[255] 代表127对应字符
		ht[i].data = j;

	in = fopen("source.txt", "r");              // 读source文件
	while ( (ch = fgetc(in)) && !feof(in) )     // 一个char一个char地读
	{
		++cnt[ch+128];                          // 同时统计 -128对应的是cnt[0]
	}
	fclose(in);

	for (i = 0; i < 256; ++i)               // 遍历cnt数组，找出出现过的字符，赋值给哈夫曼树（数组实现）的前几个节点
	{
		if (cnt[i])     					// cnt[i] != 0
		{
			ht[cur].data = i - 128;         // 还原为signed char所对应的 -128 ~ 127
			ht[cur].weight = cnt[i];        // 权值就是出现的次数
			++cur;                          // cur记录出现过的字符的个数
		}
	}

	CreateHT(ht, cur);                      // 建立哈夫曼树
	CreateHCode(ht, hcd, cur);              // 生成对应哈夫曼编码

	out = fopen("code.txt", "w");
	for (i = 0; i < cur; ++i)              	    // 输出字符及其对应哈夫曼编码
	{
		fprintf(out, "%d ", (int)ht[i].data);   // 为方便直观不出错（有些单字符显示不出来），signed char类型转int类型
		for (j = hcd[i].start; j <= cur; ++j)
			fprintf(out, "%c", hcd[i].cd[j]);   // 从开始到结尾输出哈夫曼编码的每一位
		fprintf(out, "\n");
	}
	fclose(out);
}

/* 2. 利用code.txt对source.txt加密 */
void encrypt()
{
	char code[N][N];    // 保存哈夫曼编码的二维数组，如code[200] 200-128=72所对应的字符 所对应的哈夫曼编码 的 字符串
	int t;
	FILE *in, *out;
	ElemType ch;
	
	in = fopen("code.txt", "r");
	
	while (fscanf(in, "%d", &t) != EOF)     // 从code.txt中读取会出现的字符的哈夫曼编码，保存到code二维数组中
		fscanf(in, "%s", code[t+128]);      // 字符 + 128 才能对应上数组下标0-255
		
	fclose(in);


	in = fopen("source.txt", "r");     
	out = fopen("encrypt.txt", "w");
	
	while ( (ch=fgetc(in)) && !feof(in))    // 根据读取到的哈夫曼编码，从source.txt中读取原文，生成密文
		fprintf(out, "%s", code[ch+128]);   // 输出从source中读取到的字符 对应的哈夫曼编码 的 字符串
		
	fclose(in); fclose(out);
}

/* 3.解密 */
void unencrypt()
{
	int t;
	BTNode *bt, *p; CreateBTNode(bt);   // 初始化一棵二叉树（最终是哈夫曼树）
	FILE *in, *out;
	ElemType ch;
	char tmp[N];      					// 用来暂时存储哈夫曼编码
	
	in = fopen("code.txt", "r");        
	
	while (fscanf(in, "%d", &t) != EOF)		// 从code.txt中读取每一个字符，生成对应的节点
	{
		fscanf(in, "%s", tmp);
		addNode(bt, tmp, t);            // 用哈夫曼编码，在二叉树中不断开辟/寻找节点，最终找到对应的叶子节点并赋值
	}
	
	fclose(in);
	

	in = fopen("encrypt.txt", "r");
	out = fopen("unencrypt.txt", "w");

	p = bt;                                 // p指向当前节点，一开始指向根节点
	while ( (ch=fgetc(in)) && !feof(in))    // 根据生成的二叉树（哈夫曼树），读取密文，寻找对应叶子节点
	{
		p = (ch == '0') ? p->lchild : p->rchild;    // 读取到的是'0'吗？是的话，当前节点p指向其左孩子
		                                            // 不是的话（读取到的就是'1'了），当前节点指向其右孩子
		if (p->data != -1)                          // 如果当前节点有值
		{
			fprintf(out, "%c", p->data);            // 就输出该值（以char类型输出，如果是汉字的一部分也没关系，两个部分会合成一个汉字）
			p = bt;                                 // 当前节点来到重新回到树的根节点
		}
	}
	fclose(in); fclose(out);
}

int main()
{
	char ch;
	cout << "请输入需要的操作" << endl;
	cout << "0：依次进行1、2、3" << endl;
	cout << "1: 计算出文档中每个字符出现的频率，对于每个字符生成对应的哈夫曼编码，结果保存在code.txt中" << endl;
	cout << "2: 将源文source.txt中的每个字符用哈夫曼编码替换生成密文encrypt.txt文档" << endl;
	cout << "3：把密文encrypt.txt根据code.txt的编码规则还原成明文unencrypt.txt文档" << endl;
	
	cin >> ch;
	switch(ch)
	{
		case '0': statAndCalc(); encrypt(); unencrypt(); break;
		case '1': statAndCalc(); break;
		case '2': encrypt(); break;
		case '3': unencrypt(); break;
		default: cout << "请重新运行程序" << endl; return 0;
	}
	
	cout << "操作成功" << endl;
	return 0;
}
