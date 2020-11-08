#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



#include "AVLtree.h"
#include "RBtree.h"
#include "BVStree.h"
#include "DoubleHash.h"
#include "LinkedHash.h"

#define COUNT 1000000//velkost vstupu
#define SAMPLE 1
//pocet opakovani testov


//cudzia implementacia RB stromu
struct node *ROOT = NULL;;
struct node *NILL = NULL;;

//cudzia implementacia hasing table-u
HASHTABLELINKED* array = NULL;
int size = 0;         /* Determines the no. of elements present in Hash Table */
int max = 10;       /* Determines the maximum capacity of Hash Table array */

//otestuje nevyvazeny strom na insert, search a kombinovane
void test_BVS_insertsearch(int* paSequence, int countOfNums, int statisticNum) {
    NODE_BVS* paRootBVS = NULL;
    NODE_BVS* searchIBVS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;
    if (countOfNums > 100000) printf("Pozor... tento algoritmus moze trvat dlho.\n");
    //Insert BVS
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        if (deleteBVS(&paRootBVS) == 0) {
            printf("BVS strom sa nepodarilo uvolnit cely - hlbka je prilis velka.\n");
        }

        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT BVS  %20f\n", temp / statisticNum);
    temp = 0;

    //Search BVS
    for(int i = 0; i < countOfNums; i++){
        insertBVS(&paRootBVS, paSequence[i]);
    }
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            searchIBVS = searchBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    if (deleteBVS(&paRootBVS) == 0) {
        printf("BVS strom sa nepodarilo uvolnit cely - hlbka je prilis velka.\n");
    }
    printf("SEARCH BVS  %20f\n", temp / statisticNum);
    temp = 0;

    //Insert/Search BVS
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertBVS(&paRootBVS, paSequence[i]);
            searchIBVS = searchBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        if (deleteBVS(&paRootBVS) == 0) {
            printf("BVS strom sa nepodarilo uvolnit cely - hlbka je prilis velka.\n");
        }
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH BVS  %20f\n", temp / statisticNum);
    temp = 0;
    printf("\n");
}
//otestuje AVL strom na insert, search a kombinovane
void test_AVL_insertsearch(int* paSequence, int countOfNums, int statisticNum)
{
    NODE_AVL* paRootAVL = NULL;
    NODE_AVL* searchIAVL = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //Insert AVL
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertAVL(&paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteAVL(&paRootAVL);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT AVL  %20f\n", temp / statisticNum);
    temp = 0;

    //Search AVL
    for(int i = 0; i < countOfNums; i++){
        insertAVL(&paRootAVL, paSequence[i]);
    }
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            searchIAVL = searchAVL(paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteAVL(&paRootAVL);
    printf("SEARCH AVL  %20f\n", temp / statisticNum);
    temp = 0;

    //Insert/Search AVL
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertAVL(&paRootAVL, paSequence[i]);
            searchIAVL = searchAVL(paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteAVL(&paRootAVL);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH AVL  %20f\n", temp / statisticNum);
    temp = 0;
    printf("\n");
}
//otestuje cerveno-cierny strom na insert, search a kombinovane
void test_RB_insertsearch(int* paSequence, int countOfNums, int statisticNum)
{
    struct node* searchRB = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //Insert RB
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            red_black_insert(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteRB(&ROOT);
        ROOT = NILL;
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT RB  %20f\n", temp / statisticNum);
    temp = 0;

    //Search RB
    for(int i = 0; i < countOfNums; i++){
        red_black_insert(paSequence[i]);
    }
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            searchRB = tree_search(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteRB(&ROOT);
    ROOT = NILL;
    printf("SEARCH RB  %20f\n", temp / statisticNum);
    temp = 0;

    //Insert/Search RB
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            red_black_insert(paSequence[i]);
            searchRB = tree_search(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteRB(&ROOT);
        ROOT = NILL;
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH RB  %20f\n", temp / statisticNum);
    temp = 0;
    printf("\n");
}
//otestuje hash s otvorenu adresaciu na insert, search a kombinovane
void test_OpenAdressingHash_insertsearch(int* paSequence, int countOfNums, int statisticNum)
{
    HASHTABLE* rootMyHash = NULL;
    int* searchHS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //insert my HashTable
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteDoubleHash(&rootMyHash);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT DOUBLE HASHING  %20f\n", temp / statisticNum);
    temp = 0;


    //search my HashTable
    for(int i = 0; i < countOfNums; i++){
        insertDoubleHash(&rootMyHash, paSequence[i]);
    }
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++) {
            searchHS = searchDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteDoubleHash(&rootMyHash);
    printf("SEARCH DOUBLE HASHING  %20f\n", temp / statisticNum);
    temp = 0;


    //insertLinkHash my HashTable
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertDoubleHash(&rootMyHash, paSequence[i]);
            searchHS = searchDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteDoubleHash(&rootMyHash);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH DOUBLE HASHING  %20f\n", temp / statisticNum);
    temp = 0;
    printf("\n");
}
//otestuje hash so zretazenim na insert, search a kombinovane
void test_LinkedListHash_insertsearch(int* paSequence, int countOfNums, int statisticNum){
    int* searchHS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //insert LinkedHash
    for (int j = 0; j < statisticNum; j++) {
        size = 0;
        max = 10;
        array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
        init_array();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){

            insertLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteLinkedHash();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT LINKED LIST HASH  %20f\n", temp / statisticNum);
    temp = 0;

    //search linked list hash
    size = 0;
    max = 10;
    array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
    init_array();
    for(int i = 0; i < countOfNums; i++){
        insertLinkedHS(paSequence[i]);
    }
    for (int j = 0; j < statisticNum; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            searchHS = searchLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteLinkedHash();
    printf("SEARCH LINKED LIST HASH  %20f\n", temp / statisticNum);
    temp = 0;

    //insert/search linked list hash
    for (int j = 0; j < statisticNum; j++) {
        size = 0;
        max = 10;
        array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
        init_array();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < countOfNums; i++){
            insertLinkedHS(paSequence[i]);
            searchHS = searchLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteLinkedHash();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH LINKED LIST HASH  %20f\n", temp / statisticNum);
    temp = 0;

    printf("\n");
}

//0, 1, 2, 3, 4, ..., n
int* test1_1n_sequence(int countOfNums, int statisticNum)
{
    printf("Postupnost od 1 po n s poctom prvkov: %d a s poctom opakovani: %d\n", countOfNums, statisticNum);
    int*p = (int*) malloc(countOfNums * sizeof(int));
    for(int i = 0; i < countOfNums; i++){
        *(p+i) = i;
    }
    return p;
}
//0, n, 1, n-1, .....
int* test2_change_sequence(int countOfNums, int statisticNum)
{
    printf("Postupnost  (0, n, 1, n-1) s poctom prvkov: %d a s poctom opakovani: %d\n", countOfNums, statisticNum);
    int*p = (int*) malloc(countOfNums * sizeof(int));
    for(int i = countOfNums, k = 0, j = 0; i > k; i--, k++, j += 2){
        *(p+j) = k;
        *(p+j+1) = i;
    }
    return p;
}
//random sequence
int* test3_random_sequence(int countOfNums, int statisticNum)
{
    printf("Postupnost nahodna so seedom 1 s poctom prvkov: %d a s poctom opakovani: %d\n", countOfNums, statisticNum);
    srand(1);
    int*p = (int*) malloc(countOfNums * sizeof(int));
    for(int i = 0; i < countOfNums; i++) {
        *(p+i) = (rand()*rand());
    }
    return p;
}

//vypise vsetkych 5 implementacii na nahodnej vzorke s velkostou 50, ako dokaz ze vsetko funguje
void test_function() {
    int* paSequence = test3_random_sequence(50, 1);
    printf("BVS strom ---------------------------------------------------------- \n");
    NODE_BVS* paRootBVS = NULL;
    for(int i = 0; i < 50; i++){
        insertBVS(&paRootBVS, paSequence[i]%100);
    }
    printBVS(paRootBVS, 10);
    deleteBVS(&paRootBVS);

    printf("\nAVL strom: ----------------------------------------------------------\n");
    NODE_AVL* paRootAVL = NULL;
    for(int i = 0; i < 50; i++){
        insertAVL(&paRootAVL, paSequence[i]%100);
    }
    printAVL(paRootAVL, 10);
    deleteAVL(&paRootAVL);

    printf("\nRB strom: ----------------------------------------------------------\n");
    for(int i = 0; i < 50; i++){
        red_black_insert(paSequence[i]%100);
    }
    printRB(ROOT, 10);
    deleteRB(&ROOT);
    ROOT = NILL;

    printf("\nDOUBLE HASHING tabulka: ----------------------------------------------------------\n");
    HASHTABLE* rootMyHash = NULL;
    for(int i = 0; i < 50; i++){
        insertDoubleHash(&rootMyHash, paSequence[i]%100);
    }
    printDoubleHash(rootMyHash);
    deleteDoubleHash(&rootMyHash);

    size = 0;
    max = 10;
    array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
    init_array();
    printf("\nLINKED LIST HASHING tabulka: ----------------------------------------------------------\n");
    for(int i = 0; i < 50; i++){
        insertLinkedHS(paSequence[i]%100);
    }
    display();
    deleteLinkedHash();
}

int main() {
    //Treba pre cudziu implementaciu
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;
    int*p = NULL;

    //testovanie funkcnosti
    //test_function();

    //testovanie linearnej postupnosti
    p =  test1_1n_sequence(COUNT, SAMPLE);
    //test_BVS_insertsearch(p, COUNT, SAMPLE);
    test_AVL_insertsearch(p, COUNT, SAMPLE);
    test_RB_insertsearch(p, COUNT, SAMPLE);
    test_OpenAdressingHash_insertsearch(p, COUNT, SAMPLE);
    test_LinkedListHash_insertsearch(p, COUNT, SAMPLE);
    free(p);

    //testovanie striedavej postupnosti
    p =  test2_change_sequence(COUNT, SAMPLE);
    //test_BVS_insertsearch(p, COUNT, SAMPLE);
    test_AVL_insertsearch(p, COUNT, SAMPLE);
    test_RB_insertsearch(p, COUNT, SAMPLE);
    test_OpenAdressingHash_insertsearch(p, COUNT, SAMPLE);
    test_LinkedListHash_insertsearch(p, COUNT, SAMPLE);
    free(p);

    //testovanie nahodnej postupnosti
    p =  test3_random_sequence(COUNT, SAMPLE);
    test_BVS_insertsearch(p, COUNT, SAMPLE);
    test_AVL_insertsearch(p, COUNT, SAMPLE);
    test_RB_insertsearch(p, COUNT, SAMPLE);
    test_OpenAdressingHash_insertsearch(p, COUNT, SAMPLE);
    test_LinkedListHash_insertsearch(p, COUNT, SAMPLE);
    free(p);

    return 0;
}
