#include<stdio.h>
#include<windows.h>
#define MAXM 1000
int FindKthLargest(int A[],int N,int K);
void BuildMinHeap(int *H,int K);
int main(){
    int N;
    printf("Please input the size of the list:");
    scanf("%d",&N);
    int K;
    printf("Please input the rank that you want to find:");
    scanf("%d",&K);
    int i,result;
    int A[MAXM];
    for(i=0;i<N;i++){
        scanf("%d",&A[i]);
    }
    printf("The %dth largest element is %d",K,FindKthLargest(A,N,K));
}

int FindKthLargest(int A[],int N,int K){
    int *H;
    int i,next,child;
    H=(int *)malloc((K+1)*sizeof(int));
    for(i=1;i<=K;i++)H[i]=A[i-1];
    BuildMinHeap(H,K);
    for(next=K;next<N;next++){
        H[0]=A[next];
        if(H[0]>H[1]){
            for(i=1;i*2<=K;i=child){
                child=i*2;
                if(child!=K&&H[child]>H[child+1])child++;
                if(H[child]<H[0])H[i]=H[child];
                else break;
            }
            H[i]=H[0];
        }
    }
    return H[1];
}

void BuildMinHeap(int *H,int K){
   int i,j;
   int size=0;
   H[0]=-1;
   for(i=1;i<=K;i++){
    size++;
    for(j=i;H[j/2]>H[j];j/=2){
        H[j]=H[j/2];
    }
    H[j]=H[i];
   }
}