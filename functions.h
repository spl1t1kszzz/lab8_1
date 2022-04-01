#ifndef LAB8_2_FUNCTIONS_H
#define LAB8_2_FUNCTIONS_H
#include <stdint.h>
#include <stdbool.h>

#define maxLen (INT32_MAX)

typedef struct {
    short int first;
    short int second;
    int weight;
} edge;

// This function makes set.
void makeSet(int* array, int value ) {
    *(array + value) = value;
}

// This function returns the set to which the element belongs.
int findSet(const int *array, int value) {
    if (value == *(array + value))
        return value;
    else return findSet(array, *(array + value));
}

// This functions unites two sets.
void unite(int* array, int first, int second) {
    first = findSet(array, first);
    second = findSet(array,second);
    *(array + first) = second;
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
    bool* tags = malloc(sizeof(bool) * *numNodes + 1);
    for (int i = 1; i < *numEdges + 1; ++i) {
        int first, second;
        long long weight;
        if (3 != fscanf(in, "%d %d %lld", &first, &second, &weight)) {
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
        if (weight >  (long long )maxLen) {
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
void initSets(int* sets, int* numNodes) {
    for (int i = 1; i < *numNodes + 1; ++i)
        makeSet(sets, i);
}

// This function need to qsort
int compare (const void * a, const void * b) {
    edge *first = (edge *)a;
    edge *second = (edge *)b;
    return ( first->weight - second->weight );
}

#endif //LAB8_2_FUNCTIONS_H