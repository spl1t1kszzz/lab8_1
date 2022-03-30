
#ifndef LAB8_2_FUNCTIONS_H
#define LAB8_2_FUNCTIONS_H

// This function makes set.
void makeSet(int* array, int* ranks, int value ) {
    *(array + value) = value;
    *(ranks + value) = 0;
}


//
int find(const int *array, int value) {
    if (value == *(array + value))
        return value;
    return find(array, *(array + value));
}



#endif //LAB8_2_FUNCTIONS_H
