#include<bits/stdc++.h>
using namespace std;




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
