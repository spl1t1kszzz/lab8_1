#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#define maxLen (INT32_MAX)


int main() {
    int* sets = malloc(sizeof (int) * 11);
    int* ranks = malloc(sizeof (int) * 11);
    makeSet(sets, 1);
    for (int i = 1; i < 11; ++i)
        *(sets + i) = i;
    for (int i = 1; i < 11; ++i) {
        printf("%d ", *(sets + i));

    }
    return 0;
}