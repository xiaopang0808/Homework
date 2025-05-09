#include <iostream>
using namespace std;

typedef char Elemtype;
typedef struct Lnode {
    Elemtype data;
    struct Lnode *next;
} Linklist;

void Initlist(Linklist *&L) {
    L = new Linklist;
    L->next = NULL;
}

void Creatlist_R(Linklist *&L, int n) {
    L->next = NULL;
    Linklist *r = L;
    for (int i = 0; i < n; i++) {
        Linklist *p = new Linklist;
        cin >> p->data;
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

void Creatlist_H(Linklist *&L, int n) {
    L->next = NULL;
    for (int i = 0; i < n; i++) {
        Linklist *p = new Linklist;
        cin >> p->data;
        p->next = L->next;
        L->next = p;
    }
}

void outputlist(Linklist *L) {
    Linklist *p = L->next;
    while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

void Listlen(Linklist *L, int &len) {
    int cnt = 0;
    Linklist *p = L->next;
    while (p) {
        cnt++;
        p = p->next;
    }
    len = cnt;
}

bool Listempty(Linklist *L) {
    return L->next == NULL;
}

bool GetElem(Linklist *L, int pos, Elemtype &e) {
    if (pos < 1) return false;
    Linklist *p = L->next;
    int j = 1;
    while (p && j < pos) {
        p = p->next;
        j++;
    }
    if (!p || j != pos) return false;
    e = p->data;
    return true;
}

bool LocateElem(Linklist *L, int &pos, Elemtype e) {
    Linklist *p = L->next;
    int j = 1;
    while (p && p->data != e) {
        p = p->next;
        j++;
    }
    if (p) {
        pos = j;
        return true;
    } else {
        pos = 0;
        return false;
    }
}

bool InsertElem(Linklist *&L, int pos, Elemtype e) {
    if (pos < 1) return false;
    Linklist *p = L;
    int j = 0;
    while (p && j < pos - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > pos - 1) return false;
    Linklist *temp = new Linklist;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return true;
}

bool DeleteElem(Linklist *&L, int pos, Elemtype &e) {
    if (pos < 1) return false;
    Linklist *p = L;
    int j = 0;
    while (p && j < pos - 1) {
        p = p->next;
        j++;
    }
    if (!p || !p->next) return false;
    Linklist *temp = p->next;
    e = temp->data;
    p->next = temp->next;
    delete temp;
    return true;
}

void Clearlist(Linklist *&L) {
    while (L->next) {
        Linklist *p = L->next;
        L->next = p->next;
        delete p;
    }
}

void DestroyList(Linklist *&L) {
    Clearlist(L);
    delete L;
    L = NULL;
}

int main() {
    Linklist *L;
    Initlist(L);
    int n;
    cout << "请输入链表长度：";
    cin >> n;
    cout << "尾插法创建链表,请依次输入元素：";
    Creatlist_R(L, n);

    cout << "\n输出链表：";
    outputlist(L);

    int len;
    Listlen(L, len);
    cout << "\n链表的长度为：" << len << endl;

    if (Listempty(L))
        cout << "\n链表为空" << endl;
    else
        cout << "\n链表不为空" << endl;

    int pos1;
    Elemtype e1;
    cout << "\n请输入想获取的元素的位置：";
    cin >> pos1;
    if (GetElem(L, pos1, e1)) {
        cout << "位置" << pos1 << "的元素为：" << e1 << endl;
    } else {
        cout << "输入错误！访问越界" << endl;
    }

    int pos2;
    Elemtype e2;
    cout << "\n请输入想定位的元素值：";
    cin >> e2;
    if (LocateElem(L, pos2, e2)) {
        cout << e2 << "位于位置" << pos2 << endl;
    } else {
        cout << "未找到元素" << e2 << endl;
    }

    int pos3;
    Elemtype e3;
    cout << "\n请输入插入元素的值：";
    cin >> e3;
    cout << "请输入插入元素的位置：";
    cin >> pos3;
    if (InsertElem(L, pos3, e3)) {
        cout << "插入成功";
    } else {
        cout << "输入错误！访问越界";
    }
    cout << "当前链表：";
    outputlist(L);

    int pos4;
    Elemtype e4;
    cout << "\n请输入删除元素的位置：";
    cin >> pos4;
    if (DeleteElem(L, pos4, e4)) {
        cout << e4 << "已删除" << endl;
    } else {
        cout << "删除失败！访问越界" << endl;
    }
    cout << "当前链表：";
    outputlist(L);

    Clearlist(L);
    cout << "\n链表已清空" << endl;
    if (Listempty(L))
        cout << "链表为空" << endl;
    else
        cout << "链表不为空" << endl;

    DestroyList(L);
    cout << "\n链表已销毁" << endl;
    return 0;
}
