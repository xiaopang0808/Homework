#include <iostream>
using namespace std;

typedef char Elemtype;

typedef struct Lnode {
    Elemtype data;         // ������
    struct Lnode *next;    // ָ����ָ���̽ڵ�
} Linklist;

//��ʼ��
void Initlist(Linklist *&L) {
    L = new Linklist;      
    L->next = L;          // �γɿջ��ṹ
}

//�������
void outputlist(Linklist *L) {
    if (L->next == L) {   // ��������
        cout << "����Ϊ��" << endl;
        return;
    }
    Linklist *p = L->next; 
    do {
        cout << p->data << ' ';
        p = p->next;
    } while (p != L->next); // ѭ����ֹ�������ص���ʼ�ڵ�
    cout << endl;
}

//��
void Listlen(Linklist *L, int &len) {
    if (L->next == L) {   // ��������
        len = 0;
        return;
    }
    len = 0;
    Linklist *p = L->next->next; // �ӵڶ����ڵ㿪ʼ����
    while (p != L->next) { // ����������
        len++;
        p = p->next;
    }
}

//�жϿձ�
bool Listempty(Linklist *L) {
    return L->next == L;  
}

//��λ����
bool GetElem(Linklist *L, int pos, Elemtype &e) {
    int len;
    Listlen(L, len);
    if (pos < 1 || pos > len) return false;  // ��Ч�Լ��

    Linklist *p = L->next; // ָ���һ�����ݽڵ�
    for (int j = 1; j < pos; j++) // �ƶ���Ŀ��λ��
        p = p->next;
    e = p->data;          // ��ȡԪ��ֵ
    return true;
}

//��ֵ����
bool LocateElem(Linklist *L, int &pos, Elemtype e) {
    if (L->next == L) {   // ������ֱ�ӷ���
        pos = 0;
        return false;
    }
    Linklist *p = L->next;
    pos = 1;
    do {  // ����������
        if (p->data == e)
            return true;
        p = p->next;
        pos++;
    } while (p != L->next);
    pos = 0;              // δ�ҵ�����λ��
    return false;
}

//����
bool InsertElem(Linklist *&L, int pos, Elemtype e) {
    if (pos < 1) return false;

    int len;
    Listlen(L, len);
    if (pos > len + 1) return false; // ����λ�ò��ܳ�������+1

    Linklist *p = L;      // ��ͷ�ڵ㿪ʼ
    for (int j = 0; j < pos - 1; j++) // �ƶ�������λ��ǰ��
        p = p->next;

    // �����������½ڵ�
    Linklist *temp = new Linklist;
    temp->data = e;
    temp->next = p->next;
    p->next = temp;
    return true;
}

//ɾ��
bool DeleteElem(Linklist *&L, int pos, Elemtype &e) {
    int len;
    Listlen(L, len);
    if (pos < 1 || pos > len) return false;  // ��Ч�Լ��

    Linklist *p = L;      // ��ͷ�ڵ㿪ʼ
    for (int j = 0; j < pos - 1; j++) // �ƶ���ɾ��λ��ǰ��
        p = p->next;

    Linklist *temp = p->next; // ��¼��ɾ�ڵ�
    e = temp->data;       // ���汻ɾԪ��ֵ
    p->next = temp->next; // ������ɾ�ڵ�
    delete temp;          // �ͷ��ڴ�
    return true;
}

//�������
void Clearlist(Linklist *&L) {
    Linklist *current = L->next; // ��һ�����ݽڵ�
    while (current != L) {       // �����������ݽڵ�
        Linklist *nextNode = current->next;
        delete current;         // �ͷŵ�ǰ�ڵ�
        current = nextNode;
    }
    L->next = L;                // ����ͷ�ڵ�ָ��
}

//����
void DestroyList(Linklist *&L) {
    Clearlist(L);    // ������ݽڵ�
    delete L;        // �ͷ�ͷ�ڵ�
    L = NULL;        // ��ֹҰָ��
}

int main() {
    Linklist *L;
    Initlist(L);     // ��ʼ��ѭ������

    // ���Բ��빦��
    InsertElem(L, 1, 'A');
    InsertElem(L, 2, 'B');
    InsertElem(L, 3, 'C');
    InsertElem(L, 4, 'D');
    InsertElem(L, 5, 'E');

    cout << "�������";
    outputlist(L);   
    cout << endl;

    int len;
    Listlen(L, len);
    cout << "����ĳ���Ϊ��" << len << endl << endl;  

    if (Listempty(L))
        cout << "����Ϊ��" << endl << endl;
    else
        cout << "����Ϊ��" << endl << endl;

    int pos1;
    Elemtype e1;
    cout << "���������ȡ��Ԫ�ص�λ�ã�";
    cin >> pos1;
    if (GetElem(L, pos1, e1)) {
        cout << "λ��" << pos1 << "��Ԫ��Ϊ��" << e1 << endl;
    } else {
        cout << "������󣡷���Խ��" << endl;
    }
    cout << endl;

    int pos2;
    Elemtype e2;
    cout << "�������붨λ��Ԫ��ֵ��";
    cin >> e2;
    if (LocateElem(L, pos2, e2)) {
        cout << e2 << "λ��λ��" << pos2 << endl;
    } else {
        cout << "δ�ҵ�Ԫ��" << e2 << endl;
    }
    cout << endl;

    int pos3;
    Elemtype e3;
    cout << "���������Ԫ�ص�ֵ��";
    cin >> e3;
    cout << "���������Ԫ�ص�λ�ã�";
    cin >> pos3;
    if (InsertElem(L, pos3, e3)) {
        cout << "����ɹ�����ǰ����";
        outputlist(L);
    } else {
        cout << "������󣡷���Խ��" << endl;
    }
    cout << endl;

    int pos4;
    Elemtype e4;
    cout << "������ɾ��Ԫ�ص�λ�ã�";
    cin >> pos4;
    if (DeleteElem(L, pos4, e4)) {
        cout << e4 << "��ɾ������ǰ����";
        outputlist(L);
    } else {
        cout << "ɾ��ʧ�ܣ�����Խ��" << endl;
    }
    cout << endl;

    Clearlist(L);
    cout << "���������" << endl << endl;

    if (Listempty(L))
        cout << "����Ϊ��" << endl << endl;
    else
        cout << "����Ϊ��" << endl << endl;

    DestroyList(L);
    cout << "����������" << endl << endl;
    return 0;
}
