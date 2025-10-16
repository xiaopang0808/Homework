#include<bits/stdc++.h>
using namespace std;

typedef int elemtype;
typedef struct Lnode{
	elemtype data;
	struct Lnode *next;
}ListLink;
//��������
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
//�������
void cout_forward(ListLink *head){
	if(head!=NULL){
		cout<<head->data<<' ';
		cout_forward(head->next);
	}
}
//�������
void cout_backward(ListLink *head){
	if(head!=NULL){
		cout_forward(head->next);
		cout<<head->data<<' ';
	}
}
//ͳ�ƽ����
int count(ListLink* head){
	if(head!=NULL){
		return count(head->next)+1;
	}
}
//���k���ֵ
elemtype get_kth_val(ListLink* head, elemtype k) {
    if (head==NULL || k==0) {
        return -1; // ��ʾ�������
    }
    if (k==1) {
        return head->data;
    }
    return get_kth_val(head->next, k - 1);
}
//�ڵ�k��λ�ò���e
ListLink* insert_e_at_k(ListLink* head, int k, int e) {
    if (k==1) {
        ListLink* new_node=new ListLink;
        new_node->data=e;
        new_node->next=head;
        return new_node;
    }
    if (head==NULL) {
        cout<<"����kֵ����������"<<endl;
        return head;
    }
    head->next=insert_e_at_k(head->next, k - 1, e);
    return head;
}
// ɾ����k�����
ListLink* delete_kth(ListLink* head, int k) {
    if (head==NULL) {
        cout<<"����kֵ����������"<<endl;
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
// ɾ��ֵΪX�����ݽ��
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
// �������������ֵ
int find_max(ListLink* head) {
    if (head==NULL) {
        return -9999; // ������Сֵ
    }
    int max=find_max(head->next);
    return (head->data>max)?head->data:max;
}
// ������������Сֵ
int find_min(ListLink* head) {
    if (head==NULL) {
        return 9999; // �������ֵ
    }
    int min=find_min(head->next);
    return (head->data<min)?head->data:min;
}
// ����ֵΪX�����ݽ���ڵ�ǰ������ֵ�λ��
int find_e(ListLink* head, int e, int pos) {
    if (head == NULL) {
        return -1; // ��ʾδ�ҵ�
    }
    if (head->data == e) {
        return pos;
    }
    return find_e(head->next, e, pos + 1);
}
// ���ٸ�����
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
	cout<<"�������:";cout_forward(head);cout<<endl;
	cout<<"�������:";cout_backward(head);cout<<endl;
	cout<<"�����:"<<count(head)<<endl;
	int k;cout<<"����k:";cin>>k;
    int kth_value = get_kth_val(head, k);
    if (kth_value == -1) {
		cout<<"����kֵ����������"<<endl;
    } else {
        cout<<k<<"���ֵΪ"<<kth_value<<endl;
    }
    int e;cout<<"����k e:";cin>>k>>e;
    head=insert_e_at_k(head,k,e);
    cout<<"�������:";cout_forward(head);cout<<endl;
	cout<<"����k:";cin>>k;
	head=delete_kth(head,k);
	cout<<"�������:";cout_forward(head);cout<<endl;
	cout<<"����e:";cin>>e;
    head = delete_e(head, e);
    printf("ɾ��ֵΪ %d �Ľڵ���������: ", e);
    cout<<"�������:";cout_forward(head);cout<<endl;
    cout<<"����e:";cin>>e;
    head = delete_e(head, e);
   	cout<<"ɾ������ֵΪ"<<e<<"�Ľڵ���������: ";cout_forward(head);cout<<endl;
    cout<<"��������ֵ:"<<find_max(head)<<endl;
    cout<<"�������Сֵ:"<<find_min(head)<<endl;
	cout<<"����x:";cin>>e;
    int pos = find_e(head, e, 1);
    if (pos == -1) {
        cout<<"ֵΪ"<<e<<"�Ľڵ�δ�ҵ�"<<endl;
    } else {
        cout<<"ֵΪ"<<e<<"�Ľڵ������λ��:"<<pos<<endl;
    }
    destroy_list(head);
	return 0;
}
