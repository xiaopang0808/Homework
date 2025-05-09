#include<iostream>
using namespace std;

#define MAXSIZE 40

typedef char Elemtype;

typedef struct {
    Elemtype data[MAXSIZE];  
    int top;                 // 栈顶指针（指向下一个可插入位置）
} Stack;

// 初始化栈
void StackInit(Stack*& S) {
    S = new Stack;      // 动态分配内存
    S->top = 0;         // 初始化栈顶指针为0（空栈）
}

// 判断栈是否为空
bool StackEmpty(Stack* S) {
    return S->top == 0;  // 栈顶指针为0表示空栈
}

// 元素入栈
bool Push(Stack*& S, Elemtype e) {
    if (S->top >= MAXSIZE) return false;  // 栈满则返回false
    S->data[S->top++] = e;  // 元素存入栈顶，栈顶指针+1
    return true;
}

// 获取栈顶元素（不弹出）
bool Top(Stack* S, Elemtype& e) {
    if (S->top == 0) return false;      // 空栈则返回false
    e = S->data[S->top - 1];  // 通过引用返回栈顶元素
    return true;
}

// 元素出栈
bool Pop(Stack*& S, Elemtype& e) {
    if (S->top == 0) return false;  // 空栈则返回false
    e = S->data[--S->top];  // 栈顶指针-1，返回原栈顶元素
    return true;
}

// 输出栈内容（从栈顶到栈底）
void Output(Stack* S) {
    cout << endl;
    if (S->top == 0) {
        cout << "栈为空，无法输出" << endl;  // 空栈提示
        return;
    }
    Elemtype e;
   	while(Pop(S,e)){
		cout<<e<<' ';
	}
    cout << endl;
}

// 清空栈（逻辑清空，保留内存）
void Clear(Stack*& S) {
    S->top = 0;  // 栈顶指针归零，逻辑上清空
}

// 销毁栈（释放内存）
void Distroy(Stack*& S) {
    delete S;      // 释放动态内存
    S = nullptr;   // 指针置空，避免悬空指针
}

void change_and_output(int num,int jz){
	char enum_data[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	Stack *S;
	StackInit(S);
	cout<<num<<"的"<<jz<<"进制为：";
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

    // 初始化栈
    StackInit(S);
    if (StackEmpty(S)) {
        cout << "栈为空" << endl;
    } else {
        cout << "栈不为空" << endl;
    }

    // 元素入栈
    for (int i = 0; i < 5; i++) {
        Push(S, s[i]);  // 依次压入a,b,c,d,e
    }
    if (StackEmpty(S)) {
        cout << "\n栈为空" << endl;
    } else {
        cout << "\n栈不为空" << endl;
    }

    // 输出栈内容
    Output(S);

    if (StackEmpty(S)) {
        cout << "\n栈为空" << endl;
    } else {
        cout << "\n栈不为空" << endl;
    }

    // 销毁栈
    Distroy(S);
    
    int num1;
    cout<<"\n十进制转二进制：";cin>>num1;
    change_and_output(num1,2);
	cout<<"\n十进制转任意36以内进制"<<endl;
	int num2,jz;
	cout<<"\n数:";cin>>num2;
	cout<<"\n进制：";cin>>jz;
	change_and_output(num2,jz);
    return 0;
}
