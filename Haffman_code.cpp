#include<bits/stdc++.h>
using namespace std;



typedef char elemtype;
typedef struct{
    elemtype data;
    double weight;
    int *parent;
    int *lchild;
    int *rchild;    
}HTnode;

typedef struct{
    int cd[32];
    int start;
i}

struct compare{
    bool operator()(HTnode* l,HTnode* r){
        return l->weight>r->weight;
    }
}

void HaffmanCoding(){
    
}


void CreatHT(HTnode *node,map<elemtype,int> char_count){
    priority_queue<HTnode*,vector<HTnode*>,compare> HTnode_list;
    for(auto pair:char_count){
        HTnode *temp=new HTnode;
        temp->data=pair.first;
        temp->weight=pair.second;
        HTnode_list.push(temp);
    }
    while(HTnode_list.size()!=1){
        HTnode* left=HTnode_list.top();HTnode_list.pop();
        HTnode* right=HTnode_list.top();HTnode_list.pop();
        HTnode* parent=new HTnode;
        parent->data='\0';
        parent->lchild=left;
        parent->rchild=right;
        parent->weight=left->weight+right->weight;
        HTnode_list.push(parent);
    }
    node=HTnode_list.top();
}


int main(){
    FILE *file=fopen("source.txt","r");
    if(file==NULL){
        perror("读取文件失败");
        return 1;
    }
    map<char,int> char_count;
    char buffer[100];
    while(fgets(buffer,sizeof(buffer),file)!=NULL){
        for(char ch:buffer){
            char_count[ch]++;
        }
    }
    fclose(file);
    map<char,HTcode> char_code;
    Creat_HTcode(map<char,int> char_count,map<char,HTcode>)


}
