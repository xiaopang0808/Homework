#include<bits/stdc++.h>
using namespace std;

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
    std::vector<BTnode*> stack;
    BTnode* p = NULL;
    int flag = 0;
    T =NULL;

    for (int i = 0; i < s.size(); i++) {
        switch (s[i]) {
            case '(':
                flag = 0;
                if (p) {
                    stack.push_back(p);
                }
                break;
            case ')':
                if (!stack.empty()) {
                    stack.pop_back();
                }
                break;
            case ',':
                flag = 1;
                break;
            default:
                p = new BTnode;
                p->data = s[i];
                p->lchild = p->rchild = nullptr;

                if (!T) {
                    T = p;
                } else {
                    if (stack.empty()) {
                        continue;
                    }
                    if (flag == 0) {
                        stack.back()->lchild = p;
                    } else {
                        stack.back()->rchild = p;
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

BTnode* find_node(BTnode *T,elemtype x){
	if(T==NULL) return NULL;
	if(T->data==x) return T;
	BTnode *left=find_node(T->lchild,x);
	if(left!=NULL) return left;
	return find_node(T->rchild,x);
}

int tree_height(BTnode *T){
	if(T==NULL) return 0;
	int left=tree_height(T->lchild);
	int right=tree_height(T->rchild);
	return 1+(left>right?left:right);
}

int CNT_node(BTnode *T){
	if(T==NULL) return 0;
	return 1+CNT_node(T->lchild)+CNT_node(T->rchild);
}

int CNT_double_branch(BTnode *T){
	if(T==NULL) return 0;
	int cnt=(T->lchild && T->rchild)?1:0;
	return cnt+CNT_double_branch(T->lchild)+CNT_double_branch(T->rchild);
}

int CNT_single_branch(BTnode *T){
	if(T==NULL) return 0;
	int cnt=((!T->lchild && T->rchild) || (T->lchild && !T->rchild))?1:0;
	return cnt+CNT_single_branch(T->lchild)+CNT_single_branch(T->rchild);
}

int CNT_leaf(BTnode *T){
	if(T==NULL) return 0;
	int cnt=(!T->lchild && !T->rchild)?1:0;
	return cnt+CNT_leaf(T->lchild)+CNT_leaf(T->rchild);
}

int Get_width(BTnode *T){   //�����������
	if(T==NULL) return 0;
	queue<BTnode*> q;
	int max_width=0;
	q.push(T);
	while(!q.empty()){
		int level=q.size();
		max_width=max(level,max_width);
		for(int i=0;i<level;i++){
			BTnode *newnode=q.front();
			q.pop();
			if(newnode->lchild) q.push(newnode->lchild);
			if(newnode->rchild) q.push(newnode->rchild);
		}
	}
	return max_width;
}

void destroy(BTnode *&T){
	if(T){
		destroy(T->lchild);
		destroy(T->rchild);
		delete T;
	}
}

BTnode* LCA(BTnode *T,elemtype q,elemtype p){
	if(T==NULL || T->data==q || T->data==p) return T;
	BTnode *left=LCA(T->lchild,q,p);
	BTnode *right=LCA(T->rchild,q,p);
	if(left!=NULL && right!=NULL) return T;
	return (left!=NULL)?left:right;
}

void test(string s,elemtype find_val,elemtype LCA_fir,elemtype LCA_sec){
	BTnode *T=BTtree_Init();
	Creat_tree(T,s);
	cout<<"���ű�ʾ�������������";showTree(T);cout<<endl;
	cout<<"�����ҽ���ֵ:"<<find_val<<endl;
	BTnode *find=find_node(T,find_val);
	if(find==NULL){
		cout<<"���޴�ֵ!"<<endl;
 	}
 	else{
 		cout<<"����:";
		if(find->lchild) cout<<find->lchild->data;
		else cout<<"��";
		cout<<'\t'<<"�Һ���:";
		if(find->rchild) cout<<find->rchild->data;
		else cout<<"��";
		cout<<endl;
	}
	cout<<"����:"<<tree_height(T)<<endl;
	cout<<"�����:"<<CNT_node(T)<<endl;
	cout<<"˫��֧�����:"<<CNT_double_branch(T)<<endl;
	cout<<"����֧�����:"<<CNT_single_branch(T)<<endl;
	cout<<"Ҷ����:"<<CNT_leaf(T)<<endl;
	cout<<"����:"<<Get_width(T)<<endl;
	elemtype a,b;
	cout<<"�����ͬ���Ȳ�ѯ:\n\t��һ�����:"
		<<LCA_fir<<"\t�ڶ������:"<<LCA_sec<<endl;
	BTnode *L=LCA(T,LCA_fir,LCA_sec);
	if(L) cout<<"���ǵ������ͬ����Ϊ:"<<L->data<<endl;
	else cout<<"����û����Ե��ϵ"<<endl;
}


int main(){
	string s="A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
 	cout<<"------------------��һ��ʾ��--��һ�����ݣ���ȷ��------------------"<<endl;
 	test(s,'B','J','N');
 	cout<<"------------------��һ��ʾ��--�ڶ������ݣ���ȷ��------------------"<<endl;
 	test(s,'G','L','E');
 	cout<<"------------------��һ��ʾ��--���������ݣ�����------------------"<<endl;
	test(s,'Z','Z','W');
	string s2="A(B(D(,G)),C(E,F))";
	cout<<"------------------�ڶ���ʾ��--��һ�����ݣ���ȷ��------------------"<<endl;
	test(s2,'C','G','F');
}
