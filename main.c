#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
    FILE* in = fopen("in.txt", "r");
    FILE* out = fopen("out.txt", "w");
    int numNodes, numEdges = 0;
    if (-1 == scanNodesAndEdges(in, out, &numNodes, &numEdges)) {
        fclose(in);
        fclose(out);
        return 0;
    }
    edge *edges = calloc(numEdges + 1, sizeof (edge));
    if (-1 == fillEdges(in,out, edges, &numNodes, &numEdges)) {
        free(edges);
        fclose(in);
        fclose(out);
        return 0;
    }
    int* sets = calloc(numNodes + 1, sizeof(int));
    initSets(sets, &numNodes);
    qsort(edges, numEdges + 1, sizeof (edge), compare);
    for (int i = 1; i < numEdges + 1; ++i) {
        if (findSet(sets, (edges + i)->first) != findSet(sets, (edges + i)->second)) {
            fprintf(out, "%d %d\n", (edges + i)->first, (edges + i)->second);
            unite(sets,(edges + i)->first, (edges + i)->second);
        }
    }
    free(sets);
    free(edges);
    fclose(in);
    fclose(out);
    return 0;
}