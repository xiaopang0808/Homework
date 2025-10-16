#include <iostream>
using namespace std;

typedef int elemtype;
typedef struct node {
    elemtype data;
    struct node* lchild;
    struct node* rchild;
    int height;
    int bf;  // 平衡因子（左子树高度 - 右子树高度）
} BTnode;

int flag = 0;  //标记是否进行了旋转操作（用于输出提示）

int max(int a, int b) {
    return (a > b ? a : b);
}

// 递归打印二叉树结构（先序遍历）
void showTree(BTnode* T) {
    if (T == NULL) return;
    cout << T->data;
    if (T->lchild != NULL || T->rchild != NULL) {
        cout << '(';
        showTree(T->lchild);
        if (T->rchild != NULL) {
            cout << ',';
            showTree(T->rchild);
        }
        cout << ')';
    }
}

// 递归打印各节点平衡因子（先序遍历）
void showTreeBF(BTnode* T) {
    if (T == NULL) return;
    cout << T->bf;
    if (T->lchild != NULL || T->rchild != NULL) {
        cout << '(';
        showTreeBF(T->lchild);
        if (T->rchild != NULL) {
            cout << ',';
            showTreeBF(T->rchild);
        }
        cout << ')';
    }
}

//创建新节点并初始化
BTnode* NewNode(int data) {
    BTnode* node = new BTnode;
    node->data = data;
    node->height = 1;
    node->lchild = node->rchild = nullptr;
    node->bf = 0;
    return node;
}

// 获取节点高度（空节点高度为0）
int GetHeight(BTnode* T) {
    if (T == nullptr)
        return 0;
    return T->height;
}

//更新节点高度和平衡因子（基于子节点）
void updateNode(BTnode* T) {
    if (T != nullptr) {
        T->height = 1 + max(GetHeight(T->lchild), GetHeight(T->rchild));
        T->bf = GetHeight(T->lchild) - GetHeight(T->rchild);
    }
}

// 获取节点平衡因子（空节点平衡因子为0）
int GetBalanceFactor(BTnode* T) {
    if (T == nullptr)
        return 0;
    return T->bf;
}

/*
右旋转（LL型调整）：将y的左孩子x提升为新根
         y                   x
        / \                 / \
       x   b       ->      a   y
      / \                     / \
     a   xr                 xr   b
*/
BTnode* RightRotate(BTnode* y) {
    flag = 1;  // 标记发生旋转
    BTnode* x = y->lchild;
    BTnode* xr = x->rchild;

    y->lchild = xr;  // x的右子树xr成为y的左子树
    x->rchild = y;   // y成为x的右子树

    updateNode(y);  // 先更新下层节点y的高度和平衡因子
    updateNode(x);  // 再更新上层节点x的高度和平衡因子
    return x;       // 返回新的子树根节点x
}

/*
左旋转（RR型调整）：将y的右孩子x提升为新根
         y                   x
        / \                 / \
       a   x       ->      y   b
          / \             / \
        xl   b           a   xl
*/
BTnode* LeftRotate(BTnode* y) {
    flag = 1;  // 标记发生旋转
    BTnode* x = y->rchild;
    BTnode* xl = x->lchild;

    y->rchild = xl;  // x的左子树xl成为y的右子树
    x->lchild = y;   // y成为x的左子树

    updateNode(y);  // 先更新下层节点y的高度和平衡因子
    updateNode(x);  // 再更新上层节点x的高度和平衡因子
    return x;       // 返回新的子树根节点x
}

//归插入节点（不处理平衡，仅更新高度）
BTnode* Insert(BTnode* node, int data) {
    if (node == nullptr)
        return NewNode(data);  // 插入新节点
    if (data < node->data)
        node->lchild = Insert(node->lchild, data);  // 递归插入左子树
    else if (data > node->data)
        node->rchild = Insert(node->rchild, data);  // 递归插入右子树
    else
        return node;  // 数据已存在，不重复插入
    updateNode(node);  // 插入后更新当前节点高度和平衡因子
    return node;
}

//递归插入节点并调整平衡（处理四种失衡情况）
BTnode* Insert_AND_Balance(BTnode* node, int data) {
    if (node == nullptr)
        return NewNode(data);
    if (data < node->data)
        node->lchild = Insert_AND_Balance(node->lchild, data);
    else if (data > node->data)
        node->rchild = Insert_AND_Balance(node->rchild, data);
    else
        return node;
    updateNode(node);  // 插入后更新当前节点高度和平衡因子

    int bf=GetBalanceFactor(node);   
    //LL型
    if(bf>1 && data<node->lchild->data){
        printf("结点%d失衡,进行LL型调整...\n",node->data);
        /*
        LL型:NL比NR多至少两层，可理解为将node降级成为NR的一层
                   node                    NL
                  /    \                 /    \
                NL      NR             NLL     node
               /  \                   /   \    /  \
             NLL  NLR           ->  NLLL NLLR NLR  NR  
            /  \                 
          NLLL NLLR                        
        */  
        return RightRotate(node);           //LL/LR型:都需要右转
    }
    //RR型:过程类似LL型
    if(bf<-1 && data>node->rchild->data){
        printf("结点%d失衡,进行RR型调整...\n",node->data);
        return LeftRotate(node);           //R-型:都需要左转
    }
    //LR型:
    if(bf>1 && data>node->lchild->data){
        printf("结点%d失衡,进行LR型调整...\n",node->data);
        /*
        LR型:比LL型多一步，需要先将LR型变成LL型
                 node                      node
                /    \                    /    \
              NL      NR      ->        NLR     NR
             /  \                      /  \  
           NLL  NLR                  NL   data
                   \                 /   
                   data           NLL    
        */
        node->lchild=LeftRotate(node->lchild);  
        return RightRotate(node);               //再右转
    }
    //RL型:
    if(bf<-1 && data<node->rchild->data){
        printf("结点%d失衡,进行RL型调整...\n",node->data);
        //过程类似LR型，先将RL型变成RR型，再左转
    	node->rchild=RightRotate(node->rchild);  //先右转
        return LeftRotate(node);                //再左转
    }
    return node;                       //该结点平衡，不做处理
}

