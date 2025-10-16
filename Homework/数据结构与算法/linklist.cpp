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
    cout << "�����������ȣ�";
    cin >> n;
    cout << "β�巨��������,����������Ԫ�أ�";
    Creatlist_R(L, n);

    cout << "\n�������";
    outputlist(L);

    int len;
    Listlen(L, len);
    cout << "\n����ĳ���Ϊ��" << len << endl;

    if (Listempty(L))
        cout << "\n����Ϊ��" << endl;
    else
        cout << "\n����Ϊ��" << endl;

    int pos1;
    Elemtype e1;
    cout << "\n���������ȡ��Ԫ�ص�λ�ã�";
    cin >> pos1;
    if (GetElem(L, pos1, e1)) {
        cout << "λ��" << pos1 << "��Ԫ��Ϊ��" << e1 << endl;
    } else {
        cout << "������󣡷���Խ��" << endl;
    }

    int pos2;
    Elemtype e2;
    cout << "\n�������붨λ��Ԫ��ֵ��";
    cin >> e2;
    if (LocateElem(L, pos2, e2)) {
        cout << e2 << "λ��λ��" << pos2 << endl;
    } else {
        cout << "δ�ҵ�Ԫ��" << e2 << endl;
    }

    int pos3;
    Elemtype e3;
    cout << "\n���������Ԫ�ص�ֵ��";
    cin >> e3;
    cout << "���������Ԫ�ص�λ�ã�";
    cin >> pos3;
    if (InsertElem(L, pos3, e3)) {
        cout << "����ɹ�";
    } else {
        cout << "������󣡷���Խ��";
    }
    cout << "��ǰ����";
    outputlist(L);

    int pos4;
    Elemtype e4;
    cout << "\n������ɾ��Ԫ�ص�λ�ã�";
    cin >> pos4;
    if (DeleteElem(L, pos4, e4)) {
        cout << e4 << "��ɾ��" << endl;
    } else {
        cout << "ɾ��ʧ�ܣ�����Խ��" << endl;
    }
    cout << "��ǰ����";
    outputlist(L);

    Clearlist(L);
    cout << "\n���������" << endl;
    if (Listempty(L))
        cout << "����Ϊ��" << endl;
    else
        cout << "����Ϊ��" << endl;

    DestroyList(L);
    cout << "\n����������" << endl;
    return 0;
}
