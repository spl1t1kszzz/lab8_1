#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    FILE* in = fopen("in.txt", "r");
    FILE* out = fopen("out.txt", "w");
    long long numNodes, numEdges = 0;
    scanNodesAndEdges(in, out, &numNodes, &numEdges);
    edge *edges = malloc(sizeof(edge) * numEdges);
    fillEdges(in, out, edges, &numNodes, &numEdges);
    for (int i = 1; i < numEdges + 1; ++i) {
        printf("%d %d %d\n", (edges + i)->first, (edges + i)->second, (edges + i)->weight);
    }
    int* sets = malloc(sizeof (int) * 11);
    return 0;
}