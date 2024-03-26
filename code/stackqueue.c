#include<stdio.h>
#include<windows.h>
#define MAXM 1001
int pa=-1;
int pb=-1;
void pop(int a[],int b[],int m,int n,int openumber);
int main(){
    int n;
    int i;
    int a[MAXM];
    int b[MAXM];
    
    char ope;
    int openumber;
    
    int operatingtime;
    int popnumber;

    scanf("%d",&n);
    getchar();
    for(i=0;i<n;i++){
        scanf("%c",&ope);
        if(ope=='I'){
           scanf("%d",&openumber);
           pa++;
           a[pa]=openumber;
        }else{
            pop(a,b,pa,pb,openumber);
        }
        getchar();
    }
}

void pop(int a[],int b[],int m,int n,int openumber){
    pa=m;
    pb=n;

    int operatingtime;
    int popnumber;
    int i;

    if(pb==-1){
        if(pa==-1)printf("ERROR\n");
        else{
           for(i=0;i<=pa;i++){
            b[i]=a[pa-i];
           }
           pb=pa;
           operatingtime= 2*(pa+1)+1;
           popnumber=b[pb];
           pb--;
           pa--;
           if(pa>=0){
             for(i=0;i<=pa;i++){
               a[i]=a[i+1];
             }
           }
        }
    }else{
        operatingtime=1;
        popnumber=b[pb];
        pb--;
        pa--;
        if(pa>=0){
          for(i=0;i<=pa;i++){
            a[i]=a[i+1];
          }
        }
    }
    printf("%d %d\n",popnumber,operatingtime);
}
