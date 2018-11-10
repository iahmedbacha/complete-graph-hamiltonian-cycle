#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "stack.h"
#include "queue.h"

typedef struct {
    int index;
    int* indexes;
} vertex_t;


void dfs (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP);
void dfsIterative (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP);
void bfs (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP);
int cycleCost (int n, int** adjacencyMatrix, int* indexes);
//int** getArray2D (int n);
int** readArray2D (char* fileName, int* n);
void printArray2D (int n, int** array);
int* initializeArray (int n,int value);
int* cloneArray (int n, int* array);
void printArray (int n, int* array);
int* indexesToVertexes(int n,int* indexes);

int main(int argc, char const *argv[]) {
    // read input
    char* fileName = "./input.txt";
    int n;
    int** adjacencyMatrix = readArray2D(fileName, &n);
    // end read input

    // print input
    printf("\nMatrice d'adjacence : \n");
    printArray2D(n, adjacencyMatrix);
    // end print input

    // dfs
    printf("DFS:\n");
    int minCost1 = INT_MAX;
    int* minIndexes1 = initializeArray(n,-1);
    vertex_t* vertex1 = malloc(sizeof(vertex_t));
    vertex1->indexes = initializeArray(n,-1);
    vertex1->indexes[0] = 0;
    vertex1->index = 1;
    dfs(n,adjacencyMatrix,vertex1,&minCost1,&minIndexes1);
        // print results
        printf("\tLe plus petit cycle hamiltonien : ");
        printArray(n, indexesToVertexes(n,minIndexes1));
        printf("\tLe coût minimal = %d\n", minCost1);
        // end print results
    // end dfs

    // dfs iterative
    printf("DFS iterative:\n");
    int minCost2 = INT_MAX;
    int* minIndexes2 = initializeArray(n,-1);
    vertex_t* vertex2 = malloc(sizeof(vertex_t));
    vertex2->indexes = initializeArray(n,-1);
    vertex2->indexes[0] = 0;
    vertex2->index = 1;
    dfsIterative(n,adjacencyMatrix,vertex2,&minCost2,&minIndexes2);
        // print results
        printf("\tLe plus petit cycle hamiltonien : ");
        printArray(n, indexesToVertexes(n,minIndexes2));
        printf("\tLe coût minimal = %d\n", minCost2);
        // end print results
    // end dfs iterative

    // bfs
    printf("BFS:\n");
    int minCost3 = INT_MAX;
    int* minIndexes3 = initializeArray(n,-1);
    vertex_t* vertex3 = malloc(sizeof(vertex_t));
    vertex3->indexes = initializeArray(n,-1);
    vertex3->indexes[0] = 0;
    vertex3->index = 1;
    bfs(n,adjacencyMatrix,vertex3,&minCost3,&minIndexes3);
        // print results
        printf("\tLe plus petit cycle hamiltonien : ");
        printArray(n, indexesToVertexes(n,minIndexes3));
        printf("\tLe coût minimal = %d\n", minCost3);
        // end print results
    // end bfs
	return 0;
}

void dfs (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP) {
     // leaf, we evaluate the configuration
     if (vertex->index == n) {
         int cost = cycleCost(n, adjacencyMatrix, vertex->indexes);
         if (cost< *minCostP) {
             *minCostP=cost;
             free(*minIndexesP);
             *minIndexesP=vertex->indexes;
         }
         else {
             free(vertex->indexes);
         }
         free(vertex);
     }
     else {
         // for every vertex, if it doesn't exist in the cycle, we generate a new configuration
         for (int newVertexId = 0; newVertexId < n; ++newVertexId) {
             // vertex doesn't exists in the cycle
             if (vertex->indexes[newVertexId]==-1) {
                 vertex_t* new_vertex= malloc(sizeof(vertex_t));
                 new_vertex->indexes = cloneArray(n,vertex->indexes);
                 new_vertex->indexes[newVertexId]= vertex->index;
                 new_vertex->index = vertex->index +1;
                 dfs(n,adjacencyMatrix,new_vertex,minCostP,minIndexesP);
             }
         }
         free(vertex->indexes);
         free(vertex);
     }
 }

