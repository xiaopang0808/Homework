#include <iostream>
#define MAXSIZE 40  // 定义队列的最大容量，实际可用大小为MAXSIZE-1

using namespace std;

typedef char ElemType;

typedef struct {
    ElemType data[MAXSIZE];
    int front;               // 队首指针
    int rear;                // 队尾指针
} CircularQueue;

void InitQueue(CircularQueue*& q) {
    q = new CircularQueue;
    q->front = q->rear = 0;  // 初始时队首和队尾都指向0
}

bool IsEmpty(CircularQueue* q) {
    return q->front == q->rear;
}

bool Enqueue(CircularQueue*& q, ElemType elem) {
    if ((q->rear + 1) % MAXSIZE == q->front) {  // 队列已满
        return false;
    }
    q->data[q->rear] = elem;
    q->rear = (q->rear + 1) % MAXSIZE;  // 循环后移
    return true;
}

bool Dequeue(CircularQueue*& q, ElemType& elem) {
    if (IsEmpty(q)) {  // 队列为空
        return false;
    }
    elem = q->data[q->front];
    q->front = (q->front + 1) % MAXSIZE;  // 循环后移
    return true;
}

void DestroyQueue(CircularQueue*& q) {
    delete q;
    q = nullptr;  // 避免野指针
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

    // 测试队列是否为空
    if (IsEmpty(q)) {
        cout << "队列为空" << endl;
    } else {
        cout << "队列非空" << endl;
    }

    // 第一组元素入队测试
    ElemType a[] = "abc";
    for (int i = 0; i < 3; i++) {
        if (Enqueue(q, a[i])) {
            cout << a[i] << " 入队成功" << endl;
        } else {
            cout << a[i] << " 入队失败（队列已满）" << endl;
        }
    }

    // 队首元素出队测试
    ElemType e1;
    if (Dequeue(q, e1)) {
        cout << "队首元素 " << e1 << " 出队" << endl;
    } else {
        cout << "出队失败（队列为空）" << endl;
    }

    // 第二组元素入队测试
    ElemType b[] = "def";
    for (int i = 0; i < 3; i++) {
        if (Enqueue(q, b[i])) {
            cout << b[i] << " 入队成功" << endl;
        } else {
            cout << b[i] << " 入队失败（队列已满）" << endl;
        }
    }

    // 遍历输出队列剩余元素
    ElemType e2;
    cout << "队列剩余元素：";
    while (!IsEmpty(q)) {
        Dequeue(q, e2);
        cout << e2 << ' ';
    }
    cout << endl;

    // 销毁队列
    DestroyQueue(q);

    return 0;
}
//int main() {
//    CircularQueue* q;
//    InitQueue(q);
//    change(q,2,0.635);
//
//	ElemType e;
//	cout<<"0.635转二进制：0.";
//	while(!IsEmpty(q)){
//	Dequeue(q,e);
//		cout<<e;
//	}cout<<endl;
//	
//	InitQueue(q);
//	change(q,29,0.1234567);
//   	cout<<"0.1234567转29进制：0.";
//	while(!IsEmpty(q)){
//	Dequeue(q,e);
//		cout<<e;
//	}cout<<endl;
//
//    return 0;
//}
