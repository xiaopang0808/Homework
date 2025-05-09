#include <iostream>
using namespace std;

typedef char Elemtype;

typedef struct Lnode {
    Elemtype data;         // 数据域
    struct Lnode *next;    // 指针域，指向后继节点
} Linklist;

//初始化
void Initlist(Linklist *&L) {
    L = new Linklist;      
    L->next = L;          // 形成空环结构
}

//输出链表
void outputlist(Linklist *L) {
    if (L->next == L) {   // 空链表检测
        cout << "链表为空" << endl;
        return;
    }
    Linklist *p = L->next; 
    do {
        cout << p->data << ' ';
        p = p->next;
    } while (p != L->next); // 循环终止条件：回到起始节点
    cout << endl;
}

//表长
void Listlen(Linklist *L, int &len) {
    if (L->next == L) {   // 空链表处理
        len = 0;
        return;
    }
    len = 0;
    Linklist *p = L->next->next; // 从第二个节点开始计数
    while (p != L->next) { // 遍历整个环
        len++;
        p = p->next;
    }
}

//判断空表
bool Listempty(Linklist *L) {
    return L->next == L;  
}

//按位查找
bool GetElem(Linklist *L, int pos, Elemtype &e) {
    int len;
    Listlen(L, len);
    if (pos < 1 || pos > len) return false;  // 有效性检查

    Linklist *p = L->next; // 指向第一个数据节点
    for (int j = 1; j < pos; j++) // 移动到目标位置
        p = p->next;
    e = p->data;          // 获取元素值
    return true;
}

//按值查找
bool LocateElem(Linklist *L, int &pos, Elemtype e) {
    if (L->next == L) {   // 空链表直接返回
        pos = 0;
        return false;
    }
    Linklist *p = L->next;
    pos = 1;
    do {  // 遍历整个环
        if (p->data == e)
            return true;
        p = p->next;
        pos++;
    } while (p != L->next);
    pos = 0;              // 未找到重置位置
    return false;
}

//插入
bool InsertElem(Linklist *&L, int pos, Elemtype e) {
    if (pos < 1) return false;

    int len;
    Listlen(L, len);
    if (pos > len + 1) return false; // 插入位置不能超过长度+1

    Linklist *p = L;      // 从头节点开始
    for (int j = 0; j < pos - 1; j++) // 移动到插入位置前驱
        p = p->next;

    // 创建并插入新节点
    Linklist *temp = new Linklist;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return true;
}

//删除
bool DeleteElem(Linklist *&L, int pos, Elemtype &e) {
    int len;
    Listlen(L, len);
    if (pos < 1 || pos > len) return false;  // 有效性检查

    Linklist *p = L;      // 从头节点开始
    for (int j = 0; j < pos - 1; j++) // 移动到删除位置前驱
        p = p->next;

    Linklist *temp = p->next; // 记录被删节点
    e = temp->data;       // 保存被删元素值
    p->next = temp->next; // 跳过被删节点
    delete temp;          // 释放内存
    return true;
}

//清空链表
void Clearlist(Linklist *&L) {
    Linklist *current = L->next; // 第一个数据节点
    while (current != L) {       // 遍历所有数据节点
        Linklist *nextNode = current->next;
        delete current;         // 释放当前节点
        current = nextNode;
    }
    L->next = L;                // 重置头节点指针
}

//销毁
void DestroyList(Linklist *&L) {
    Clearlist(L);    // 清空数据节点
    delete L;        // 释放头节点
    L = NULL;        // 防止野指针
}

int main() {
    Linklist *L;
    Initlist(L);     // 初始化循环链表

    // 测试插入功能
    InsertElem(L, 1, 'A');
    InsertElem(L, 2, 'B');
    InsertElem(L, 3, 'C');
    InsertElem(L, 4, 'D');
    InsertElem(L, 5, 'E');

    cout << "输出链表：";
    outputlist(L);   
    cout << endl;

    int len;
    Listlen(L, len);
    cout << "链表的长度为：" << len << endl << endl;  

    if (Listempty(L))
        cout << "链表为空" << endl << endl;
    else
        cout << "链表不为空" << endl << endl;

    int pos1;
    Elemtype e1;
    cout << "请输入想获取的元素的位置：";
    cin >> pos1;
    if (GetElem(L, pos1, e1)) {
        cout << "位置" << pos1 << "的元素为：" << e1 << endl;
    } else {
        cout << "输入错误！访问越界" << endl;
    }
    cout << endl;

    int pos2;
    Elemtype e2;
    cout << "请输入想定位的元素值：";
    cin >> e2;
    if (LocateElem(L, pos2, e2)) {
        cout << e2 << "位于位置" << pos2 << endl;
    } else {
        cout << "未找到元素" << e2 << endl;
    }
    cout << endl;

    int pos3;
    Elemtype e3;
    cout << "请输入插入元素的值：";
    cin >> e3;
    cout << "请输入插入元素的位置：";
    cin >> pos3;
    if (InsertElem(L, pos3, e3)) {
        cout << "插入成功，当前链表：";
        outputlist(L);
    } else {
        cout << "输入错误！访问越界" << endl;
    }
    cout << endl;

    int pos4;
    Elemtype e4;
    cout << "请输入删除元素的位置：";
    cin >> pos4;
    if (DeleteElem(L, pos4, e4)) {
        cout << e4 << "已删除，当前链表：";
        outputlist(L);
    } else {
        cout << "删除失败！访问越界" << endl;
    }
    cout << endl;

    Clearlist(L);
    cout << "链表已清空" << endl << endl;

    if (Listempty(L))
        cout << "链表为空" << endl << endl;
    else
        cout << "链表不为空" << endl << endl;

    DestroyList(L);
    cout << "链表已销毁" << endl << endl;
    return 0;
}
