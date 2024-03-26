#include<stdio.h>
#include<windows.h>
#include<math.h>
#define MinData -1
#define MAXM 1001
typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode{
    ElementType  Value;
    Tree Left;
    Tree Right;
    int level;
};

void sort(int a[],int n);
Tree BuildTree(int a[],int start,int end,int level);
void levelorder(Tree H,int n);
int scaleofleft(int n);
void findelement(Tree Temp,int findlevel,int levelnumber[]);

int j;

int main(){
    Tree H;
    int n,i;
    int a[MAXM];
    scanf("%d",&n);
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    sort(a,n);
    H = BuildTree(a,0,n-1,0);
   levelorder(H,n);
  
}

void sort(int a[],int n){
    int i,j;
    int temp;
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(a[j]<a[i]){
                temp=a[j];
                a[j]=a[i];
                a[i]=temp;
            }
        }
    }
}

Tree BuildTree(int a[],int start,int end,int level){
    if(start>end)return NULL;
    
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
    int m= scaleofleft(end-start+1);
    T->Value= a[start+m];
    T->level=level;
    T->Left=BuildTree(a,start,start+m-1,level+1);
    T->Right=BuildTree(a,start+m+1,end,level+1);
    return T;
}

int scaleofleft(int n){
    int result;
    int i=1;
    int level=0;
    while(i<(n+1)){
        level++;
        i=i*2;   
    }
    if(level==1)result=0;
    else{
    int x1=pow(2,level-1)-1;
    int x2=n-x1+pow(2,level-2)-1;
      if(x1<x2){
        result=x1;
      }else{
        result=x2;
      }
      
    }
    return result;
}

void levelorder(Tree H,int n){
    int levelnumber[MAXM];
    int i,k;
    int printnumber=0;
    for(i=0;;i++){
        j=0;
        findelement(H,i,levelnumber);
        if(j==0)break;
             for(k=0;k<j;k++){
                printnumber++;
				if(printnumber!=n)
					printf("%d ", levelnumber[k]);
				else 
					printf("%d", levelnumber[k]);
				

			 }
		}
}

void findelement(Tree Temp,int findlevel,int levelnumber[]){
  if(Temp==NULL)return;
  if(Temp->level==findlevel){
     levelnumber[j]=Temp->Value;
     j++;
     return;
  }else {
		findelement(Temp->Left,findlevel,levelnumber);
		findelement(Temp->Right,findlevel,levelnumber);
  }
}