//This program is to compute the value of a determiant.
#include<stdio.h>
#include<windows.h>
#include<math.h>
#define MAXM 1001
double Compute(double a[],int n);
int main(){
    int n;
    int i,j;
    double a[MAXM];
    printf("Please input the size of the Det:");
    scanf("%d",&n);
    printf("Please input the numbers in your Det row by row:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%lf",&a[i*n+j]);
        }
    }
    printf("The value of the Det is: %.2f",Compute(a,n));
}
double Compute(double a[],int n){
   if(n==1)return a[0];
   else{
      int i,j;
      int k=0;
      double result;
      double b[MAXM],c[MAXM];
        for(i=0;i<n;i++){
          b[i]=a[i];
        }

        for(i=0;i<n;i++){
            k=0;
            for(j=0;j<n*n;j++){
               if(((j-i)%n!=0)&&(j>=n)){
                 c[k]=a[j];
                  k++;
                }
            }
            result+=pow(-1,i)*b[i]*Compute(c,n-1);
        }
        return result;
    }  
}
