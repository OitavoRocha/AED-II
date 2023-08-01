// Otávio Rocha, João Vitor Farias e Leonardo Melo
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

typedef struct{
    int row;
    int column;
    int value;
}pos;
pos *Weights;

int buildNodes();
void addWeight( int ** matrix, int * numNodes, int * numEdges);
void MENU( int * option );
void PRINT( int ** matrix, int * numNodes );
void dijkstra( int numNodes, int startingNode, int endingNode, int **matrix, int numEdges);
void kruskal( int numEdges, int nodes );
void prim( int ** matrix, int nodes, int numEdges);
pos *posMerge( pos *leftArr, pos *rightArr, int n, int leftSize, int rightSize );
pos *posMergeSort( pos *array, int n );
int find( int idx, int *parents );
int *union_( int *parents, int left, int right );

void kruskal( int numEdges, int nodes ) {

    if (numEdges == 0){
        return;
    }
    
    printf("numEdges: %d\n", numEdges);
    printf("nodes: %d\n", nodes);

    int *parents = malloc(sizeof(int) * nodes);
    int cost = 0;
    int **minSpanTree;
    
    minSpanTree = ( int ** )malloc( sizeof( int * ) * nodes );
    for( int i = 0 ; i < nodes ; ++i )
    minSpanTree[i] = ( int *)calloc( nodes, sizeof( int ) );

    for (int i = 0; i < nodes; i++){ // Inicializando a lista do union-find
        parents[i] = -1;
    }

    pos *orderedWeights = (pos *)malloc(sizeof(pos) * numEdges); 
    orderedWeights = posMergeSort(Weights, numEdges);

    for (int i = 0; i < numEdges; i++){
        if (find(orderedWeights[i].row, parents) != find(orderedWeights[i].column, parents)){
            parents = union_(parents, find(orderedWeights[i].row, parents), find(orderedWeights[i].column, parents));
            minSpanTree[orderedWeights[i].row][orderedWeights[i].column] = orderedWeights[i].value;
            minSpanTree[orderedWeights[i].column][orderedWeights[i].row] = orderedWeights[i].value;
            cost += orderedWeights[i].value;
        }
    }

    printf("Tree Cost: %d\n", cost);
    printf("Matrix: \n");
    PRINT(minSpanTree, &nodes);

}

int find(int idx, int *parents){

    while (parents[idx] >= 0){
        idx = parents[idx];
    }
    return idx;
}

int *union_(int *parents, int left, int right){

    parents[right] = left;
    return parents;
}

void prim( int ** matrix, int nodes, int numEdges) {

    if (numEdges == 0){
        return;
    }

    int parents[nodes];
    int minKey, x, y;
    int cost = 0;

    for( int i = 0 ; i<nodes ; i++ ) 
        parents[i] = 0;
    
    parents[0] = 1;

    int i = 0;
    printf("Minimun Spanning Tree:\nEdge\tWeight\n");
    while ( i < nodes - 1 ) {
        minKey = INT_MAX;

        x = 0, y = 0;

        for( int j = 0 ; j<nodes ; j++ ) {
            if ( parents[j] == 1 ) {
                for ( int k = 0 ; k<nodes ; k++ ) {                    
                    if( parents[k] == 0 && matrix[j][k] ) {
                        if( minKey > matrix[j][k] ) {
                            minKey = matrix[j][k];
                            x = j, y = k;
                        }
                    }
                }
            }
        }

        printf("%d - %d -- %d\n", x, y, matrix[x][y]);
        cost += matrix[x][y];
        parents[y] = 1;
        i++;
    }

    printf("Tree Cost: %d\n", cost);
}


void dijkstra(int numNodes, int startingNode, int endingNode, int **matrix, int numEdges){

    if (numEdges == 0){
        return;
    }

    int unvisitedNodes[numNodes];
    data table[numNodes];
    table[startingNode].previousNode = -1; // o começo não tem nó anterior
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

    while (table[endingNode].previousNode != -1){
        printf("%d -> ", endingNode);
        endingNode = table[endingNode].previousNode;
    }
    printf("%d\n", endingNode);
}

