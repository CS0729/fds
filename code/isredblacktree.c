#include<stdio.h>
#include<windows.h>
#include<math.h>
#define MAXM 31

typedef int ElementType;                 //definition of struct variables
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType value;                  
    Tree  left;
    Tree  right;
    ElementType flag;                      //flag stands for color(1 for black and -1 for red)
    ElementType itsblack;                 //itsblack stands for the number of black nodes from the node to descendant leaves
};

Tree Buildtree(int a[],int start,int end);     //statements of six functions
int test1(Tree T);
int test2(Tree T);
int test3(Tree T);
int test4(Tree T);
void countblack(Tree T);


int main(){
    int treenumber;                          //definition of variables
    int nodenumber;
    int a[MAXM];
    int i,j;
    Tree H;

    scanf("%d",&treenumber);                 //input
    for(i=1;i<=treenumber;i++){
        scanf("%d",&nodenumber);
        for(j=0;j<nodenumber;j++){
            scanf("%d",&a[j]);
        }
        H=Buildtree(a,0,nodenumber-1);        //build the tree from the prefix array
        countblack(H);                        //count the number of black nodes from each node to descendant leaves
        if(test1(H)&&test2(H)&&test3(H)&&test4(H)){
            printf("Yes\n");             
        }else{
            printf("No\n");
        }
    }
}


Tree Buildtree(int a[],int start,int end)       //Function Buildtree builds a binary search tree from a profix array
{
    if(start>end) return NULL;                  //end building
    Tree T = (Tree)malloc(sizeof(struct TreeNode));  //ask for space
    int i;
    if(a[start]<0){                            //the first element is the root 
        T->value=-a[start];                    //judge whether it is black or red
        T->flag=-1;
    }else{
        T->value=a[start];
        T->flag=1;
    }

    for(i=start+1;i<=end;i++){             //the first element that is bigger than the original root is the cut point of left subtree and roght subtree
        if(abs(a[i])>T->value){
            break;
        }
    }

    T->left=Buildtree(a,start+1,i-1);      //recursion
    T->right=Buildtree(a,i,end);
    
    return T;
}

int test1(Tree T){                //Function test1 verifies whether there is a node which is neither red nor black
    int a,b;
    if(T==NULL){
        return 1;
    }else{
    if(T->value==0){             //jugde whether T->value is 0 so that the node is neither red or black
        return 0;
    }else{
        a=test1(T->left);        //recursion
        b=test1(T->right);       //only if left subtree and right subtree both satisfy can the whole treesatisfy
        if(a&&b)return 1;
        else return 0;
    }
    }
}

int test2(Tree T){               //Function test2 verifies whether the root of the tree is black
    if(T==NULL){
        return 1;                //judge whether the flag of the root is 1 or -1,1 stands for black,-1 stands for red
    }else if(T->flag>0){
        return 1;
    }else{
        return 0;
    }
}

int test3(Tree T){             //Function test3 verifies whether the children of a red node is black
    int a,b;
        if(T==NULL){
          return 1;
        }else if(T->flag==-1){    //if a node is red,its left or right children is either NULL or black
          if((T->left==NULL||T->left->flag==1)&&(T->right==NULL||T->right->flag==1)){
                return 1;
          }else{
                return 0;
          }
        }
     a=test3(T->left);         //recursion
     b=test3(T->right);
     if(a&&b)return 1;        //only if left subtree and right subtree both satisfy can the whole tree satisfy
     else return 0;
    }

int test4(Tree T){             //Function test4 verifies whether  all simple paths from the node to descendant leaves 
    if(T==NULL)return 1;       //contain the same number of black nodes for each node.
    else{
        if(T->left==NULL&&T->right!=NULL){
            if(T->right->itsblack!=0)return 0;
        }else if(T->left!=NULL&&T->right==NULL){
            if(T->left->itsblack!=0)return 0;
        }else if(T->left==NULL&&T->right==NULL){
            return 1;
        }else if(T->left!=NULL&&T->right!=NULL){
            if(T->left->itsblack!=T->right->itsblack)return 0;
            }
        }
    if(test4(T->left)&&test4(T->right))return 1;   //recursion,only if left subtree and right subtree both satisfy can the whole tree satisfy
    else return 0;
}


void countblack(Tree T){           //Function countblack counts the number of black nodes from each node to descendant leaves
    if(T==NULL)return;
    else{
        if(T->left==NULL&&T->right!=NULL){                //if the node T is black,T->itsblack=T->right(left is also suitable)->itsblack +1
            countblack(T->right);                         //if the node T is red,T->itsblack=T->right(left is also suitable)->itsblack
            if(T->flag==1)T->itsblack=T->right->itsblack+1;
            else T->itsblack=T->right->itsblack;
        }else if(T->left!=NULL&&T->right==NULL){
            countblack(T->left);
            if(T->flag==1)T->itsblack=T->left->itsblack+1;
            else T->itsblack=T->left->itsblack;
        }else if(T->left==NULL&&T->right==NULL){
            if(T->flag==1)T->itsblack=1;
            else T->itsblack=0;
        }else if(T->left!=NULL&&T->right!=NULL){
            countblack(T->left);
            countblack(T->right);
            if(T->flag==1)T->itsblack=T->right->itsblack+1;
            else T->itsblack=T->right->itsblack;
        }
}
}