void dfsIterative (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP){
    stack_type* stack_p = constructStack();
    push(stack_p,vertex);
    while (!isEmptyStack(stack_p)){
        vertex=pop(stack_p);
        // leaf, we evaluate the configuration
        if (vertex->index==n) {
            int cost = cycleCost(n, adjacencyMatrix, vertex->indexes);
            if (cost< *minCostP) {
                *minCostP=cost;
                free(*minIndexesP);
                *minIndexesP=vertex->indexes;
            }
            else {
                free(vertex->indexes);
            }
            free(vertex);
        }
        else {
            // for every vertex, if it doesn't exist in the cycle, we generate a new configuration
            for (int newVertexId = 0; newVertexId < n; ++newVertexId) {
                // vertex doesn't exists in the cycle
                if (vertex->indexes[newVertexId]==-1) {
                    vertex_t* new_vertex= malloc(sizeof(vertex_t));
                    new_vertex->indexes = cloneArray(n,vertex->indexes);
                    (new_vertex->indexes)[newVertexId] = (vertex->index);
                    new_vertex->index = (vertex->index)+1;
                    push(stack_p,new_vertex);
                }
            }
            free(vertex->indexes);
            free(vertex);
        }
    }
    destructStack(&stack_p);
}

void bfs (int n, int** adjacencyMatrix,vertex_t* vertex, int* minCostP, int** minIndexesP){
    queue_type* queue_p = constructQueue();
    enQueue(queue_p,vertex);
    while (!isEmptyQueue(queue_p)){
        vertex=deQueue(queue_p);
        // leaf, we evaluate the configuration
        if (vertex->index==n) {
            int cost = cycleCost(n, adjacencyMatrix, vertex->indexes);
            if (cost < *minCostP) {
                *minCostP = cost;
                free(*minIndexesP);
                *minIndexesP = vertex->indexes;
            }
            else {
                free(vertex->indexes);
            }
            free(vertex);
        }
        else {
            // for every vertex, if it doesn't exist in the cycle, we generate a new configuration
            for (int newVertexId = 0; newVertexId < n; ++newVertexId) {
                // vertex doesn't exists in the cycle
                if (vertex->indexes[newVertexId]==-1) {
                    vertex_t* new_vertex= malloc(sizeof(vertex_t));
                    new_vertex->indexes = cloneArray(n,vertex->indexes);
                    new_vertex->indexes[newVertexId]= vertex->index;
                    new_vertex->index = vertex->index +1;
                    enQueue(queue_p,new_vertex);
                }
            }
            free(vertex->indexes);
            free(vertex);
        }
    }
    destructQueue(&queue_p);
}

int cycleCost (int n, int** adjacencyMatrix, int* indexes) {
    int* vertexes = indexesToVertexes(n,indexes);
    int cost=0;
    for (int i = 0; i < n; ++i) {
        cost+=adjacencyMatrix[vertexes[i]][vertexes[(i+1)%n]];
    }
    free(vertexes);
    return cost;
}

//int** getArray2D (int n) {
//    int** array = (int**) malloc(sizeof(int*)*n);
//    for (int i = 0; i < n; ++i) {
//        array[i]=(int*) malloc(sizeof(int)*n);
//    }
//    return array;
//}

int** readArray2D (char* fileName, int* n) {
    FILE* input = fopen(fileName, "r");
    if (input == NULL) {
        printf("input not found. \n");
        exit(12);
    }
    fscanf(input,"%d",n);
    int** array = (int**) malloc(sizeof(int**)*(*n));
    for (int i = 0; i < (*n); ++i) {
        array[i] = (int*) malloc(sizeof(int*)*(*n));
        for (int j = 0; j < (*n); ++j) {
            fscanf(input, "%d", &array[i][j]);
        }
    }
    fclose(input);
    return array;
}

void printArray2D (int n, int** array) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }
}

int* initializeArray (int n,int value) {
    int* array = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; ++i) {
        array[i]=value;
    }
    return array;
}

int* cloneArray (int n, int* array) {
    int* arrayClone = (int*) malloc(sizeof(int)*n);
    for (int i = 0; i < n; ++i) {
        arrayClone[i]=array[i];
    }
    return arrayClone;
}

void printArray (int n, int* array) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int* indexesToVertexes(int n,int* indexes){
    int* vertexes = malloc(sizeof(int)*n);
    for (int i = 0; i < n; ++i) {
        vertexes[indexes[i]]=i;
    }
    return vertexes;
}
