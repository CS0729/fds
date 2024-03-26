#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

#define MaxVertices 10  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};

Graph ReadG(); /* details omitted */

void PrintV( Vertex V )
{
   printf("%d ", V);
}

void StronglyConnectedComponents( Graph G, void (*visit)(Vertex V) );

int main()
{
    Graph G = ReadG();
    StronglyConnectedComponents( G, PrintV );
    return 0;
}


void DFS(Vertex V, Graph G, int* visited, void (*visit)(Vertex V))
{
    PtrToVNode WNode;
    visited[V] = 1;
    visit(V);
    for (WNode = G->Array[V]; WNode; WNode = WNode->Next) {
        if (!visited[WNode->Vert]) {
            DFS(WNode->Vert, G, visited, visit);
        }
    }
}

void ReverseDFS(Vertex V, Graph G, int* visited)
{
    PtrToVNode WNode;
    visited[V] = 1;
    for (WNode = G->Array[V]; WNode; WNode = WNode->Next) {
        if (!visited[WNode->Vert]) {
            ReverseDFS(WNode->Vert, G, visited);
        }
    }
}

void StronglyConnectedComponents(Graph G, void (*visit)(Vertex V))
{
    int* visited = (int*)malloc(G->NumOfVertices * sizeof(int));
    int i;

    // Initialize visited array
    for (i = 0; i < G->NumOfVertices; i++) {
        visited[i] = 0;
    }

    // Perform DFS on each unvisited vertex
    for (i = 0; i < G->NumOfVertices; i++) {
        if (!visited[i]) {
            DFS(i, G, visited, visit);
        }
    }

    // Reverse the graph
    Graph reverseG = (Graph)malloc(sizeof(struct GNode));
    reverseG->NumOfVertices = G->NumOfVertices;
    reverseG->NumOfEdges = G->NumOfEdges;
    reverseG->Array = (PtrToVNode*)malloc(G->NumOfVertices * sizeof(PtrToVNode));
    for (i = 0; i < G->NumOfVertices; i++) {
        reverseG->Array[i] = NULL;
    }
    for (i = 0; i < G->NumOfVertices; i++) {
        PtrToVNode node = G->Array[i];
        while (node) {
            PtrToVNode newNode = (PtrToVNode)malloc(sizeof(struct VNode));
            newNode->Vert = i;
            newNode->Next = reverseG->Array[node->Vert];
            reverseG->Array[node->Vert] = newNode;
            node = node->Next;
        }
    }

    // Reset visited array
    for (i = 0; i < G->NumOfVertices; i++) {
        visited[i] = 0;
    }

    // Perform DFS on reverse graph in order of finishing times
    for (i = G->NumOfVertices - 1; i >= 0; i--) {
        Vertex V = visited[i];
        if (!visited[V]) {
            ReverseDFS(V, reverseG, visited);
            printf("\n");
        }
    }

    free(visited);
    free(reverseG->Array);
    free(reverseG);
}

