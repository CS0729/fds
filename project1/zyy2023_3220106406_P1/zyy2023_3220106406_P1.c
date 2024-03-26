//This is a combination of a testing program (line3-line42)and three functions(line44-line76).
//Since the whole project isn't large,I don't divide into different C files. 
//Note:The program now can't run!Testers must modify line 28 when wanting to test a function.
#include <stdio.h>
#include<time.h>
double iterativepow2(double x,long m);
double iterativepow1(double x,long m);
double recursivepow(double x,long m);
clock_t start,stop;
double duration;
double overallduration;

int main(){
	double x;
	long m;
    double res;
	long ticks=0;
	long iterations =0;   //initialization
	
	printf("Base = ");
	scanf("%lf",&x);      //x represents the base
	printf("Exponent = ");
	scanf("%ld",&m);     //m represents the exponent
	
	do{
	start=clock();
	
	//run the testing function in the following line please
	res = function(x,m);  	//for example,change the line to "res = recursivepow(x,m);"

	stop=clock();
	ticks+=(stop-start);
	iterations++;         //iterations represents the times the functions have been operated
    }while(ticks<10);    // ticks=10 is large enough if we want an accuracy of at least 10%.
	overallduration=(double)(ticks)/CLK_TCK; 
	duration=overallduration/iterations;//computing the average operating time

	printf("Ans = %lf\n",res); //part of printing results
	printf("Iterations = %ld\n",iterations);
	printf("Ticks = %ld\n",ticks);
	printf("Totaltime = %lf\n",overallduration);
	printf("Duration = %.10lf\n",duration);
}

//This function uses the Algorithm1 to conpute x^m
double iterativepow1(double x,long m){
	long i;
	double result=1;
	for(i=1;i<=m;i++){   //getting the result by using N-1 multiplications
		result*=x;
	}
	return result;
}

//This function uses the recursive version of Algorithm2 to compute x^m
double recursivepow(double x,long m){
	if(m==0){      //the exit of recursion
	  return 1;
    }else if(m%2==0){   //if m is even,x^m=(x^x)^(m/2);
    	return recursivepow(x*x,m/2);
	}else{
		return recursivepow(x*x,m/2)*x;  //if m is odd,x^m=x*(x^x)^((m-1)/2)
	}
}

//This function uses the iterative version of Algorithm2 to compute x^m
double iterativepow2(double x,long m)
	{
	long i;
	double result=1;
	for(i=m;i!=0;i/=2){
		if(i%2==1)   //if i is odd,multiply x;Then, is even.
		  result *= x;
		x=x*x;     //This operation halves the the number of x left to multiply
	}
    return result;
	}
