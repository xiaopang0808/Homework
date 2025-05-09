#include<iostream>
using namespace std;


typedef char elemtype;
typedef struct {
    elemtype data;    
    double weight;    
    int parent;       
    int lchild;       
    int rchild;       
}HTnode;

// ����������ṹ��
typedef struct {
    int code[20];     
    int start;       
}Hcode;

// ������������
void CreatHT(HTnode HT[],int n0){
    int lnode,rnode;       // �洢��СȨ�ؽڵ����������
    double min1,min2;      // �洢��ǰ�ҵ���������СȨ��ֵ   
    // ��ʼ�����нڵ㣺���ڵ�������ӽڵ��ʼ��Ϊ-1����ʾ�����ӣ�
    for(int i=0;i<2*n0-1;i++){
        HT[i].parent=HT[i].lchild=HT[i].rchild=-1;
    }
    // ������Ҷ�ӽڵ㣨�ܹ���n0-1����Ҷ�ӽڵ㣬�ӵ�n0��λ�ÿ�ʼ������
    for(int i=n0;i<2*n0-1;i++){
        min1=min2=32767;    
        lnode=rnode=-1;          
        // ��δ�ϲ��Ľڵ���Ѱ��������СȨ�صĽڵ�
        for(int k=0;k<i;k++){
            if(HT[k].parent==-1){  // ������δ���ϲ��Ľڵ㣨���ڵ�Ϊ-1��ʾδ�ϲ���
                if(HT[k].weight<min1){
                    // �ҵ���С��Ȩ��ֵ�����´�Сֵ����С����
                    min2=min1;       
                    rnode=lnode;     
                    min1=HT[k].weight; 
                    lnode=k;   
                }else if(HT[k].weight<min2){
                    // �ҵ���С��Ȩ��ֵ�����´�С����
                    min2=HT[k].weight; 
                    rnode=k;          
                }
            }
        }
        
        // �ϲ�������СȨ�ؽڵ㣬�����µķ�Ҷ�ӽڵ�
        HT[i].weight=min1+min2;  // �½ڵ�Ȩ��Ϊ���ӽڵ�Ȩ��֮��
        HT[i].lchild=lnode;    
        HT[i].rchild=rnode;      
        HT[lnode].parent=i;     
        HT[rnode].parent=i;    
    }
}

// ���ɹ���������
void HaffmanCode(HTnode HT[],Hcode hcd[],int n0){
    int i,f,c;       // i-��ǰҶ�ӽڵ�������f-���ڵ�������c-��ǰ�ڵ�����
    Hcode  hc;       // ��ʱ�洢��ǰ�ڵ�ı���
    
    for(i=0;i<n0;i++){
        hc.start=n0;  // ���������ĩβ��ʼ�洢
        c=i;          // �ӵ�ǰҶ�ӽڵ㿪ʼ���ϻ���
        f=HT[i].parent;  // ��ȡ��ǰ�ڵ�ĸ��ڵ�
        // ��Ҷ�ӽڵ���ݵ����ڵ㣬���ɱ���
        while(f!=-1){
            if(HT[f].lchild==c){
                // �����ǰ�ڵ��Ǹ��ڵ�����ӽڵ㣬�������0
                hc.code[hc.start--]=0;
            }else{
                // �����ǰ�ڵ��Ǹ��ڵ�����ӽڵ㣬�������1
                hc.code[hc.start--]=1;
            }
            c=f;          // �������ϻ���
            f=HT[f].parent;  // ��ȡ���ڵ�ĸ��ڵ�
        }
        hc.start++;      // ������ʼλ�ã���Ϊ���һ��start--����һ�Σ�
        hcd[i]=hc;       // ���浱ǰҶ�ӽڵ�ı���
    }
}

// ������������Ĵ�Ȩ·�����ȣ�WPL��
double WPL(HTnode HT[],int n0){
    double wpl=0;    
    for(int i=0;i<n0;i++){
        int j=HT[i].parent;  
        int depth=0;        
        // ���ϻ��ݵ����ڵ㣬����·������
        while(j!=-1){
            depth++;    
            j=HT[j].parent;  
        }
        wpl+=HT[i].weight*depth;  // �ۼӵ�ǰҶ�ӽڵ��Ȩ��*���
    }
    return wpl;
}

int main(){
    cout<<"ʵ��һ��"<<endl;
    HTnode HT[20];    // �洢���������ڵ㣨���20���ڵ㣩
    Hcode HC[20];     // �洢��Ҷ�ӽڵ�ı���
    elemtype ch[5]={'A','B','C','D','E'};
    double w[5]={6,4,8,5,7};               
    int n0=5;                            
    // ��ʼ��Ҷ�ӽڵ����ݺ�Ȩ��
    for(int i=0;i<n0;i++){
        HT[i].data=ch[i];
        HT[i].weight=w[i];
    }
    CreatHT(HT,n0);        
    HaffmanCode(HT,HC,n0);
    for(int i=0;i<n0;i++){
        cout<<HT[i].data<<":";
        for(int j=HC[i].start;j<=n0;j++){ 
            cout<<HC[i].code[j];
        }
        cout<<endl;
    }
    cout<<"��Ȩ·������WPL��"<<WPL(HT,n0)<<endl;  

    cout<<"ʵ������"<<endl;
    elemtype ch2[8]={'A','B','C','D','E','F','G','H'};  
    double w2[8]={0.07,0.19,0.02,0.06,0.32,0.03,0.21,0.1};  
    int n1=8;                                              
    for(int i=0;i<n1;i++){
        HT[i].data=ch2[i];
        HT[i].weight=w2[i];
    }
    
    CreatHT(HT,n1);        
    HaffmanCode(HT,HC,n1);  
    
    // �����Ҷ�ӽڵ�ı�����
    for(int i=0;i<n1;i++){
        cout<<HT[i].data<<":";
        for(int j=HC[i].start;j<=n1;j++){  
            cout<<HC[i].code[j];
        }
        cout<<endl;
    }
    cout<<"��Ȩ·������WPL��"<<WPL(HT,n1)<<endl; 

    return 0;
}
