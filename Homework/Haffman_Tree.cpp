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

// 哈夫曼编码结构体
typedef struct {
    int code[20];     
    int start;       
}Hcode;

// 构建哈夫曼树
void CreatHT(HTnode HT[],int n0){
    int lnode,rnode;       // 存储最小权重节点的左右索引
    double min1,min2;      // 存储当前找到的两个最小权重值   
    // 初始化所有节点：父节点和左右子节点初始化为-1（表示无连接）
    for(int i=0;i<2*n0-1;i++){
        HT[i].parent=HT[i].lchild=HT[i].rchild=-1;
    }
    // 构建非叶子节点（总共有n0-1个非叶子节点，从第n0个位置开始构建）
    for(int i=n0;i<2*n0-1;i++){
        min1=min2=32767;    
        lnode=rnode=-1;          
        // 在未合并的节点中寻找两个最小权重的节点
        for(int k=0;k<i;k++){
            if(HT[k].parent==-1){  // 仅处理未被合并的节点（父节点为-1表示未合并）
                if(HT[k].weight<min1){
                    // 找到更小的权重值，更新次小值和最小索引
                    min2=min1;       
                    rnode=lnode;     
                    min1=HT[k].weight; 
                    lnode=k;   
                }else if(HT[k].weight<min2){
                    // 找到次小的权重值，更新次小索引
                    min2=HT[k].weight; 
                    rnode=k;          
                }
            }
        }
        
        // 合并两个最小权重节点，生成新的非叶子节点
        HT[i].weight=min1+min2;  // 新节点权重为两子节点权重之和
        HT[i].lchild=lnode;    
        HT[i].rchild=rnode;      
        HT[lnode].parent=i;     
        HT[rnode].parent=i;    
    }
}

// 生成哈夫曼编码
void HaffmanCode(HTnode HT[],Hcode hcd[],int n0){
    int i,f,c;       // i-当前叶子节点索引；f-父节点索引；c-当前节点索引
    Hcode  hc;       // 临时存储当前节点的编码
    
    for(i=0;i<n0;i++){
        hc.start=n0;  // 编码从数组末尾开始存储
        c=i;          // 从当前叶子节点开始向上回溯
        f=HT[i].parent;  // 获取当前节点的父节点
        // 从叶子节点回溯到根节点，生成编码
        while(f!=-1){
            if(HT[f].lchild==c){
                // 如果当前节点是父节点的左子节点，编码添加0
                hc.code[hc.start--]=0;
            }else{
                // 如果当前节点是父节点的右子节点，编码添加1
                hc.code[hc.start--]=1;
            }
            c=f;          // 继续向上回溯
            f=HT[f].parent;  // 获取父节点的父节点
        }
        hc.start++;      // 调整起始位置（因为最后一次start--会多减一次）
        hcd[i]=hc;       // 保存当前叶子节点的编码
    }
}

// 计算哈夫曼树的带权路径长度（WPL）
double WPL(HTnode HT[],int n0){
    double wpl=0;    
    for(int i=0;i<n0;i++){
        int j=HT[i].parent;  
        int depth=0;        
        // 向上回溯到根节点，计算路径长度
        while(j!=-1){
            depth++;    
            j=HT[j].parent;  
        }
        wpl+=HT[i].weight*depth;  // 累加当前叶子节点的权重*深度
    }
    return wpl;
}

int main(){
    cout<<"实例一："<<endl;
    HTnode HT[20];    // 存储哈夫曼树节点（最多20个节点）
    Hcode HC[20];     // 存储各叶子节点的编码
    elemtype ch[5]={'A','B','C','D','E'};
    double w[5]={6,4,8,5,7};               
    int n0=5;                            
    // 初始化叶子节点数据和权重
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
    cout<<"带权路径长度WPL："<<WPL(HT,n0)<<endl;  

    cout<<"实例二："<<endl;
    elemtype ch2[8]={'A','B','C','D','E','F','G','H'};  
    double w2[8]={0.07,0.19,0.02,0.06,0.32,0.03,0.21,0.1};  
    int n1=8;                                              
    for(int i=0;i<n1;i++){
        HT[i].data=ch2[i];
        HT[i].weight=w2[i];
    }
    
    CreatHT(HT,n1);        
    HaffmanCode(HT,HC,n1);  
    
    // 输出各叶子节点的编码结果
    for(int i=0;i<n1;i++){
        cout<<HT[i].data<<":";
        for(int j=HC[i].start;j<=n1;j++){  
            cout<<HC[i].code[j];
        }
        cout<<endl;
    }
    cout<<"带权路径长度WPL："<<WPL(HT,n1)<<endl; 

    return 0;
}
