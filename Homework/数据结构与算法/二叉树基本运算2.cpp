#include<bits/stdc++.h>
using namespace std;
int len=40;         //凹入表示法输出长度

typedef char elemtype;
typedef struct node{
	elemtype data;
	struct node *lchild,*rchild;
}BTnode;

BTnode* BTtree_Init(){
	BTnode *T=new BTnode;
	T->lchild=NULL;
	T->rchild=NULL;
	return T;
}

void Creat_tree(BTnode*& T, string s) {
    vector<BTnode*> vec;
    BTnode* p = NULL;
    int flag = 0;
    T=NULL;

    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case '(':
                flag = 0;
                if (p) {
                    vec.push_back(p);
                }
                break;
            case ')':
                if (!vec.empty()) {
                    vec.pop_back();
                }
                break;
            case ',':
                flag = 1;
                break;
            default:
                p = new BTnode;
                p->data = s[i];
                p->lchild = p->rchild = NULL;
                if (!T) {
                    T = p;
                } else {
                    if (vec.empty()) {
                        continue;
                    }
                    if (flag == 0) {
                        vec.back()->lchild = p;
                    } else {
                        vec.back()->rchild = p;
                    }
                }
        }
    }
}

void showTree(BTnode *T){
	if(T==NULL) return;
	cout<<T->data;
	if(T->lchild!=NULL || T->rchild!=NULL){
		cout<<'(';
		showTree(T->lchild);
		if(T->rchild!=NULL){
			cout<<',';
			showTree(T->rchild);
		}
		cout<<')';
	}
	
}

/* 先序遍历*/
void PreDisp(BTnode *T){
    if(!T){ cout<<'^'; return; }
    cout<<T->data;      //先输出根节点
    PreDisp(T->lchild); //优先遍历左子树
    PreDisp(T->rchild);
}

/* 中序遍历*/
void InOrder(BTnode *T){
    if(!T){ cout<<'^'; return; }
    InOrder(T->lchild);
    cout<<T->data;      //先遍历左子树再输出根节点
    InOrder(T->rchild);
}

/* 后序遍历*/
void PostOrder(BTnode *T){
    if(!T){ cout<<'^'; return; }
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    cout<<T->data;      //先遍历左右子树，再输出根节点
}

/* 层次遍历*/
void PrefaceDisp(BTnode *T){
    queue<BTnode*> q;
    q.push(T);
    // 创建空节点标记
    BTnode *temp=new BTnode{'^'};
    while(!q.empty()){  //广度优先搜索，按层展开
        BTnode *new_node=q.front();
        cout<<new_node->data;
        q.pop();
        // 遇到标记节点不处理子节点
        if(new_node->data=='^') continue;
        // 子节点处理，空节点用^代替
        q.push(new_node->lchild?new_node->lchild:temp);
        q.push(new_node->rchild?new_node->rchild:temp);
    }
}

/*先序凹入输出*/
void Pre_In_Disp(BTnode *T,int deep,char name){
	if(T==NULL) return ;
	int Tab=3;          //缩进长度
	int pos=deep*Tab-2;     //计算结点字符位置
	for(int i=1;i<=len;i++){    //补全剩余字符
		if(i<pos) cout<<' ';
		else if(i==pos) cout<<T->data;
		else{
			if(i==len) cout<<name<<endl;    //尾字符输出结点名字
			else cout<<'=';
		}
	}
	Pre_In_Disp(T->lchild,deep+1,'L');  //递归左右子树
	Pre_In_Disp(T->rchild,deep+1,'R');
}
/*中序凹入输出，与先序--类似，不再赘述*/
void InOrder_In_Disp(BTnode *T,int deep,char name){
	if(T==NULL) return ;
	int Tab=3;
	int pos=deep*Tab-2;
	InOrder_In_Disp(T->lchild,deep+1,'L');
	for(int i=1;i<=len;i++){
		if(i<pos) cout<<' ';
		else if(i==pos) cout<<T->data;
		else{
			if(i==len) cout<<name<<endl;
			else cout<<'=';
		}
	}
	InOrder_In_Disp(T->rchild,deep+1,'R');
}

/*后序凹入输出，与先序--类似，不再赘述*/
void Post_In_Disp(BTnode *T,int deep,char name){
	if(T==NULL) return ;
	int Tab=3;
	int pos=deep*Tab-2;
	Post_In_Disp(T->lchild,deep+1,'L');
	Post_In_Disp(T->rchild,deep+1,'R');
	for(int i=1;i<=len;i++){
		if(i<pos) cout<<' ';
		else if(i==pos) cout<<T->data;
		else{
			if(i==len) cout<<name<<endl;
			else cout<<'=';
		}
	}
}

/*翻转左右子树，即创建镜像树*/
BTnode* MirrorTree(BTnode *T){
	if(T==NULL) return NULL;
	BTnode *temp=new BTnode;
	temp=MirrorTree(T->lchild);
	T->lchild=MirrorTree(T->rchild);
	T->rchild=temp;
	return T;
}

//使用全局变量，方便操作
int max_distance = 0;       
BTnode* max_nodeA = NULL;
BTnode* max_nodeB = NULL;

struct Result {
    int depth;      //当前子树深度
    BTnode* deepest;    //当前子树最深结点
};

Result Farthest_node(BTnode* T) {
    if (T==NULL) return {0,NULL};   //空结点
    Result left=Farthest_node(T->lchild);   //递归获得左右子树信息
    Result right=Farthest_node(T->rchild);

    int now_deep=1+max(left.depth, right.depth);    //当亲深度为左右子树最大深度+1

    // 确定当前子树的最深叶节点
    BTnode* now_deepest_node=new BTnode;
    if (left.depth>right.depth) {
        now_deepest_node = left.deepest;    //继承左子树最深节点
    } else if (right.depth > left.depth) {
        now_deepest_node = right.deepest;   // 右子树更深，继承右子树最深节点
    } else {
        /*
            三种情况：左右子树分别为空，或都为空
		*/
        if (left.deepest)
            now_deepest_node = left.deepest;
        else if (right.deepest)
            now_deepest_node = right.deepest;
        else
            now_deepest_node = T;            //叶子结点
    }
    // 计算经过当前节点的最长路径（左深度 + 右深度）
    int now_max = left.depth + right.depth;

    if (now_max > max_distance) {
        max_distance = now_max;
        // 左子树的最深节点
        max_nodeA = (left.deepest != NULL) ? left.deepest : T;
        // 右子树的最深节点
        max_nodeB = (right.deepest != NULL) ? right.deepest : T;
    }
    // 返回当前子树信息（
    return {now_deep, now_deepest_node};
}

int main(){
	string s="A(B(D(,G)),C(E,F))";
	BTnode *T;
	Creat_tree(T,s);
 	cout<<"先序遍历:";PreDisp(T);cout<<endl;
 	cout<<"中序遍历:";InOrder(T);cout<<endl;
 	cout<<"后序遍历:";PostOrder(T);cout<<endl;
 	cout<<"层次遍历:";PrefaceDisp(T);cout<<endl;
 	cout<<"先序凹入表示法:"<<endl;
 	Pre_In_Disp(T,1,'B');
 	cout<<"中序凹入表示法:"<<endl;
 	InOrder_In_Disp(T,1,'B');
 	cout<<"后序凹入表示法:"<<endl;
 	Post_In_Disp(T,1,'B');
 	BTnode *B=MirrorTree(T);
    cout<<"镜像树:";showTree(B);cout<<endl;
    Farthest_node(T);
    cout<<"相隔最远的两个结点为:"<<max_nodeA->data<<"与"<< max_nodeB->data << endl;
    return 0;
}
