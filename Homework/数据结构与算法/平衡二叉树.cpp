#include <iostream>
using namespace std;

typedef int elemtype;
typedef struct node {
    elemtype data;
    struct node* lchild;
    struct node* rchild;
    int height;
    int bf;  // ƽ�����ӣ��������߶� - �������߶ȣ�
} BTnode;

int flag = 0;  //����Ƿ��������ת���������������ʾ��

int max(int a, int b) {
    return (a > b ? a : b);
}

// �ݹ��ӡ�������ṹ�����������
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

// �ݹ��ӡ���ڵ�ƽ�����ӣ����������
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

//�����½ڵ㲢��ʼ��
BTnode* NewNode(int data) {
    BTnode* node = new BTnode;
    node->data = data;
    node->height = 1;
    node->lchild = node->rchild = nullptr;
    node->bf = 0;
    return node;
}

// ��ȡ�ڵ�߶ȣ��սڵ�߶�Ϊ0��
int GetHeight(BTnode* T) {
    if (T == nullptr)
        return 0;
    return T->height;
}

//���½ڵ�߶Ⱥ�ƽ�����ӣ������ӽڵ㣩
void updateNode(BTnode* T) {
    if (T != nullptr) {
        T->height = 1 + max(GetHeight(T->lchild), GetHeight(T->rchild));
        T->bf = GetHeight(T->lchild) - GetHeight(T->rchild);
    }
}

// ��ȡ�ڵ�ƽ�����ӣ��սڵ�ƽ������Ϊ0��
int GetBalanceFactor(BTnode* T) {
    if (T == nullptr)
        return 0;
    return T->bf;
}

/*
����ת��LL�͵���������y������x����Ϊ�¸�
         y                   x
        / \                 / \
       x   b       ->      a   y
      / \                     / \
     a   xr                 xr   b
*/
BTnode* RightRotate(BTnode* y) {
    flag = 1;  // ��Ƿ�����ת
    BTnode* x = y->lchild;
    BTnode* xr = x->rchild;

    y->lchild = xr;  // x��������xr��Ϊy��������
    x->rchild = y;   // y��Ϊx��������

    updateNode(y);  // �ȸ����²�ڵ�y�ĸ߶Ⱥ�ƽ������
    updateNode(x);  // �ٸ����ϲ�ڵ�x�ĸ߶Ⱥ�ƽ������
    return x;       // �����µ��������ڵ�x
}

/*
����ת��RR�͵���������y���Һ���x����Ϊ�¸�
         y                   x
        / \                 / \
       a   x       ->      y   b
          / \             / \
        xl   b           a   xl
*/
BTnode* LeftRotate(BTnode* y) {
    flag = 1;  // ��Ƿ�����ת
    BTnode* x = y->rchild;
    BTnode* xl = x->lchild;

    y->rchild = xl;  // x��������xl��Ϊy��������
    x->lchild = y;   // y��Ϊx��������

    updateNode(y);  // �ȸ����²�ڵ�y�ĸ߶Ⱥ�ƽ������
    updateNode(x);  // �ٸ����ϲ�ڵ�x�ĸ߶Ⱥ�ƽ������
    return x;       // �����µ��������ڵ�x
}

//�����ڵ㣨������ƽ�⣬�����¸߶ȣ�
BTnode* Insert(BTnode* node, int data) {
    if (node == nullptr)
        return NewNode(data);  // �����½ڵ�
    if (data < node->data)
        node->lchild = Insert(node->lchild, data);  // �ݹ����������
    else if (data > node->data)
        node->rchild = Insert(node->rchild, data);  // �ݹ����������
    else
        return node;  // �����Ѵ��ڣ����ظ�����
    updateNode(node);  // �������µ�ǰ�ڵ�߶Ⱥ�ƽ������
    return node;
}

