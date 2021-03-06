#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"
#define EMPTY -1

// The gravy train
void breadthFirst( int ** matrix, int startVertex, int matrixSize , struct queue * q );
void depthFirst(int ** matrix, int startVertex, int matrixSize, struct stack s);
void depthFirstRecursive(int ** matrix, int vertex, int matrixSize, int * visited );
int * getAdjacent(int ** matrix, int matrixSize, int vertex);

// Utilities
int ** readIn(int n);
int readGraph();
void printMatrix(int ** matrix, int n);

int main(){
    int numGraphs = 0 ;
    scanf("%d",&numGraphs);

    int i = 0 ;
    for ( i = 0 ; i < numGraphs ; i++ ){
        readGraph();
    }
}



void breadthFirst( int ** matrix, int startVertex, int matrixSize , struct queue * q ){
    // Initialize variables required
    int dq ;                        // Used to hold dequeued values
    int visited[matrixSize] ;       // Array used to keep track of visited vertexes
    int i = 0 ;                     // Used for the for loop
    for ( i = 0 ; i < matrixSize ; i++ ) visited[i] = 0 ;   // Fill the newly visited array with 0's (for false)

    // Enqueue the first vertex and mark as visited
    enqueue(q,startVertex);
    visited[startVertex] = 1 ;

    // While the queue is not empty
    while (!queue_empty(q)){
        // Dequeue and print dequeued value
        dq = dequeue(q);
        printf("%d ",dq);

        int j = 0 ;

        /*
         * Move to row # dq, and for each unvisited 1 in that row, add the column # to the queue and
         * mark as visited.
         */
        for ( j = 0 ; j < matrixSize ; j++ ){
            // if there is a 1 in row # dq and column # j that is unvisited, add to queue and mark as visited
            if ( matrix[dq][j] == 1 && visited[j] == 0 ){
                enqueue(q,j);
                visited[j] = 1 ;
            }
        }
    }
}


/*
 * All vertices, except the first, is printed and marked as visited when it is pushed to the stack
 */
void depthFirst(int ** matrix, int startVertex, int matrixSize, struct stack s){
    // Initialize variables required
    int * visited = (int *) malloc(sizeof(int)*matrixSize); // Array to hold visited vertices
    int i = 0 ; // Used for the for loop
    for ( i = 0 ; i < matrixSize ; i++ ) visited[i] = 0 ; // Fill the visited array with 0's (for false)

    // Push the starting index onto the stack and mark as visited
    push(&s,startVertex);
    visited[startVertex]= 1;
    printf("%d ",startVertex);

    int vertex ;            // Holds popped off vertices
    // while the stack isn't empty
    while (!empty(&s)){
        vertex = pop(&s);   // Pop one off the stack

        /* For every element in the row of 'vertex', if matrix contains a 1 and it is unvisited
         * push it to the stack, mark as visited, and then print it.                            */
        for ( i = 0 ; i < matrixSize ; i++ ){
            if ((matrix[vertex][i]==1) && (visited[i]==0)) {
                push(&s,i);
                visited[i] = 1;
                printf("%d ",i);
            }
        }
    }
}

void depthCaller( int ** matrix , int matrixSize ){
    int * visited = (int *) malloc(sizeof(int)*matrixSize);

    int i = 0 ;
    for ( i = 0 ; i < matrixSize ; i++ ) visited[i] = '0' ;

    while ( visited + i != NULL ){
        if ( *(visited+i) == '0' ){
            depthFirstRecursive(matrix,i,matrixSize,visited);
        }
        i++ ;
    }
}
void depthFirstRecursive(int ** matrix, int vertex, int matrixSize, int * visited ){
    int * adj = getAdjacent(matrix,matrixSize,vertex);
    int i = 0 ;
    visited[vertex] = 1 ;
    printf("%d ",vertex);
    for ( i = 0 ; i < matrixSize ; i++ ){
        if ( adj[i]  != -1 ){
            if (visited[adj[i]] == 0 ) {
                depthFirstRecursive(matrix,i,matrixSize,visited);
            }
        }
    }
}

int topological(int ** matrix, int matrixSize ){
    int i, j ;

    int excludes[matrixSize] ;
    for ( i = 0 ; i < matrixSize ; i++) excludes[i] = 0 ;

    for ( i = 0 ; i < matrixSize ; i++ ) {
        // Only visit rows that aren't marked in excludes
        if ( excludes[i] != 1 ){
            // if in columns we find a 1 that isn't excluded then
            // it doesn't contain only zeros
            for ( j = 0 ; j < matrixSize ; j++ ){
                if ( matrix[i][j] == 1 && excludes[j] != 1 ){
                    break ;
                }
            }
            // If control reaches here, and j == matrixSize then we know that row
            // i only contained 0's, with exclusion of indices marked in excludes
            // array.
            if ( j == matrixSize ){
                excludes[i] = 1 ;
                // repeat
                i = 0 ;
            }
        }
    }
}


int * getAdjacent(int ** matrix, int matrixSize, int vertex){
    int i = 0 ;
    int m = 0 ;
    int * adj = (int *)malloc(sizeof(int)*matrixSize);
    for ( i = 0 ; i < matrixSize ; i++ ){
        if (matrix[vertex][i] == 1 ){
            adj[m] = i ;
            m++ ;
        }
    }
    for ( ; m < matrixSize ; m++ ){
        adj[m] = -1 ;
    }
    return adj ;
}





int readGraph(){
    int startVertex = 0 ;
    int n = 0 ;
    scanf("%d",&startVertex);
    scanf("%d",&n);

    int ** matrix = readIn(n);
    printMatrix(matrix,n);

    struct queue* q = (struct queue*)malloc(sizeof(struct queue));
    init(q);
    struct stack stk;
    initialize(&stk);
    int * visited = (int *) malloc(sizeof(int)*n);
    int i = 0 ;
    for ( i = 0 ; i < n ; i++ ) visited[i] = 0 ;

    printf("\nBreadth First: ");
    breadthFirst(matrix,startVertex,n,q);


    printf("\nDepth First: ");
    depthFirst(matrix,startVertex,n,stk);
    printf("\nDepth First: ");
    depthCaller(matrix,n);
    printf("\n");

    free(q);
    free(visited);
    free(matrix);

    return 0 ;
}
int ** readIn(int n){
    int ** matrix = (int **)malloc(sizeof(int *)*n);
    int i = 0 ;
    for ( i = 0 ; i < n ; i++ ){
        *(matrix+i) = (int *)malloc(sizeof(int)*n);
        int j = 0 ;
        for ( j = 0 ; j < n ; j++ ){
            scanf("%d",(*(matrix+i)+j));
        }
    }
    return matrix ;
}
void printMatrix(int ** matrix, int n){
    int i, j ;
    i = 0 ;
    j = 0 ;
    printf("\n-----------------------------\n");
    printf(  "-----------Matrix------------\n");
    printf(  "-----------------------------\n");
    for ( i = 0 ; i < n ; i++ ){
        for ( j = 0 ; j < n ; j++ ){
            printf("%d ",*(*(matrix+i)+j));
        }
        printf("\n");
    }
    printf("\n");
}
