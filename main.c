#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    FILE* in = fopen("in.txt", "r");
    FILE* out = fopen("out.txt", "w");
    long long numNodes, numEdges = 0;
    scanNodesAndEdges(in, out, &numNodes, &numEdges);
    edge* edges = malloc(sizeof(edge) * numEdges);
    fillEdges(in, out, edges, &numNodes, &numEdges);
    int* sets = malloc(sizeof (int) * numNodes + 1);
    initSets(sets, (int *) &numNodes);
    return 0;
}