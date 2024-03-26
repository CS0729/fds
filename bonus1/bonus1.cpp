/*Author:陈硕; ID:3220106406; No.01*/
#include<stdio.h>
#include<windows.h>
#define MAXM 1001
int pa=-1;   /*global variable,points to the top of a[]*/
int pb=-1;   /*global variable,points to the top of b[]*/
void pop(int a[],int b[],int m,int n,int openumber);
int main(){
    int n;
    int i;
    int a[MAXM];
    int b[MAXM];
    
    char ope;       /*'I'or'O'*/
    int openumber;  /*the number we push in at present*/
    
    int operatingtime; /*result 1:time we need to compute*/
    int popnumber;  /*result 2:the number we pop*/

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
        if(pa==-1){
          printf("ERROR\n");  /*pa=-1&&pb=-1:can't pop*/
          return;
        }
        else{                /*pb=-1&&pa!=-1:pop all the numbers in a[] and push them in b[]*/
           for(i=0;i<=pa;i++){
            b[i]=a[pa-i];     
           }
           pb=pa;
           operatingtime= 2*(pa+1)+1;  /*pop from a[]:pa+1    push into b[]:pb+1(pa=pb)   now the number we should pop is on the top of stack b,so another opration is enough*/
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
        operatingtime=1;/*if pb!=-1,then the number we should pop is just on the top of stack b,so one operation is enough*/
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
