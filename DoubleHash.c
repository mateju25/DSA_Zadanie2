//
// Created by Matej Delincak on 2. 4. 2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "DoubleHash.h"
#pragma GCC optimize("01")

//vytvori hash tabulku
HASHTABLE* createHash(HASHTABLE* paTable) {
    paTable = (HASHTABLE*) malloc(sizeof(HASHTABLE));
    paTable->countOfNumb = 0;
    paTable->maxSize = 11;
    paTable->primeSmall = 7;
    paTable->newArr = (int*) malloc(sizeof(int) * paTable->maxSize);
    for (int i = 0; i < paTable->maxSize; i++) paTable->newArr[i] = -1;
    return paTable;
}
//prva hash funckia vrati cislo mod velkost pola
int hashFunctionFirst(HASHTABLE* paTable, int paKey) {
    return abs(paKey) % paTable->maxSize;
}
//druha hash funkcia
int hashFunctionSecond(HASHTABLE* paTable, int paKey) {
    return paTable->primeSmall - (abs(paKey) % paTable->primeSmall);
}
//funkcia zisti ci je cislo prvocislo
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
//funkcia nastavi novu velkost pola a taktiez prvocislo, ktore sa pouziva pri druhej hash funckii
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
//funkcia na zvacsenie tabulky
void expandTable(HASHTABLE** paTable) {
    int old = (*paTable)->maxSize;
    (*paTable)->maxSize = newSizeAndPrime(*paTable);
    int* oldArr = (*paTable)->newArr;
    (*paTable)->newArr = (int*) malloc(sizeof(int) * (*paTable)->maxSize);
    if ((*paTable)->newArr == NULL) {
        printf("Malo pamate");
        return;
    }
    for (int i = 0; i < (*paTable)->maxSize; i++) (*paTable)->newArr[i] = -1;
    //premiestni zo stareho pola do noveho
    for (int i = 0; i < old/2; i++)
    {
        if((oldArr[i] != -1) && (i != hashFunctionFirst( (*paTable), oldArr[i])))
        {
            int num = oldArr[i];
            insertDoubleHash(paTable, num);
            (*paTable)->countOfNumb--;
        }
    }
    free(oldArr);
}
//vlozi prvok do tabulky
void insertDoubleHash(HASHTABLE** paTable, int paVal) {
    if ((*paTable) == NULL)
        *paTable = createHash(*paTable);
    int index = hashFunctionFirst((*paTable), paVal);
    if ((*paTable)->newArr[index] == paVal) return;

    if ((*paTable)->newArr[index] != -1) {
        //nasla sa kolizia
        int hash1 = hashFunctionFirst((*paTable), paVal);
        int hash2 = hashFunctionSecond((*paTable),paVal);
        int i = 1;
        while (1) {
            index = (hash1 + (i++)*hash2 + i) % ((*paTable)->maxSize);
            if ((*paTable)->newArr[index] == paVal) return;
            if ((*paTable)->newArr[index] == -1) break;
        }
    }
    //vloz prvok
    (*paTable)->newArr[index] = paVal;
    (*paTable)->countOfNumb++;
    //otestuj ci netreba zvacsit
    if (((double)(*paTable)->countOfNumb) / (*paTable)->maxSize >= 0.5) expandTable(paTable);
}
//vyhlada prvok v tabulke
int* searchDoubleHash(HASHTABLE** paTable, int paVal) {
    if ((*paTable) == NULL)
        return NULL;
    int j = 0;
    int i = hashFunctionFirst((*paTable), paVal);
    if ((*paTable)->newArr[i] == paVal) return &((*paTable)->newArr[i]);
    int valHash = hashFunctionSecond((*paTable),i);
    while ((*paTable)->newArr[i] != -1) {
        //prvok sa nenasiel na indexe, pokracuj v hladani
        i = (i + valHash) % (*paTable)->maxSize;
        if ((*paTable)->newArr[i] == paVal) return &((*paTable)->newArr[i]);
        if (j++ > (*paTable)->maxSize) return NULL;
    }
}
//vymaze tabulku
void deleteDoubleHash(HASHTABLE** paTable) {
    free((*paTable)->newArr);
    free((*paTable));
    (*paTable) = NULL;
}
//vypise obsah tabulky
void printDoubleHash(HASHTABLE* paTable) {
    printf("Velkost: %d\n", paTable->maxSize);
    for (int i = 0; i < paTable->maxSize; i++) {
        printf("%d ", *(paTable->newArr + i));
    }
}