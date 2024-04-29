#pragma once
#include "vector.h"

tPair Pair_Create(Key key, Value value) {
    tPair pair;
    pair.key = key;

    memcpy(pair.value, value, sizeof(Value));

    return pair;
}

tVector Vector_Create() {
    tVector vector;
    vector.count = 0;
    vector.capacity = 2;
    vector.pairs = (tPair*)calloc(vector.capacity, sizeof(tPair));
    return vector;
}

void Vector_IncreaseCapacity(tVector* vector) {
    int current = vector->capacity;
    int next = current * 2;
    
    tPair* newArray = calloc(next, sizeof(tPair));
    memcpy(newArray, vector->pairs, vector->capacity * sizeof(tPair));
    free(vector->pairs);

    vector->pairs = newArray;
    vector->capacity = next;
}

void Vector_Add(tVector* vector, tPair pair) {
    if (vector->count + 1 > vector->capacity) {
        Vector_IncreaseCapacity(vector);
    }
    vector->pairs[vector->count++] = pair;
}

void Vector_PushFront(tVector* vector, tPair pair) {
    if (vector->count + 1 < vector->capacity) {
        Vector_IncreaseCapacity(vector);
    }
    for (int i = vector->count - 1; i >= 0 ; i--) {
        vector->pairs[i + 1] = vector->pairs[i];
    }
    vector->pairs[0] = pair;
    vector->count++;
}

void switchPairs(tPair* a, tPair* b) {
    tPair c = *a;
    *a = *b;
    *b = c;
}

void Vector_Sort(tVector* vector) {
    int offset = vector->count / 2;
    while (offset > 0)
    {
        for (int end = offset; end < vector->count; end++)
        {
            int i = end;
            while (i >= offset)
            {
                if (vector->pairs[i].key < vector->pairs[i - offset].key)
                {
                    switchPairs(&vector->pairs[i], &vector->pairs[i - offset]);
                    // Vector_PrintDebug(vector);
                }
                i -= offset;
            }
        }
        offset /= 2;
    }
}

void Vector_PrintDebug(tVector* vector) {
    printf("Keys (%i): ", vector->count);
    if (vector->count >= 1)
        printf("%lli", vector->pairs[0].key);
    for (int i = 1; i < vector->count; i++)
    {
        printf(", %lli", vector->pairs[i].key);
    }
    printf("\n");
}

void Vector_Print(tVector* vector) {
    printf("Key\tValue\n");
    for (int i = 0; i < vector->count; i++)
    {
        printf("%lli\t%s\n", vector->pairs[i].key, vector->pairs[i].value);
    }
}

tPair* Vector_BinarySearch(tVector* vector, Key key)
{
    int step = vector->count / 2;
    int i = step;
    while (step > 0) {
        step /= 2;
        if (vector->pairs[i].key > key) {
            i += step;
        } else if (vector->pairs[i].key == key) {
            return &vector->pairs[i];
        } else {
            i -= step;
        }
    }

    return NULL;
}