//�ݹ����ڵ㲢����ƽ�⣨��������ʧ�������
BTnode* Insert_AND_Balance(BTnode* node, int data) {
    if (node == nullptr)
        return NewNode(data);
    if (data < node->data)
        node->lchild = Insert_AND_Balance(node->lchild, data);
    else if (data > node->data)
        node->rchild = Insert_AND_Balance(node->rchild, data);
    else
        return node;
    updateNode(node);  // �������µ�ǰ�ڵ�߶Ⱥ�ƽ������

    int bf=GetBalanceFactor(node);   
    //LL��
    if(bf>1 && data<node->lchild->data){
        printf("���%dʧ��,����LL�͵���...\n",node->data);
        /*
        LL��:NL��NR���������㣬�����Ϊ��node������ΪNR��һ��
                   node                    NL
                  /    \                 /    \
                NL      NR             NLL     node
               /  \                   /   \    /  \
             NLL  NLR           ->  NLLL NLLR NLR  NR  
            /  \                 
          NLLL NLLR                        
        */  
        return RightRotate(node);           //LL/LR��:����Ҫ��ת
    }
    //RR��:��������LL��
    if(bf<-1 && data>node->rchild->data){
        printf("���%dʧ��,����RR�͵���...\n",node->data);
        return LeftRotate(node);           //R-��:����Ҫ��ת
    }
    //LR��:
    if(bf>1 && data>node->lchild->data){
        printf("���%dʧ��,����LR�͵���...\n",node->data);
        /*
        LR��:��LL�Ͷ�һ������Ҫ�Ƚ�LR�ͱ��LL��
                 node                      node
                /    \                    /    \
              NL      NR      ->        NLR     NR
             /  \                      /  \  
           NLL  NLR                  NL   data
                   \                 /   
                   data           NLL    
        */
        node->lchild=LeftRotate(node->lchild);  
        return RightRotate(node);               //����ת
    }
    //RL��:
    if(bf<-1 && data<node->rchild->data){
        printf("���%dʧ��,����RL�͵���...\n",node->data);
        //��������LR�ͣ��Ƚ�RL�ͱ��RR�ͣ�����ת
    	node->rchild=RightRotate(node->rchild);  //����ת
        return LeftRotate(node);                //����ת
    }
    return node;                       //�ý��ƽ�⣬��������
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
        /*  �ҵ�Ҫɾ���Ľڵ�
        ���������ӽڵ�Ľڵ㣬�ҵ�����������С�ڵ�temp������left<temp<right��������ת��Ϊɾ��ֻ��һ�����ӽڵ��û���ӽڵ�Ľڵ�
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
        if (root->lchild != nullptr && root->rchild != nullptr) {  // �ڵ��������ӽڵ�
            BTnode* temp = root->rchild;
            while (temp->lchild!= nullptr) {  // �ҵ�����������С�ڵ�
                temp = temp->lchild;
            }
            root->data = temp->data;  // ������������С�ڵ��滻��ǰ�ڵ�
            root->rchild = DeleteNode(root->rchild, temp->data);  // ɾ������������С�ڵ�
        }
        /*
        ����һ����/���ӽڵ�Ľڵ㣬ֱ���ø��ӽڵ��滻��ǰ�ڵ�
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
        else {  // �ڵ�ֻ��һ���ӽڵ��û���ӽڵ�
            BTnode* temp = root->lchild ? root->lchild : root->rchild;
            if(temp==nullptr){  // û���ӽڵ�
                temp = root;
                root = nullptr;
            }
            else{  // ֻ��һ���ӽڵ�
                *root = *temp;  // ���ӽڵ��滻��ǰ�ڵ�
            }
            delete temp;  // ɾ���ڵ�
        }
    }
    //ɾ����˫�ӽڵ�Ľڵ�󣬿��ܳ���rootΪ�յ��������ʱֱ�ӷ���nullptr
    if (root == nullptr) return root;
    updateNode(root);  // ���½ڵ�߶Ⱥ�ƽ������
    int bf=GetBalanceFactor(root);
    //LL��  
    if(bf>1 && GetBalanceFactor(root->lchild)>=0){
        return RightRotate(root);
    } 
    //RR��
    if(bf<-1 && GetBalanceFactor(root->rchild)<=0){
        return LeftRotate(root);
    }       
    //LR��
    if(bf>1 && GetBalanceFactor(root->lchild)<0){
        root->lchild=LeftRotate(root->lchild);
        return RightRotate(root);
    }
    //RL��
    if(bf<-1 && GetBalanceFactor(root->rchild)>0){
        root->rchild=RightRotate(root->rchild);
        return LeftRotate(root);
    }
    return root;
}

int test1() {
    cout<<"����ƽ�������\n";
    BTnode* root = nullptr;
    BTnode* temp = nullptr;
    int arr[] = {16, 3, 7, 11, 9, 26, 18, 14, 15};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        cout << "����" << arr[i] << endl;
        root = Insert(root, arr[i]);
        cout << "���ƽ�������";
        showTree(root);
        cout << endl;
        cout << "���ڵ�ƽ������Ϊ:";
        showTreeBF(root);
        cout << endl << endl;

        temp = Insert_AND_Balance(root, arr[i]);
        root = temp;
        if (flag == 1) {
            cout << "���ƽ�������";
            showTree(temp);
            cout << endl;
            cout << "���ڵ�ƽ������Ϊ:";
            showTreeBF(temp);
            cout << endl << endl;
            flag = 0;  // ������ת���
        }
    }
    cout<<"������Ҫɾ���Ľڵ�:";
    int num;
    while(cin>>num){
        root=DeleteNode(root,num);
        cout<<"ɾ���ɹ���\n";
        cout<<"���ƽ�������";showTree(root);cout << endl;
        cout << "���ڵ�ƽ������Ϊ:";showTreeBF(root);cout << endl << endl;
        cout<<"������Ҫɾ���Ľڵ�:";
    }
    return 0;
}

int test2() {
    cout<<"����ƽ�������\n";
    BTnode* root = nullptr;
    BTnode* temp = nullptr;
    int arr[] = {4,7,6,1,0,5,8,9};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++) {
        cout << "����" << arr[i] << endl;
        root = Insert(root, arr[i]);
        cout << "���ƽ�������";
        showTree(root);
        cout << endl;
        cout << "���ڵ�ƽ������Ϊ:";
        showTreeBF(root);
        cout << endl << endl;

        temp = Insert_AND_Balance(root, arr[i]);
        root = temp;
        if (flag == 1) {
            cout << "���ƽ�������";
            showTree(temp);
            cout << endl;
            cout << "���ڵ�ƽ������Ϊ:";
            showTreeBF(temp);
            cout << endl << endl;
            flag = 0;  // ������ת���
        }
    }
    cout<<"������Ҫɾ���Ľڵ�:";
    int num;
    while(cin>>num){
        root=DeleteNode(root,num);
        cout<<"ɾ���ɹ���\n";
        cout<<"���ƽ�������";showTree(root);cout << endl;
        cout << "���ڵ�ƽ������Ϊ:";showTreeBF(root);cout << endl << endl;
        cout<<"������Ҫɾ���Ľڵ�:";
    }
    return 0;
}

int main() {
    test1();  
    // test2();
    return 0;
}