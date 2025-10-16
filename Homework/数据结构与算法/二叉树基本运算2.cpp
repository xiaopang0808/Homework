#include<bits/stdc++.h>
using namespace std;
int len=40;         //�����ʾ���������

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

/* �������*/
void PreDisp(BTnode *T){
    if(!T){ cout<<'^'; return; }
    cout<<T->data;      //��������ڵ�
    PreDisp(T->lchild); //���ȱ���������
    PreDisp(T->rchild);
}

/* �������*/
void InOrder(BTnode *T){
    if(!T){ cout<<'^'; return; }
    InOrder(T->lchild);
    cout<<T->data;      //�ȱ�����������������ڵ�
    InOrder(T->rchild);
}

/* �������*/
void PostOrder(BTnode *T){
    if(!T){ cout<<'^'; return; }
    PostOrder(T->lchild);
    PostOrder(T->rchild);
    cout<<T->data;      //�ȱ���������������������ڵ�
}

/* ��α���*/
void PrefaceDisp(BTnode *T){
    queue<BTnode*> q;
    q.push(T);
    // �����սڵ���
    BTnode *temp=new BTnode{'^'};
    while(!q.empty()){  //�����������������չ��
        BTnode *new_node=q.front();
        cout<<new_node->data;
        q.pop();
        // ������ǽڵ㲻�����ӽڵ�
        if(new_node->data=='^') continue;
        // �ӽڵ㴦���սڵ���^����
        q.push(new_node->lchild?new_node->lchild:temp);
        q.push(new_node->rchild?new_node->rchild:temp);
    }
}

/*���������*/
void Pre_In_Disp(BTnode *T,int deep,char name){
	if(T==NULL) return ;
	int Tab=3;          //��������
	int pos=deep*Tab-2;     //�������ַ�λ��
	for(int i=1;i<=len;i++){    //��ȫʣ���ַ�
		if(i<pos) cout<<' ';
		else if(i==pos) cout<<T->data;
		else{
			if(i==len) cout<<name<<endl;    //β�ַ�����������
			else cout<<'=';
		}
	}
	Pre_In_Disp(T->lchild,deep+1,'L');  //�ݹ���������
	Pre_In_Disp(T->rchild,deep+1,'R');
}
/*�����������������--���ƣ�����׸��*/
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

/*�����������������--���ƣ�����׸��*/
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

/*��ת����������������������*/
BTnode* MirrorTree(BTnode *T){
	if(T==NULL) return NULL;
	BTnode *temp=new BTnode;
	temp=MirrorTree(T->lchild);
	T->lchild=MirrorTree(T->rchild);
	T->rchild=temp;
	return T;
}

//ʹ��ȫ�ֱ������������
int max_distance = 0;       
BTnode* max_nodeA = NULL;
BTnode* max_nodeB = NULL;

struct Result {
    int depth;      //��ǰ�������
    BTnode* deepest;    //��ǰ����������
};

Result Farthest_node(BTnode* T) {
    if (T==NULL) return {0,NULL};   //�ս��
    Result left=Farthest_node(T->lchild);   //�ݹ�������������Ϣ
    Result right=Farthest_node(T->rchild);

    int now_deep=1+max(left.depth, right.depth);    //�������Ϊ��������������+1

    // ȷ����ǰ����������Ҷ�ڵ�
    BTnode* now_deepest_node=new BTnode;
    if (left.depth>right.depth) {
        now_deepest_node = left.deepest;    //�̳�����������ڵ�
    } else if (right.depth > left.depth) {
        now_deepest_node = right.deepest;   // ����������̳�����������ڵ�
    } else {
        /*
            ������������������ֱ�Ϊ�գ���Ϊ��
		*/
        if (left.deepest)
            now_deepest_node = left.deepest;
        else if (right.deepest)
            now_deepest_node = right.deepest;
        else
            now_deepest_node = T;            //Ҷ�ӽ��
    }
    // ���㾭����ǰ�ڵ���·��������� + ����ȣ�
    int now_max = left.depth + right.depth;

    if (now_max > max_distance) {
        max_distance = now_max;
        // ������������ڵ�
        max_nodeA = (left.deepest != NULL) ? left.deepest : T;
        // ������������ڵ�
        max_nodeB = (right.deepest != NULL) ? right.deepest : T;
    }
    // ���ص�ǰ������Ϣ��
    return {now_deep, now_deepest_node};
}

int main(){
	string s="A(B(D(,G)),C(E,F))";
	BTnode *T;
	Creat_tree(T,s);
 	cout<<"�������:";PreDisp(T);cout<<endl;
 	cout<<"�������:";InOrder(T);cout<<endl;
 	cout<<"�������:";PostOrder(T);cout<<endl;
 	cout<<"��α���:";PrefaceDisp(T);cout<<endl;
 	cout<<"�������ʾ��:"<<endl;
 	Pre_In_Disp(T,1,'B');
 	cout<<"�������ʾ��:"<<endl;
 	InOrder_In_Disp(T,1,'B');
 	cout<<"�������ʾ��:"<<endl;
 	Post_In_Disp(T,1,'B');
 	BTnode *B=MirrorTree(T);
    cout<<"������:";showTree(B);cout<<endl;
    Farthest_node(T);
    cout<<"�����Զ���������Ϊ:"<<max_nodeA->data<<"��"<< max_nodeB->data << endl;
    return 0;
}