BTnode* DeleteNode(BTnode* root, int data) {
    if (root == nullptr) return root;
    if (data < root->data) {
        root->lchild = DeleteNode(root->lchild, data);
    }
    else if (data > root->data) {
        root->rchild = DeleteNode(root->rchild, data);
    }
    else {   
        /*  找到要删除的节点
        对于两个子节点的节点，找到右子树的最小节点temp，满足left<temp<right，将问题转换为删除只有一个右子节点或没有子节点的节点
               root                     temp
              /    \                   /    \
            left   right             left   right
                  /     \      ->          /     \
                ...     ...              ...     ...
                /                        /
              temp                     temp                         
             /   \                    /    \
          null   ...                null   ...
        */
        if (root->lchild != nullptr && root->rchild != nullptr) {  // 节点有两个子节点
            BTnode* temp = root->rchild;
            while (temp->lchild!= nullptr) {  // 找到右子树的最小节点
                temp = temp->lchild;
            }
            root->data = temp->data;  // 用右子树的最小节点替换当前节点
            root->rchild = DeleteNode(root->rchild, temp->data);  // 删除右子树的最小节点
        }
        /*
        对于一个右/左子节点的节点，直接用该子节点替换当前节点
               root                     left
              /    \                   /    \
            left   right     ->      left   right
                  /     \                  /     \
                ...     ...              ...     ...
                /                        /
              temp                     temp
             /   \                    /    \
          null   ...                null    ...
        */
        else {  // 节点只有一个子节点或没有子节点
            BTnode* temp = root->lchild ? root->lchild : root->rchild;
            if(temp==nullptr){  // 没有子节点
                temp = root;
                root = nullptr;
            }
            else{  // 只有一个子节点
                *root = *temp;  // 用子节点替换当前节点
            }
            delete temp;  // 删除节点
        }
    }
    //删除非双子节点的节点后，可能出现root为空的情况，此时直接返回nullptr
    if (root == nullptr) return root;
    updateNode(root);  // 更新节点高度和平衡因子
    int bf=GetBalanceFactor(root);
    //LL型  
    if(bf>1 && GetBalanceFactor(root->lchild)>=0){
        return RightRotate(root);
    } 
    //RR型
    if(bf<-1 && GetBalanceFactor(root->rchild)<=0){
        return LeftRotate(root);
    }       
    //LR型
    if(bf>1 && GetBalanceFactor(root->lchild)<0){
        root->lchild=LeftRotate(root->lchild);
        return RightRotate(root);
    }
    //RL型
    if(bf<-1 && GetBalanceFactor(root->rchild)>0){
        root->rchild=RightRotate(root->rchild);
        return LeftRotate(root);
    }
    return root;
}

int test1() {
    cout<<"创建平衡二叉树\n";
    BTnode* root = nullptr;
    BTnode* temp = nullptr;
    int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        cout << "插入" << arr[i] << endl;
        root = Insert(root, arr[i]);
        cout << "输出平衡二叉树";
        showTree(root);
        cout << endl;
        cout << "各节点平衡因子为:";
        showTreeBF(root);
        cout << endl << endl;

        temp = Insert_AND_Balance(root, arr[i]);
        root = temp;
        if (flag == 1) {
            cout << "输出平衡二叉树";
            showTree(temp);
            cout << endl;
            cout << "各节点平衡因子为:";
            showTreeBF(temp);
            cout << endl << endl;
            flag = 0;  // 重置旋转标记
        }
    }
    cout<<"请输入要删除的节点:";
    int num;
    while(cin>>num){
        root=DeleteNode(root,num);
        cout<<"删除成功！\n";
        cout<<"输出平衡二叉树";showTree(root);cout << endl;
        cout << "各节点平衡因子为:";showTreeBF(root);cout << endl << endl;
        cout<<"请输入要删除的节点:";
    }
    return 0;
}

int test2() {
    cout<<"创建平衡二叉树\n";
    BTnode* root = nullptr;
    BTnode* temp = nullptr;
    int arr[] = {4,7,6,1,0,5,8,9};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        cout << "插入" << arr[i] << endl;
        root = Insert(root, arr[i]);
        cout << "输出平衡二叉树";
        showTree(root);
        cout << endl;
        cout << "各节点平衡因子为:";
        showTreeBF(root);
        cout << endl << endl;

        temp = Insert_AND_Balance(root, arr[i]);
        root = temp;
        if (flag == 1) {
            cout << "输出平衡二叉树";
            showTree(temp);
            cout << endl;
            cout << "各节点平衡因子为:";
            showTreeBF(temp);
            cout << endl << endl;
            flag = 0;  // 重置旋转标记
        }
    }
    cout<<"请输入要删除的节点:";
    int num;
    while(cin>>num){
        root=DeleteNode(root,num);
        cout<<"删除成功！\n";
        cout<<"输出平衡二叉树";showTree(root);cout << endl;
        cout << "各节点平衡因子为:";showTreeBF(root);cout << endl << endl;
        cout<<"请输入要删除的节点:";
    }
    return 0;
}

int main() {
    test1();  
    // test2();
    return 0;
}