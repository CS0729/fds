#include<stdio.h>
#include<windows.h>
#include<math.h>
#define MAXM 101

void solve(int n,double X[]);
double Compute(double temp[],int n);
void print(double X[],int n2);
void copy(double temp[],double a[],int n);
int computerank(double M[],int m1,int m2);
int Max(int a,int b,int c,int d);

int main(){
    int n1,n2;
    double X[MAXM];
    printf("Please input the number of formulas:");
    scanf("%d",&n1);
    printf("Please input the number of variables:");
    scanf("%d",&n2);
    if(n1==n2){
        solve(n1,X);
    }else{
        
    }

}

//This function computes the solution of a equation set with n equations and n variables
void solve(int n,double X[]){
   int i,j;
   double a[MAXM],b[MAXM],temp[MAXM];
   double D[MAXM];
   double Det;
   printf("Please input the coefficientss of every variable row by row:\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%lf",&a[i*n+j]);
        }
    }
    printf("Please input the constants row by row:\n");
    for(i=0;i<n;i++){
        scanf("%lf",&b[i]);
    }
    
        for(i=0;i<n;i++){
            copy(temp,a,n);
            for(j=0;j<n;j++){
                temp[j*n+i]=b[j];
            }
            D[i]=Compute(temp,n);
        }
        copy(temp,a,n);
        Det=Compute(temp,n);
    if(Det!=0){
           for(i=0;i<n;i++){
            X[i]=D[i]/Det;
           }
            print(X,n);
    }else{
        for(i=0;i<n;i++){
           if(D[i]!=0){
           printf("There is no solution!\n");
           return;
           }
        }
      int rankofDet=computerank(a,n,n);
      printf("There are uncountable solutions,and the degree of fredom is %d\n",n-rankofDet);
    }
    
}

//This function conputes the value of a determinant
double Compute(double temp[],int n){
   if(n==1)return temp[0];
   else{
      int i,j;
      int k=0;
      double result=0;
      double b[MAXM],c[MAXM];
        for(i=0;i<n;i++){
          b[i]=temp[i];
        }

        for(i=0;i<n;i++){
            k=0;
            for(j=0;j<n*n;j++){
               if(((j-i)%n!=0)&&(j>=n)){
                 c[k]=temp[j];
                  k++;
                }
            }
            result+=pow(-1,i)*b[i]*Compute(c,n-1);
        }
        return result;
    }  
}

//This function copies the numbers in a[] into temp[]
void copy(double temp[],double a[],int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            temp[i*n+j]=a[i*n+j];
        }
    }
}

void print(double X[],int n2){
    int i;
    for(i=0;i<n2;i++){
        printf("X%d = %.2f\n",i,X[i]);
    }
}

int computerank(double M[],int m1,int m2){
    int n,i,j,k;
    int result=0;
    if(m1==m2){
        n=m1;
    }else if(m1>m2){
       double N[m1-m2][MAXM];
       for(i=0;i<=m1-m2;i++){
        for(j=0;j<m2;j++){
            for(k=0;k<m2;k++){
                N[i][j*m2+k]=M[j*m2+k+m2*i];
            }
        }
       }
       for(i=0;i<=m1-m2;i++){
         if(computerank(N[i],m2,m2)>result)
         result=computerank(N[i],m2,m2);
       }
       return result;
    }else{
        double N[m2-m1][MAXM];
       for(i=0;i<=m2-m1;i++){
        for(j=0;j<m1;j++){
            for(k=0;k<m1;k++){
                N[i][j*m1+k]=M[j*m1+k+j+i];
            }
        }
       }
       for(i=0;i<=m2-m1;i++){
         if(computerank(N[i],m1,m1)>result)
         result=computerank(N[i],m1,m1);
       }
       return result;
    }
    if(n==1){
        for(int i=0;i<m1*m2;i++){
            if(M[i]!=0)
            return 1;
        }
        return 0;
    }else{
    double det;
    int result;
    det=Compute(M,n);
    if(det!=0)
       return n;
    else{
        double M1[MAXM],M2[MAXM],M3[MAXM],M4[MAXM];
        int i,j;
        for(i=0;i<n-1;i++){
            for(j=0;j<n-1;j++){
                M1[i*n+j]=M[i*n+j+i];
            }
        }
        for(i=0;i<n-1;i++){
            for(j=0;j<n-1;j++){
                M2[i*n+j]=M[i*n+j+i+1];
            }
        }
        for(i=0;i<n-1;i++){
            for(j=0;j<n-1;j++){
                M3[i*n+j]=M[i*n+j+i+n];
            }
        }
        for(i=0;i<n-1;i++){
            for(j=0;j<n-1;j++){
                M4[i*n+j]=M[i*n+j+i+n+1];
            }
        }
        
        return Max(computerank(M1,n-1,n-1),computerank(M2,n-1,n-1),computerank(M3,n-1,n-1),computerank(M4,n-1,n-1));
    }   
    }
}

int Max(int a,int b,int c,int d){
    int m1,m2;
    if(a<b){
        m1=b;
    }else{
        m1=a;
    }
    if(c>d){
        m2=c;
    }else{
        m2=d;
    }
    if(m1>m2)return m1;
    else return m2;
}