#include<windows.h>
#include<stdio.h>

#define MAXM 31

typedef int ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
    int level;
};

Tree BuildTree(int a[],int b[],int level,int N);
void zigzagging(Tree Temp);
void findelement(Tree Temp,int findlevel,int levelnumber[]);

int j;
int numberofnode;
int count=0;

int main(){
    int numberofnode;
    int i;
    int a[MAXM],b[MAXM],levelnumber[MAXM];
    Tree T;

   scanf("%d",&numberofnode);
   for(i=0;i<numberofnode;i++){
    scanf("%d",&a[i]);
   }
   for(i=0;i<numberofnode;i++){
    scanf("%d",&b[i]);
   }

   T = BuildTree(a,b,0,numberofnode);
   zigzagging(T);
}


Tree BuildTree(int a[],int b[],int level,int N){
    Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->level = level;
	T->Element = b[N-1];

    int i;
    int markindex;

    if (N == 1) {
		T->Left = NULL;
		T->Right = NULL;
		return T;
	}
   
    for(i=0;i<N;i++){
        if(a[i]==b[N-1]){
           markindex = i;
           break;
        }
    }
    
    if (markindex != 0 && markindex != N-1)
	{
		
		T->Left = BuildTree(a,b,level+1,markindex);
		
		T->Right = BuildTree(&a[i+1], &b[i],level+1 , N-1-markindex);
	}
	
	else if (markindex == N - 1)
	{
		T->Right = NULL;
		T->Left = BuildTree(a,b,level+1,markindex);
	}
	
	else if (markindex == 0)
	{
		T->Left = NULL;
		T->Right = BuildTree(&a[i+1], &b[i],level+1 , N-1-markindex);
	}
	return T;
}


void findelement(Tree Temp,int findlevel,int levelnumber[]){
  
  if(Temp==NULL)return;
  if(Temp->level==findlevel){
     levelnumber[j]=Temp->Element;
     j++;
     return;
  }else {
		findelement(Temp->Left,findlevel,levelnumber);
		findelement(Temp->Right,findlevel,levelnumber);
  }
}


void zigzagging(Tree Temp){
    Tree T=Temp;
    int printnumber=0;
    int i,k;
    int levelnumber[MAXM];
    
    for(i=0;;i++){
        j=0;
        findelement(T,i,levelnumber);
        if(j==0)break;
        if (i%2== 0) {
			while (j > 0) {
				j--;
				printnumber++;
				if (printnumber != numberofnode) {
					printf("%d ", levelnumber[j]);
				}
				else {
					printf("%d", levelnumber[j]);
				}

			}
		}
		else {
			for (k = 0; k < j; k++) {
				printnumber++;
				if (printnumber != numberofnode) {
					printf("%d ", levelnumber[k]);
				}
				else {
					printf("%d", levelnumber[k]);
				}
			}

        }
    }
}

