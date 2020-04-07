//
// Created by Matej on 2. 4. 2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DoubleHash.h"
#pragma GCC optimize("01")

HASHTABLE* createHash(HASHTABLE* paTable) {
    paTable = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    paTable->countOfNumb = 0;
    paTable->maxSize = 8;
    paTable->primeSmall = 7;
    paTable->newArr = (int*) malloc(sizeof(int) * paTable->maxSize);
    for (int i = 0; i < paTable->maxSize; i++) paTable->newArr[i] = -1;
    return paTable;
}

int hashFunctionFirst(HASHTABLE* paTable, int paKey) {
    return paKey % paTable->maxSize;
}

int hashFunctionSecond(HASHTABLE* paTable, int paKey) {
    return paTable->primeSmall - (paKey % paTable->primeSmall);
}

int isPrime(int paNum) {
    int flag = 1;
    for (int i = 2; i <= sqrt(paNum); i++) {
        if (paNum % i == 0) {
            flag = 0;
            break;
        }
    }
    return flag;
}

int newSizeAndPrime(HASHTABLE* paTable) {
    paTable->maxSize *= 2;
    int i = paTable->maxSize-1;
    while (!isPrime(i)) {
        i--;
    }
    paTable->primeSmall = i;
    i = paTable->maxSize+1;
    while (!isPrime(i)) {
        i++;
    }
    paTable->maxSize = i;
    return paTable->maxSize;
}

void expandTable(HASHTABLE** paTable) {
    int old = (*paTable)->maxSize;
    (*paTable)->maxSize = newSizeAndPrime(*paTable);
    (*paTable)->newArr = (int*) realloc((*paTable)->newArr, sizeof(int) * (*paTable)->maxSize);
    for (old; old < (*paTable)->maxSize; old++) (*paTable)->newArr[old] = -1;

    for (int i = 0; i < old/2; i++)
    {
        if(((*paTable)->newArr[i] != -1) && (i != hashFunctionFirst( (*paTable), (*paTable)->newArr[i])))
        {
            int num = (*paTable)->newArr[i];
            (*paTable)->newArr[i] = -1;
            insertDoubleHash(paTable, num);
            (*paTable)->countOfNumb--;
        }
    }
}


void insertDoubleHash(HASHTABLE** paTable, int paVal) {
    if ((*paTable) == NULL)
        *paTable = createHash(*paTable);
    int index = hashFunctionFirst((*paTable), paVal);
    if ((*paTable)->newArr[index] == paVal) return;

    if ((*paTable)->newArr[index] != -1) {
        int hash1 = hashFunctionFirst((*paTable), paVal);
        int hash2 = hashFunctionSecond((*paTable),paVal);
        int i = 1;
        while (1) {
            index = (hash1 + (i++)*hash2 + i) % ((*paTable)->maxSize);
            if ((*paTable)->newArr[index] == paVal) return;
            if ((*paTable)->newArr[index] == -1) break;
        }
    }

    (*paTable)->newArr[index] = paVal;
    (*paTable)->countOfNumb++;
    if (((double)(*paTable)->countOfNumb) / (*paTable)->maxSize >= 0.5) expandTable(paTable);
}

int* searchDoubleHash(HASHTABLE** paTable, int paVal) {
    if ((*paTable) == NULL)
        return NULL;
    int j = 0;
    int i = hashFunctionFirst((*paTable), paVal);
    if ((*paTable)->newArr[i] == paVal) return &((*paTable)->newArr[i]);
    int valHash = hashFunctionSecond((*paTable),i);
    while ((*paTable)->newArr[i] != -1) {
        i = (i + valHash) % (*paTable)->maxSize;
        if ((*paTable)->newArr[i] == paVal) return &((*paTable)->newArr[i]);
        if (j++ > (*paTable)->maxSize) return NULL;
    }
}

void deleteDoubleHash(HASHTABLE** paTable) {
    free((*paTable)->newArr);
    free((*paTable));
    (*paTable) = NULL;
}

void printDoubleHash(HASHTABLE* paTable) {
    printf("%d\n", paTable->maxSize);
    for (int i = 0; i < paTable->maxSize; i++) {
        printf("%d ", *(paTable->newArr + i));
    }
}