#include<iostream>
using namespace std;

#define MAXSIZE 40

typedef char Elemtype;

typedef struct {
    Elemtype data[MAXSIZE];  
    int top;                 // ջ��ָ�루ָ����һ���ɲ���λ�ã�
} Stack;

// ��ʼ��ջ
void StackInit(Stack*& S) {
    S = new Stack;      // ��̬�����ڴ�
    S->top = 0;         // ��ʼ��ջ��ָ��Ϊ0����ջ��
}

// �ж�ջ�Ƿ�Ϊ��
bool StackEmpty(Stack* S) {
    return S->top == 0;  // ջ��ָ��Ϊ0��ʾ��ջ
}

// Ԫ����ջ
bool Push(Stack*& S, Elemtype e) {
    if (S->top >= MAXSIZE) return false;  // ջ���򷵻�false
    S->data[S->top++] = e;  // Ԫ�ش���ջ����ջ��ָ��+1
    return true;
}

// ��ȡջ��Ԫ�أ���������
bool Top(Stack* S, Elemtype& e) {
    if (S->top == 0) return false;      // ��ջ�򷵻�false
    e = S->data[S->top - 1];  // ͨ�����÷���ջ��Ԫ��
    return true;
}

// Ԫ�س�ջ
bool Pop(Stack*& S, Elemtype& e) {
    if (S->top == 0) return false;  // ��ջ�򷵻�false
    e = S->data[--S->top];  // ջ��ָ��-1������ԭջ��Ԫ��
    return true;
}

// ���ջ���ݣ���ջ����ջ�ף�
void Output(Stack* S) {
    cout << endl;
    if (S->top == 0) {
        cout << "ջΪ�գ��޷����" << endl;  // ��ջ��ʾ
        return;
    }
    Elemtype e;
   	while(Pop(S,e)){
		cout<<e<<' ';
	}
    cout << endl;
}

// ���ջ���߼���գ������ڴ棩
void Clear(Stack*& S) {
    S->top = 0;  // ջ��ָ����㣬�߼������
}

// ����ջ���ͷ��ڴ棩
void Distroy(Stack*& S) {
    delete S;      // �ͷŶ�̬�ڴ�
    S = nullptr;   // ָ���ÿգ���������ָ��
}

void change_and_output(int num,int jz){
	char enum_data[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	Stack *S;
	StackInit(S);
	cout<<num<<"��"<<jz<<"����Ϊ��";
	while(num){
		Push(S,enum_data[num%jz]);
		num/=jz;
	}
	Output(S);
	Distroy(S);
}

int main() {
    char s[] = "abcde"; 
    Stack* S;

    // ��ʼ��ջ
    StackInit(S);
    if (StackEmpty(S)) {
        cout << "ջΪ��" << endl;
    } else {
        cout << "ջ��Ϊ��" << endl;
    }

    // Ԫ����ջ
    for (int i = 0; i < 5; i++) {
        Push(S, s[i]);  // ����ѹ��a,b,c,d,e
    }
    if (StackEmpty(S)) {
        cout << "\nջΪ��" << endl;
    } else {
        cout << "\nջ��Ϊ��" << endl;
    }

    // ���ջ����
    Output(S);

    if (StackEmpty(S)) {
        cout << "\nջΪ��" << endl;
    } else {
        cout << "\nջ��Ϊ��" << endl;
    }

    // ����ջ
    Distroy(S);
    
    int num1;
    cout<<"\nʮ����ת�����ƣ�";cin>>num1;
    change_and_output(num1,2);
	cout<<"\nʮ����ת����36���ڽ���"<<endl;
	int num2,jz;
	cout<<"\n��:";cin>>num2;
	cout<<"\n���ƣ�";cin>>jz;
	change_and_output(num2,jz);
    return 0;
}
