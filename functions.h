#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


typedef struct {
    short int first;
    short int second;
    int weight;
} edge;

// This functions unites two sets.
void unite(short int *sets, int numNodes, int first, int second) {
    for (int i = 1; i < numNodes + 1; i++) {
        if (*(sets + i) == first)
            *(sets + i) = second;
    }
}

// This function scans number of nodes and edges.
int scanNodesAndEdges(FILE* in, FILE* out, int* numNodes, int* numEdges) {
    if (1 != fscanf(in, "%d", numNodes))
        return -1;
    if (*numNodes < 0 || *numNodes > 5000) {
        fprintf(out, "%s", "bad number of vertices");
        return -1;
    }
    if (*numNodes == 0) {
        fprintf(out, "%s", "no spanning tree");
        return -1;
    }
    if (1 != fscanf(in, "%d", numEdges))
        return -1;
    if (*numEdges < 0 || *numEdges > *numNodes * (*numNodes - 1) / 2) {
        fprintf(out, "%s", "bad number of edges");
        return -1;
    }
    return 0;
}

// This function fills edges.
int fillEdges(FILE* in, FILE* out, edge* edges, int* numNodes, int* numEdges) {
    int lines = 0;
    bool* tags = calloc(*numNodes + 1, sizeof(bool));
    for (int i = 1; i < *numEdges + 1; ++i) {
        int first, second;
        unsigned long long weight;
        if (3 != fscanf(in, "%d %d %llu", &first, &second, &weight)) {
            if (lines < *numEdges)
                fprintf(out, "%s", "bad number of lines");
            free(tags);
            return -1;
        }
        if (first < 1 || first > *numNodes || second < 1 || second > *numNodes) {
            fprintf(out, "%s", "bad vertex");
            free(tags);
            return -1;
        }
        if (weight >  INT_MAX) {
            fprintf(out, "%s", "bad length");
            free(tags);
            return -1;
        }
        (edges + i)->first = (int)first;
        (edges + i)->second = (int)second;
        (edges + i)->weight = (int)weight;
        lines++;
        *(tags + first) = true;
        *(tags + second) = true;
    }
    for (int i = 1; i < *numNodes + 1; ++i)
        if (!*(tags + i) && *numNodes != 1) {
            fprintf(out, "%s", "no spanning tree");
            free(tags);
            return -1;
        }
    if (lines < *numEdges){
        fprintf(out, "%s", "bad number of lines");
        free(tags);
        return -1;
    }
    free(tags);
    return 0;
}

// This function inits sets array.
void initSets(short * sets, int numNodes) {
    for (int i = 1; i < numNodes + 1; ++i)
        *(sets + i) = i;
}

// This function need to qsort
int compare (const void * a, const void * b) {
    edge *first = (edge *)a;
    edge *second = (edge *)b;
    return ( first->weight - second->weight );
}

// This is the Kruskal's algorithm.
void kruskal(FILE* out, short int* sets, edge* edges, int numNodes, int numEdges) {
    for (int i = 1; i < numEdges + 1; ++i) {
        if (*(sets + (edges + i)->first) != *(sets + (edges + i)->second)) {
            fprintf(out, "%d %d\n", (edges + i)->first, (edges + i)->second);
            unite(sets, numNodes, *(sets + (edges + i)->first), *(sets + (edges + i)->second));
        }
    }
}

