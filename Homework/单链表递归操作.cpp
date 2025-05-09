#include<bits/stdc++.h>
using namespace std;

typedef int elemtype;
typedef struct Lnode{
	elemtype data;
	struct Lnode *next;
}ListLink;
//插入数据
ListLink* insert(ListLink *&head,elemtype data){
	if(head==NULL){
		ListLink* new_node=new ListLink;
		new_node->data=data;
		new_node->next=NULL;
		return new_node;
	}
	head->next=insert(head->next,data);
	return head;
}
//正向输出
void cout_forward(ListLink *head){
	if(head!=NULL){
		cout<<head->data<<' ';
		cout_forward(head->next);
	}
}
//逆向输出
void cout_backward(ListLink *head){
	if(head!=NULL){
		cout_forward(head->next);
		cout<<head->data<<' ';
	}
}
//统计结点数
int count(ListLink* head){
	if(head!=NULL){
		return count(head->next)+1;
	}
}
//输出k结点值
elemtype get_kth_val(ListLink* head, elemtype k) {
    if (head==NULL || k==0) {
        return -1; // 表示错误情况
    }
    if (k==1) {
        return head->data;
    }
    return get_kth_val(head->next, k - 1);
}
//在第k个位置插入e
ListLink* insert_e_at_k(ListLink* head, int k, int e) {
    if (k==1) {
        ListLink* new_node=new ListLink;
        new_node->data=e;
        new_node->next=head;
        return new_node;
    }
    if (head==NULL) {
        cout<<"错误：k值超出链表长度"<<endl;
        return head;
    }
    head->next=insert_e_at_k(head->next, k - 1, e);
    return head;
}
// 删除第k个结点
ListLink* delete_kth(ListLink* head, int k) {
    if (head==NULL) {
        cout<<"错误：k值超出链表长度"<<endl;
        return head;
    }
    if (k==1) {
        ListLink* temp=head;
        head=head->next;
        delete temp;
        return head;
    }
    head->next=delete_kth(head->next, k - 1);
    return head;
}
// 删除值为X的数据结点
ListLink* delete_e(ListLink* head, int e) {
    if (head==NULL) {
        return head;
    }
    if (head->data == e) {
        ListLink* temp = head;
        head = head->next;
        delete temp;
        return delete_e(head, e);
    }
    head->next = delete_e(head->next, e);
    return head;
}
// 输出该链表的最大值
int find_max(ListLink* head) {
    if (head==NULL) {
        return -9999; // 假设最小值
    }
    int max=find_max(head->next);
    return (head->data>max)?head->data:max;
}
// 输出该链表的最小值
int find_min(ListLink* head) {
    if (head==NULL) {
        return 9999; // 假设最大值
    }
    int min=find_min(head->next);
    return (head->data<min)?head->data:min;
}
// 查找值为X的数据结点在当前链表出现的位置
int find_e(ListLink* head, int e, int pos) {
    if (head == NULL) {
        return -1; // 表示未找到
    }
    if (head->data == e) {
        return pos;
    }
    return find_e(head->next, e, pos + 1);
}
// 销毁该链表
void destroy_list(ListLink* head) {
    if (head!=NULL) {
        destroy_list(head->next);
        delete head;
    }
}
int main(){
	ListLink* head=NULL;
	int data[]={13,15,8,4,8,3,4,8};
	for(int i=0;i<8;i++) head=insert(head,data[i]);
	cout<<"正向输出:";cout_forward(head);cout<<endl;
	cout<<"逆向输出:";cout_backward(head);cout<<endl;
	cout<<"结点数:"<<count(head)<<endl;
	int k;cout<<"输入k:";cin>>k;
    int kth_value = get_kth_val(head, k);
    if (kth_value == -1) {
		cout<<"错误：k值超出链表长度"<<endl;
    } else {
        cout<<k<<"结点值为"<<kth_value<<endl;
    }
    int e;cout<<"输入k e:";cin>>k>>e;
    head=insert_e_at_k(head,k,e);
    cout<<"正向输出:";cout_forward(head);cout<<endl;
	cout<<"输入k:";cin>>k;
	head=delete_kth(head,k);
	cout<<"正向输出:";cout_forward(head);cout<<endl;
	cout<<"输入e:";cin>>e;
    head = delete_e(head, e);
    printf("删除值为 %d 的节点后正向输出: ", e);
    cout<<"正向输出:";cout_forward(head);cout<<endl;
    cout<<"输入e:";cin>>e;
    head = delete_e(head, e);
   	cout<<"删除所有值为"<<e<<"的节点后正向输出: ";cout_forward(head);cout<<endl;
    cout<<"链表的最大值:"<<find_max(head)<<endl;
    cout<<"链表的最小值:"<<find_min(head)<<endl;
	cout<<"输入x:";cin>>e;
    int pos = find_e(head, e, 1);
    if (pos == -1) {
        cout<<"值为"<<e<<"的节点未找到"<<endl;
    } else {
        cout<<"值为"<<e<<"的节点出现在位置:"<<pos<<endl;
    }
    destroy_list(head);
	return 0;
}
