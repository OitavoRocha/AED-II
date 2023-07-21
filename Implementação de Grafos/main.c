// Otávio Rocha, João Vitor Farias
// https://github.com/OitavoRocha/AED-II

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NODES 20
#define INT_MAX 99999

typedef struct {
    int distance;
    int previousNode;
}data;

int buildNodes();
void addWeight( int ** matrix, int * numNodes );
void MENU( int * option );
void PRINT( int ** matrix, int * numNodes );
void dijkstra(int numNodes, int startingNode, int endingNode, int **matrix);

void dijkstra(int numNodes, int startingNode, int endingNode, int **matrix){

    int unvisitedNodes[numNodes];
    data table[numNodes];
    int smallestDistance = INT_MAX;
    int smallestDistanceIdx;

    for (int i = 0; i < numNodes; i++){
        unvisitedNodes[i] = i;
        if (i == startingNode){
            table[i].distance = 0;
        }
        else{
            table[i].distance = INT_MAX;
        }
    }

    for (int p = 0; p < numNodes; p++){
        for (int i = 0; i < numNodes; i++){
            if (unvisitedNodes[i] != -1){ // nodo não foi visitado e é valido
                if (table[i].distance < smallestDistance){
                    smallestDistance = table[i].distance;
                    smallestDistanceIdx = i;
                }
            }
        }
        for (int j = 0; j < numNodes; j++){
            if (matrix[smallestDistanceIdx][j] != 0 && unvisitedNodes[j] != -1){ // verificando vizinhos
                if (table[smallestDistanceIdx].distance + matrix[smallestDistanceIdx][j] < table[j].distance){
                    table[j].distance = table[smallestDistanceIdx].distance + matrix[smallestDistanceIdx][j];
                    table[j].previousNode = smallestDistanceIdx;
                }
            }
        }
        unvisitedNodes[smallestDistanceIdx] = -1;
        smallestDistance = INT_MAX;
    }

    printf("The shortest distance from %d to %d is: %d\n", startingNode, endingNode, table[endingNode].distance);
}

int main() {
    int nodes =  buildNodes();
    int option;
    int **adjacentMatrix;
    int start, end;

    adjacentMatrix = ( int ** )malloc( sizeof( int * ) * nodes );
    for( int i = 0 ; i < nodes ; ++i )
        adjacentMatrix[i] = ( int *)calloc( nodes, sizeof( int ) );
    
    while ( 1 ) {
        MENU( &option );

        switch (option) {
            case 1:
                addWeight(adjacentMatrix, &nodes);
                break;
            case 2:
                PRINT( adjacentMatrix, &nodes );
                break;
            case 3:
                printf("Starting node: ");
                scanf("%d", &start);
                printf("Ending node: ");
                scanf("%d", &end);
                dijkstra(nodes, start, end, adjacentMatrix);
                break;
            case 4:
                return 0;
                break;
        } 
    }
}


void addWeight( int ** matrix, int * numNodes ) {

    int node1, node2, weight;
    int flag;

    do{
        
        flag = 0;
        printf("Node 1: ");
        scanf("%d", &node1);
    
        printf("Node 2: ");
        scanf("%d", &node2);

        if( ( node1 >= *numNodes || node1 < 0 ) || ( node2 >= *numNodes || node2 < 0 ) ) {
            printf("Numbers of nodes are incorrect! Try again.\n");
            flag = 1;
        }
        
    }   while(flag);

    do{
        
        printf("Weight: ");
        scanf("%d", &weight);
        
    }   while(weight < 0);

    matrix[node1][node2] = weight;
    matrix[node2][node1] = weight;
}


int buildNodes(){
    int numNodes;

    do{   
        printf("Number of nodes: ");
        scanf("%d", &numNodes);
    } while(numNodes > 20 || numNodes < 0);

    return numNodes;
}

void MENU( int * option ) {
    do {
        printf("+------MENU------+\n");
        printf("  1.Add weight\n");
        printf("  2.Print\n");
        printf("  3.Algoritmo de Dijkstra\n");
        printf("  4.Quit\n");
        scanf("%d", option);
    } while ( *option < 1 || *option > 4 );
}


void PRINT( int ** matrix, int * numNodes ) {
    for ( int p = 0; p < *numNodes; ++p ) {
        for ( int t = 0; t < *numNodes; ++t ) {
            if ( !matrix[p][t] ) {
                printf("[  ] ");
            } else {
                if ( matrix[p][t] > 9 )
                    printf("[%d] ", matrix[p][t]);
                else 
                    printf("[%d ] ", matrix[p][t]);
            }
        }
        printf("\n");
    }
}