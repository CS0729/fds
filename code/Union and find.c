#include<stdio.h>
#include<windows.h>
#define MAXM 10000

void Union(int m,int n,int S[]);
int Find(int m,int S[]);

int main(){
    int n;
    scanf("%d",&n);
    getchar();
    int i,a,b;
    char op;
    int count=0;
    int S[MAXM]={0};
    scanf("%c",&op);
    while(op!='S'){
        scanf("%d%d",&a,&b);
        if(op=='I'){
            if(!(Find(a,S)==Find(b,S))){
                Union(a,b,S);
            }
        }else if(op=='C'){
            if(Find(a,S)==Find(b,S)){
                printf("yes\n");
            }else{
                printf("no\n");
            }
        }
        getchar();
        scanf("%c",&op);
    }
    for(i=1;i<=n;i++){
        if(S[i]==0)count++;
    }
    printf("There are %d components.\n",count);
}

int Find(int m,int S[]){
   while(S[m]>0){
    m=S[m];
   }
   return m;
}

void Union(int m,int n,int S[]){
    int a;
    if(m<n){
        a=Find(m,S);
        S[a]=n;
    }
    else{
        a=Find(n,S);
        S[a]=m;
    }
}