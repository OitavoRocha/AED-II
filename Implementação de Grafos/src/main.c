// Otávio Rocha, João Vitor Farias
// https://github.com/OitavoRocha/AED-II
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_NODES 20

int buildNodes();
void addWeight( int ** matrix, int * numNodes );
void MENU( int * option );
void PRINT( int ** matrix, int * numNodes );


int main() {
    int nodes =  buildNodes();
    int option;
    int **adjacentMatrix;

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
        printf("  3.Quit\n");
        scanf("%d", option);
    } while ( *option < 1 || *option > 3 );
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