#include<stdio.h>
#include<windows.h>
#define MAXM 501
#define INF 1000000
int flag=1;
int g[MAXM][MAXM];
int mark2[MAXM][MAXM];
int findConnectedComponents(int v);
void DFS(int visited[], int v, int node);
int primMST(int v);
int minKey(int key[], int mstSet[],int v);


int main(){
    int v,e;
    scanf("%d%d",&v,&e);
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            g[i][j]=0;
            mark2[i][j]=0;
        }
    }
    int start,end,weight;
    int mark1[MAXM]={0};
    for(int i=0;i<e;i++){
        scanf("%d%d%d",&start,&end,&weight);
        g[start-1][end-1]=weight;
        g[end-1][start-1]=weight;
        if(mark1[weight]==0){
            mark1[weight]=1;
        }else{
            mark2[start-1][end-1]=1;
            mark2[end-1][start-1]=1;
            for(int j=0;j<v;j++){
                for(int k=0;k<v;k++){
                    if(g[j][k]==weight){
                        mark2[j][k]=1;
                        mark2[k][j]=1;
                    }
                }
            }
        }
    }
    int m;
    m=findConnectedComponents(v);
    if(m==1){
       printf("%d\n",primMST(v));
       if(flag)printf("Yes\n");
       else printf("No\n"); 
    }else{
        printf("No MST\n");
        printf("%d\n",m);
    }
    
}

int findConnectedComponents(int v) {
    int visited[MAXM] = {0}; 
    int count = 0; 

    for (int i = 0; i < v; i++) {
        if (!visited[i]) {
            DFS(visited, v, i);
            count++;
        }
    }

    return count;
}


void DFS(int visited[], int v, int node) {
    visited[node] = 1;

    for (int i = 0; i < v; i++) {
        if (g[node][i] != 0 && !visited[i]) {
            DFS(visited, v, i);
        }
    }
}


int minKey(int key[], int mstSet[],int v) {
    int min = INF, min_index;

    for (int w = 0; w < v; w++) {
        if (mstSet[w] == 0 && key[w] < min) {
            min = key[w];
            min_index = w;
        }
    }

    return min_index;
}

int primMST(int v) {
    int parent[MAXM]; // 保存最小生成树
    int key[MAXM];    // 保存选择的边的权重
    int mstSet[MAXM]; // 记录节点是否已经在最小生成树中

    for (int i = 0; i < v; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < v - 1; count++) {
        int u = minKey(key, mstSet,v);
        mstSet[u] = 1;

        for (int w = 0; w < v; w++) {
            if (g[u][w] && mstSet[w] == 0 && g[u][w] < key[w]) {
                parent[w] = u;
                key[w] = g[u][w];
            }
        }
    }
   
    int minWeight = 0;
    for (int i = 1; i < v; i++) {
        mark2[i][parent[i]]=0;
        mark2[parent[i]][i]=0;
        minWeight += g[i][parent[i]];
    }
   
    for(int i=0;i<v;i++){
        for(int j=0;j<v;j++){
            if(mark2[i][j]==1){
                flag=0;
                break;
            }
        }
    }


    return minWeight;
}

 
