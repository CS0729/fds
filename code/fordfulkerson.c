#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<windows.h>

#define MAX_PLANETS 505
#define MAX_NAME_LENGTH 4
#define INT_MAX 2000000000

typedef struct {
    char source[MAX_NAME_LENGTH];
    char destination[MAX_NAME_LENGTH];
    int capacity;
} Route;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int capacity;
} Planet;

int minimum(int a, int b) {
    return a < b ? a : b;
}


void dfs(int vertex, int num_vertices, int graph[MAX_PLANETS][MAX_PLANETS], int visited[MAX_PLANETS]) {
    visited[vertex] = 1;
    for (int neighbor = 0; neighbor < num_vertices; ++neighbor) {
        if (graph[vertex][neighbor] == 1 && !visited[neighbor]) {
            dfs(neighbor, num_vertices, graph, visited);
        }
    }
}

// 判断有向图连通性的函数
int is_connected(int num_vertices, int graph[MAX_PLANETS][MAX_PLANETS]) {
    // 初始化 visited 数组
    int visited[MAX_PLANETS];
    for (int i = 0; i < num_vertices; ++i) {
        visited[i] = 0;
    }

    // 从第一个顶点开始深度优先搜索
    dfs(0, num_vertices, graph, visited);

    // 检查所有顶点是否都被访问到
    for (int i = 0; i < num_vertices; ++i) {
        if (!visited[i]) {
            return 0;
        }
    }

    return 1;
}




int fordFulkerson(int graph[MAX_PLANETS][MAX_PLANETS], int source, int sink, int numVertices) {
    int parent[MAX_PLANETS];
    int maxFlow = 0;

if(!is_connected(numVertices,graph[MAX_PLANETS][MAX_PLANETS])){
     return 0;
}else
{
    while (1) {
        memset(parent, -1, sizeof(parent));

        parent[source] = source;

        int queue[MAX_PLANETS];
        int front = 0, rear = 0;
        queue[rear++] = source;

        while (front != rear) {
            int current = queue[front++];
            for (int next = 0; next < numVertices; next++) {
                if (parent[next] == -1 && graph[current][next] > 0) {
                    parent[next] = current;
                    queue[rear++] = next;
                }
            }
        }

        if (parent[sink] == -1) {
            break; // No augmenting path found
        }

        int pathFlow = INT_MAX;

        for (int current = sink; current != source; current = parent[current]) {
            int prev = parent[current];
            pathFlow = minimum(pathFlow, graph[prev][current]);
        }

        for (int current = sink; current != source; current = parent[current]) {
            int prev = parent[current];
            graph[prev][current] -= pathFlow;
            graph[current][prev] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}
}

int main() {
    int numRoutes;
    char sourcePlanet[MAX_NAME_LENGTH];
    char destPlanet[MAX_NAME_LENGTH];

    scanf("%s %s %d", sourcePlanet, destPlanet, &numRoutes);

    int numPlanets = 0;
    Planet planets[MAX_PLANETS];
    Route routes[MAX_PLANETS];

    for (int i = 0; i < numRoutes; i++) {
        scanf("%s %s %d", routes[i].source, routes[i].destination, &routes[i].capacity);

        
        int foundSource = 0;
        for (int j = 0; j < numPlanets; j++) {
            if (strcmp(planets[j].name, routes[i].source) == 0) {
                foundSource = 1;
                break;
            }
        }

        // If not found, add it to the planet array
        if (!foundSource) {
            strcpy(planets[numPlanets].name, routes[i].source);
            numPlanets++;
        }

        // Check if destination planet is already in the planet array
        int foundDest = 0;
        for (int j = 0; j < numPlanets; j++) {
            if (strcmp(planets[j].name, routes[i].destination) == 0) {
                foundDest = 1;
                break;
            }
        }

        // If not found, add it to the planet array
        if (!foundDest) {
            strcpy(planets[numPlanets].name, routes[i].destination);
            numPlanets++;
        }
    }

    int graph[MAX_PLANETS][MAX_PLANETS] ;
    for (int i = 0; i < numRoutes; i++) {
        for (int j = 0; j < numPlanets; j++) {
            graph[i][j]=0;
        }
    }

    // Add edges to the graph based on the routes
    for (int i = 0; i < numRoutes; i++) {
        for (int j = 0; j < numPlanets; j++) {
            if (strcmp(planets[j].name, routes[i].source) == 0) {
                for (int k = 0; k < numPlanets; k++) {
                    if (strcmp(planets[k].name, routes[i].destination) == 0) {
                        graph[j][k] += routes[i].capacity;
                        break;
                    }
                }
                break;
            }
        }
    }

    // Find the minimum capacity needed for a planet station
    int sourceIndex = -1, destIndex = -1;

    for (int i = 0; i < numPlanets; i++) {
        if (strcmp(planets[i].name, sourcePlanet) == 0) {
            sourceIndex = i;
        }

        if (strcmp(planets[i].name, destPlanet) == 0) {
            destIndex = i;
        }
    }

    int minCapacity = fordFulkerson(graph, sourceIndex, destIndex, numPlanets);

    printf("%d\n", minCapacity);

    return 0;
}
