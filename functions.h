#ifndef LAB8_2_FUNCTIONS_H
#define LAB8_2_FUNCTIONS_H
#include <stdint.h>
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
int scanNodesAndEdges(FILE* in, FILE* out, long long* numNodes, long long* numEdges) {
    if (1 != fscanf(in, "%lld", numNodes))
        return -1;
    if (*numNodes < 0 || *numNodes > 5000) {
        fprintf(out, "%s", "bad number of vertices");
        return -1;
    }
    if (1 != fscanf(in, "%lld", numEdges))
        return -1;
    if (*numEdges < 0 || *numEdges > *numNodes * (*numNodes - 1) / 2) {
        fprintf(out, "%s", "bad number of edges");
        return -1;
    }
    return 0;
}

// This function fills edges.
int fillEdges(FILE* in, FILE* out, edge* edges, long long* numNodes, long long* numEdges) {
    short int lines = 0;
    for (int i = 1; i < (int) *numNodes + 1; ++i) {
        long long first, second, weight = 0;
        if (3 != fscanf(in, "%lld %lld %lld", &first, &second, &weight))
            return -1;
        if (first < 1 || first > *numNodes || second < 1 || second > *numNodes) {
            fprintf(out, "%s", "bad vertex");
            return -1;
        }
        if (weight > (long long) maxLen) {
            fprintf(out, "%s", "bad length");
            return -1;
        }
        (edges + i)->first = first;
        (edges + i)->second = second;
        (edges + i)->weight = weight;
        lines++;
    }
    if (lines < *numEdges + 2){
        fprintf(out, "%s", "bad number of lines");
        return -1;
    }
    return 0;
}

void initSets(int* sets, int* numNodes) {
    for (int i = 1; i < *numNodes + 1; ++i)
        *(sets + i) = i;
}



#endif //LAB8_2_FUNCTIONS_H