int main() {
    int nodes = buildNodes();
    int option;
    int **adjacentMatrix;
    int start, end;
    int numEdges = 0;

    Weights = (pos*)malloc( sizeof(pos) );
    adjacentMatrix = ( int ** )malloc( sizeof( int * ) * nodes );
    for( int i = 0 ; i < nodes ; ++i )
        adjacentMatrix[i] = ( int *)calloc( nodes, sizeof( int ) );
    
    while ( 1 ) {
        MENU( &option );

        switch (option) {
            case 1:
                addWeight(adjacentMatrix, &nodes, &numEdges);
                break;
            case 2:
                PRINT( adjacentMatrix, &nodes );
                break;
            case 3:
                printf("Starting node: ");
                scanf("%d", &start);
                printf("Ending node: ");
                scanf("%d", &end);
                dijkstra(nodes, start, end, adjacentMatrix, numEdges);
                break;
            case 4:
                kruskal(numEdges, nodes);
                break;
            case 5:
                prim(adjacentMatrix, nodes, numEdges);
                break;
            case 6:
                return 0;
                break;
        } 
    }
}


void addWeight( int ** matrix, int * numNodes, int * numEdges ) {

    int node1, node2, weight;
    int flag;
    int NodesInGraph = 0;

    if ( (*numEdges) != 0 ){
        Weights = (pos *)realloc(Weights, sizeof(pos) * ((*numEdges) + 1));
    }

    do{
        
        flag = 0;
        printf("Node 1: ");
        scanf("%d", &node1);
    
        printf("Node 2: ");
        scanf("%d", &node2);

        if( (( node1 >= *numNodes || node1 < 0 ) || ( node2 >= *numNodes || node2 < 0 ))  || (node1 == node2)) {
            printf("Numbers of nodes are incorrect! Try again.\n");
            flag = 1;
        }
        
    }   while(flag);

    do{
        
        printf("Weight: ");
        scanf("%d", &weight);
        
    }   while(weight < 0);



    Weights[(*numEdges)].row = node1;
    Weights[(*numEdges)].column = node2;
    Weights[(*numEdges)].value = weight;

    for (int i = 0; i < *numEdges; i++){
        if (node1 == Weights[i].row || node1 == Weights[i].column){
            if (node2 == Weights[i].column || node2 == Weights[i].row){
                NodesInGraph = 1;
            }
        }
    }
    if (!NodesInGraph){
        (*numEdges)++;
    }
    
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
        printf("  4.Kruskal\n");
        printf("  5.Prim\n");
        printf("  6.Quit\n");
        scanf("%d", option);
    } while ( *option < 1 || *option > 6 );
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

pos *posMerge(pos *leftArr, pos *rightArr, int n, int leftSize, int rightSize) {

    pos *output = (pos*)malloc(sizeof(pos) * n);
    int i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        if (leftArr[l].value < rightArr[r].value) {
            output[i] = leftArr[l]; 
            i++;
            l++;
        } else {
            output[i] = rightArr[r];
            i++;
            r++;
        }
    }
    while (l < leftSize) {
        output[i] = leftArr[l];
        i++;
        l++;
    }
    while (r < rightSize) {
        output[i] = rightArr[r];
        i++;
        r++;
    }

    return output;
}

pos *posMergeSort(pos *array, int n) {

    if (n <= 1) {
        return array;
    }

    int mid = n / 2;
    pos *left = (pos *)malloc(sizeof(pos) * mid);
    pos *right = (pos *)malloc(sizeof(pos) * (n - mid));
    pos *resultado;
    int idx = 0;

    for (int i = 0; i < mid; i++) {
        left[i] = array[i];
    }
    for (int j = mid; j < n; j++) {
        right[idx] = array[j];
        idx++;
    }

    left = posMergeSort(left, mid);
    right = posMergeSort(right, n - mid);
    resultado = posMerge(left, right, n, mid, n - mid);

    return resultado;
}
