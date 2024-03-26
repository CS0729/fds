#include<stdio.h>
#include<windows.h>
#define MAXM 1001
int flag[MAXM]={0}; //whether this number has been used
int available[MAXM]={0}; //whether this number can be put in a position
int j=0;
int Numberofthisposition(int m,int a[],int b[],int c[],int temp[],int N);
int Findmin(int temp[],int n);
int main(){
    int N,number;
    int a[MAXM];
    int b[MAXM];
    int c[MAXM]; //storing a[i]%N
    int temp[MAXM];
    scanf("%d",&N);
    number=N;
    int i;
    for(i=0;i<N;i++){
        scanf("%d",&a[i]);
        if(a[i]>=0){
            c[i]=a[i]%N; 
        }else{
            c[i]=N;
            number--;
        }
    }
    for(i=0;i<number;i++){
       b[i]=Numberofthisposition(i,a,b,c,temp,N);
    }
    for(i=0;i<number;i++){
        if(i!=N-1){
            printf("%d ",b[i]);
        }else{
            printf("%d",b[i]);
        }
    }
}

int Numberofthisposition(int m,int a[],int b[],int c[],int temp[],int N){
    int i;
    int index;
    int result;
    for(i=0;i<N;i++){
        if(c[i]==i&&flag[i]==0){
            temp[j++]=a[i];
            available[i]=1;
        }
       
    }
    for(i=0;i<N;i++){
        int mark=1;
        int m=c[i];
        if(m==i||a[i]<0)continue;
        while(m!=i){
            if(flag[m]==0){
                mark=0;
                break;
            }
            m=(m+1)%N;
        }
        if(mark==1&&flag[i]==0){
            temp[j++]=a[i];
        }
    }

    result=Findmin(temp,j);
    for(i=0;i<N;i++){
        if(a[i]==result){
            flag[i]=1;
            break;
        }
    }
    j=0;
    return result;
}

int Findmin(int temp[],int n){
    int i,result;
    result=temp[0];
    for(i=1;i<n;i++){
        if(temp[i]<result){
            result=temp[i];
        }
    }
    return result;
}