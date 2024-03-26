#include<stdio.h>
#include<windows.h>
typedef struct Node *PtrToNode;
struct Node{
    int Data;
    PtrToNode next;
};
typedef PtrToNode List;
List ListConcat(List L1,List L2);
List Read();
void Print(List L);

int main(){
    List L1,L2,L;
    L1=Read();
    L2=Read();
    L=ListConcat(L1,L2);
    Print(L);
    return 0;
}

List Read(){
    int n,i,a;
    List head,p,q,t;
    scanf("%d",&n);
    head=NULL;
    for(i=0;i<n;i++){
        p=(List)malloc(sizeof(struct Node));
        scanf("%d",&a);
        p->Data=a;
        if(head==NULL)
          head=p;
        else
           q->next=p;
        q=p;
    }
    return head;
}

void Print(List L){
    List p=L;
    if(p==NULL)
       printf("NULL");
    while(p){
        printf("%d",p->Data);
        p=p->next;
    }
}

List ListConcat(List L1,List L2){
    
    if(L1==NULL)return L2;
    if(L2==NULL)return L1;
    else{
        List p=L1;
        while(L1->next!=NULL){
            L1=L1->next;
        }
        L1->next=L2;
        return p;
    }
}