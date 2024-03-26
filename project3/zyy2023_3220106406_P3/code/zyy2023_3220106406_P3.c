#include<stdio.h>
#include<windows.h>
#define MaxVertexNum 1001
int g[MaxVertexNum][MaxVertexNum];  //global variable,storing the graph

int dijkstra(int vt[],int v);
int MinFromSettoVertex(int Set[],int num,int m);
void Buildset(int Remainset[],int Set[],int num,int v);
int MinFromSettoRemainset(int Set[],int Remainset[],int num,int v);  //four functions

int main(){
    int v,e;
    scanf("%d%d",&v,&e);        //v represents the number of vertices
    int i,k;                    //e represents the number of edges
    for(i=0;i<v;i++){            
        for(k=0;k<v;k++){
            g[i][k]=0;         //initialize the array,while g[i][k]=0 means there is no edge from vertice i to vertice k
        }
    }
    int vertex1,vertex2,value;
    for(i=0;i<e;i++){
        scanf("%d%d%d",&vertex1,&vertex2,&value);
        g[vertex1][vertex2]=value;               //read in the graph
        g[vertex2][vertex1]=value;
    }
    scanf("%d",&k);
    int vt[MaxVertexNum];
    for(i=0;i<k;i++){                          //read in the sequences remaining to be checked
        for(int j=0;j<v;j++){
            scanf("%d",&vt[j]);
        }
        if(dijkstra(vt,v))printf("Yes\n");      //judge if the present sequence is a Dijkstra sequence
        else printf("No\n");
         
    }
}

//This function is the judge function,which involves the core algorithm
int dijkstra(int vt[],int v){
     int Set[MaxVertexNum];           //We build an array called Set,storing the vertices we have included in
     int Remainset[MaxVertexNum];     //We build another array called Remainset,storing the vertices outside Set
     int min1,min2;                  //min1 represents the minimum distance from Set to the next vertive in given sequence
     int num=0;                      //min2 represents the minimum distance from Set to Remainset
     Set[0]=vt[0];
     num++;
     int i,j;
     int flag=1;                    //Every time we meet a vertice in the given sequence,we check if min1==min2
     for(i=1;i<v;i++){
            min1= MinFromSettoVertex(Set,num,vt[i]);
            Buildset(Remainset,Set,num,v);
            min2= MinFromSettoRemainset(Set,Remainset,num,v);
            if(min1!=min2){
                flag=0;
                break;
            }
            Set[num]=vt[i];
            num++;
           
    }
    return flag;                   //if min1!=min2 for any vertice,the sequence isn't a Dijkstra sequence,and we break with flag=0;                                  
}                                 //if min1==min2 for every vertice,it is a Dijkstra sequence,and we return flag=1;

//This function computes min1
int MinFromSettoVertex(int Set[],int num,int m){
    int i;
    int mindis;
    for(i=0;i<num;i++){                 //we first initialize the minimum distance,noting that the distance!=0 because 0 means there's no edge between 2 vertices
        if(g[Set[i]][m]!=0){
            mindis=g[Set[i]][m];
            break;
        }   
    }
    for(i=0;i<num;i++){                            //then we ergodic all elements in Set,comparing the distance with the minimum
        if(g[Set[i]][m]<mindis&&g[Set[i]][m]!=0){
            mindis=g[Set[i]][m];
        }
    }
    return mindis;                     //finally we return the minimum distance
}

//This function builds the array "Remainset"
void Buildset(int Remainset[],int Set[],int num,int v){
    int i=0;
    int j,k;
    int flag;
    for(j=1;j<=v;j++){               //the origin vertices are 1,2,3,……，v, while v means the number of vertices
        flag=1;                      //however,if the vertices have appeared in Set,then it can't be in Remainset,so we set flag to 0 and break
        for(k=0;k<num;k++){
            if(Set[k]==j){
                flag=0;
                break;
            }
        }
        if(flag==1){               //if flag=0,it means this vertice is outside Set,so we 'enroll' it into Remainset
            Remainset[i]=j;
            i++;
        }
    }
}

//This function computes min2
int MinFromSettoRemainset(int Set[],int Remainset[],int num,int v){
   int i,j;
   int mindis;
    for(i=0;i<num;i++){                        //we also first initialize the minimum distance,noting that the distance!=0 because 0 means there's no edge between 2 vertices
        for(j=0;j<(v-num);j++){
        if(g[Set[i]][Remainset[j]]!=0){
            mindis=g[Set[i]][Remainset[j]];
            break;
        }   
        }
    }
   for(i=0;i<num;i++){                             //then we ergodic all elements in Set and Remainset,comparing the distance with the minimum
        for(j=0;j<(v-num);j++){
            if(g[Set[i]][Remainset[j]]<mindis&&g[Set[i]][Remainset[j]]!=0){
                mindis=g[Set[i]][Remainset[j]];
            }
        }
   }
   return mindis;                                //finally we return the minimum distance
}