//
// Created by Matej on 2. 4. 2020.
//

#ifndef ZADANIE2_MYHASH_H
#define ZADANIE2_MYHASH_H

#endif //ZADANIE2_MYHASH_H

typedef struct hashTable{
    int countOfNumb;
    int maxSize;
    int primeSmall;
    int* newArr;
}HASHTABLE;

void insertDoubleHash(HASHTABLE** paTable, int paVal);
void printDoubleHash(HASHTABLE* paTable);
int* searchDoubleHash(HASHTABLE** paTable, int paVal);
void deleteDoubleHash(HASHTABLE** paTable);