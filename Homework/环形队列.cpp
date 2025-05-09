#include <iostream>
#define MAXSIZE 40  // ������е����������ʵ�ʿ��ô�СΪMAXSIZE-1

using namespace std;

typedef char ElemType;

typedef struct {
    ElemType data[MAXSIZE];
    int front;               // ����ָ��
    int rear;                // ��βָ��
} CircularQueue;

void InitQueue(CircularQueue*& q) {
    q = new CircularQueue;
    q->front = q->rear = 0;  // ��ʼʱ���׺Ͷ�β��ָ��0
}

bool IsEmpty(CircularQueue* q) {
    return q->front == q->rear;
}

bool Enqueue(CircularQueue*& q, ElemType elem) {
    if ((q->rear + 1) % MAXSIZE == q->front) {  // ��������
        return false;
    }
    q->data[q->rear] = elem;
    q->rear = (q->rear + 1) % MAXSIZE;  // ѭ������
    return true;
}

bool Dequeue(CircularQueue*& q, ElemType& elem) {
    if (IsEmpty(q)) {  // ����Ϊ��
        return false;
    }
    elem = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;  // ѭ������
    return true;
}

void DestroyQueue(CircularQueue*& q) {
    delete q;
    q = nullptr;  // ����Ұָ��
}

void change(CircularQueue *&q,int jz,double num){
	char c[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int cnt=0;
	while(cnt++!=8 && num!=0){
		int temp=num*jz;
		Enqueue(q,c[temp]);
		num=num*jz-temp;
	}
}

int main() {
    CircularQueue* q;
    InitQueue(q);

    // ���Զ����Ƿ�Ϊ��
    if (IsEmpty(q)) {
        cout << "����Ϊ��" << endl;
    } else {
        cout << "���зǿ�" << endl;
    }

    // ��һ��Ԫ����Ӳ���
    ElemType a[] = "abc";
    for (int i = 0; i < 3; i++) {
        if (Enqueue(q, a[i])) {
            cout << a[i] << " ��ӳɹ�" << endl;
        } else {
            cout << a[i] << " ���ʧ�ܣ�����������" << endl;
        }
    }

    // ����Ԫ�س��Ӳ���
    ElemType e1;
    if (Dequeue(q, e1)) {
        cout << "����Ԫ�� " << e1 << " ����" << endl;
    } else {
        cout << "����ʧ�ܣ�����Ϊ�գ�" << endl;
    }

    // �ڶ���Ԫ����Ӳ���
    ElemType b[] = "def";
    for (int i = 0; i < 3; i++) {
        if (Enqueue(q, b[i])) {
            cout << b[i] << " ��ӳɹ�" << endl;
        } else {
            cout << b[i] << " ���ʧ�ܣ�����������" << endl;
        }
    }

    // �����������ʣ��Ԫ��
    ElemType e2;
    cout << "����ʣ��Ԫ�أ�";
    while (!IsEmpty(q)) {
        Dequeue(q, e2);
        cout << e2 << ' ';
    }
    cout << endl;

    // ���ٶ���
    DestroyQueue(q);

    return 0;
}
//int main() {
//    CircularQueue* q;
//    InitQueue(q);
//    change(q,2,0.635);
//
//	ElemType e;
//	cout<<"0.635ת�����ƣ�0.";
//	while(!IsEmpty(q)){
//	Dequeue(q,e);
//		cout<<e;
//	}cout<<endl;
//	
//	InitQueue(q);
//	change(q,29,0.1234567);
//   	cout<<"0.1234567ת29���ƣ�0.";
//	while(!IsEmpty(q)){
//	Dequeue(q,e);
//		cout<<e;
//	}cout<<endl;
//
//    return 0;
//}
