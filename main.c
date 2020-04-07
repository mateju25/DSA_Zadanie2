#include <stdio.h>
#include <stdlib.h>
#include <windows.h>



#include "AVLtree.h"
#include "RBtree.h"
#include "BVStree.h"
#include "DoubleHash.h"
#include "LinkedHash.h"

#define COUNT 100000 //velkost vstupu
#define SAMPLE 1 //pocet opakovani testov


//cudzia implementacia RB stromu
struct node *ROOT = NULL;;
struct node *NILL = NULL;;

//cudzia implementacia hasing table-u
HASHTABLELINKED* array = NULL;
int size = 0;         /* Determines the no. of elements present in Hash Table */
int max = 10;       /* Determines the maximum capacity of Hash Table array */

void test_BVS_insertsearch(int* paSequence) {
    NODE_BVS* paRootBVS = NULL;
    NODE_BVS* searchIBVS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //Insert BVS
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteBVS(&paRootBVS);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT BVS  %20f\n", temp / SAMPLE);
    temp = 0;

    //Search BVS
    for(int i = 0; i < COUNT; i++){
        insertBVS(&paRootBVS, paSequence[i]);
    }
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            searchIBVS = searchBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteBVS(&paRootBVS);
    printf("SEARCH BVS  %20f\n", temp / SAMPLE);
    temp = 0;

    //Insert/Search BVS
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertBVS(&paRootBVS, paSequence[i]);
            searchIBVS = searchBVS(&paRootBVS, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteBVS(&paRootBVS);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH BVS  %20f\n", temp / SAMPLE);
    temp = 0;
    printf("\n");
}
void test_AVL_insertsearch(int* paSequence)
{
    NODE_AVL* paRootAVL = NULL;
    NODE_AVL* searchIAVL = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //Insert AVL
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertAVL(&paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteAVL(&paRootAVL);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT AVL  %20f\n", temp / SAMPLE);
    temp = 0;

    //Search AVL
    for(int i = 0; i < COUNT; i++){
        insertAVL(&paRootAVL, paSequence[i]);
    }
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            searchIAVL = searchAVL(&paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteAVL(&paRootAVL);
    printf("SEARCH AVL  %20f\n", temp / SAMPLE);
    temp = 0;

    //Insert/Search AVL
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertAVL(&paRootAVL, paSequence[i]);
            searchIAVL = searchAVL(&paRootAVL, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteAVL(&paRootAVL);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH AVL  %20f\n", temp / SAMPLE);
    temp = 0;
    printf("\n");
}
void test_RB_insertsearch(int* paSequence)
{
    struct node* searchRB = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //Insert RB
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            red_black_insert(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteRB(&ROOT);
        ROOT = NILL;
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT RB  %20f\n", temp / SAMPLE);
    temp = 0;

    //Sreach RB
    for(int i = 0; i < COUNT; i++){
        red_black_insert(paSequence[i]);
    }
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            searchRB = tree_search(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteRB(&ROOT);
    ROOT = NILL;
    printf("SEARCH RB  %20f\n", temp / SAMPLE);
    temp = 0;

    //Insert/Search RB
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            red_black_insert(paSequence[i]);
            searchRB = tree_search(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteRB(&ROOT);
        ROOT = NILL;
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH RB  %20f\n", temp / SAMPLE);
    temp = 0;
    printf("\n");
}
void test_OpenAdressingHash_insertsearch(int* paSequence)
{
    HASHTABLE* rootMyHash = NULL;
    int* searchHS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //insert my HashTable
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteDoubleHash(&rootMyHash);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT MY_HASH  %20f\n", temp / SAMPLE);
    temp = 0;


    //search my HashTable
    for(int i = 0; i < COUNT; i++){
        insertDoubleHash(&rootMyHash, paSequence[i]);
    }
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++) {
            searchHS = searchDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteDoubleHash(&rootMyHash);
    printf("SEARCH MY_HASH  %20f\n", temp / SAMPLE);
    temp = 0;


    //insertLinkHash my HashTable
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertDoubleHash(&rootMyHash, paSequence[i]);
            searchHS = searchDoubleHash(&rootMyHash, paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteDoubleHash(&rootMyHash);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH MY_HASH  %20f\n", temp / SAMPLE);
    temp = 0;
    printf("\n");
}
void test_LinkedListHash_insertsearch(int* paSequence){
    int* searchHS = NULL;
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double temp = 0;

    //insert LinkedHash
    for (int j = 0; j < SAMPLE; j++) {
        size = 0;
        max = 10;
        array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
        init_array();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){

            insertLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteLinkedHash();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT NOT MY HASH  %20f\n", temp / SAMPLE);
    temp = 0;

    //search linked list hash
    size = 0;
    max = 10;
    array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
    init_array();
    for(int i = 0; i < COUNT; i++){
        insertLinkedHS(paSequence[i]);
    }
    for (int j = 0; j < SAMPLE; j++) {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            searchHS = searchLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    deleteLinkedHash();
    printf("SEARCH NOT MY HASH  %20f\n", temp / SAMPLE);
    temp = 0;

    //insert/search linked list hash
    for (int j = 0; j < SAMPLE; j++) {
        size = 0;
        max = 10;
        array = (HASHTABLELINKED*) malloc (max* sizeof(HASHTABLELINKED));
        init_array();
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        for(int i = 0; i < COUNT; i++){
            insertLinkedHS(paSequence[i]);
            searchHS = searchLinkedHS(paSequence[i]);
        }
        QueryPerformanceCounter(&end);
        deleteLinkedHash();
        temp += (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }
    printf("INSERT/SEARCH NOT MY HASH  %20f\n", temp / SAMPLE);
    temp = 0;

    printf("\n");
}

//0, 1, 2, 3, 4, ..., n
int* test1_1n_sequence()
{
    printf("Postupnost od 1 po n s poctom prvkov: %d a s poctom opakovani: %d\n", COUNT, SAMPLE);
    int*p = (int*) malloc(COUNT * sizeof(int));
    for(int i = 0; i < COUNT; i++){
        *(p+i) = i;
    }
    return p;
}
//0, n, 1, n-1, .....
int* test2_change_sequence()
{
    printf("Postupnost  (0, n, 1, n-1) s poctom prvkov: %d a s poctom opakovani: %d\n", COUNT, SAMPLE);
    int*p = (int*) malloc(COUNT * sizeof(int));
    for(int i = COUNT, k = 0, j = 0; i > k; i--, k++, j += 2){
        *(p+j) = k;
        *(p+j+1) = COUNT;
    }
    return p;
}
//random sequence
int* test3_random_sequence()
{
    printf("Postupnost nahodna so seedom 1 s poctom prvkov: %d a s poctom opakovani: %d\n", COUNT, SAMPLE);
    srand(1);
    int*p = (int*) malloc(COUNT * sizeof(int));
    for(int i = 0; i < COUNT; i++) {
        *(p+i) = (rand()*rand());
    }
    return p;
}

int main() {
    //Treba pre cudziu implementaciu
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;
    int*p = NULL;
    p =  test1_1n_sequence();

    //test_BVS_insertsearch(p);
    test_AVL_insertsearch(p);
    test_RB_insertsearch(p);
    test_OpenAdressingHash_insertsearch(p);
    test_LinkedListHash_insertsearch(p);
    free(p);

    p =  test2_change_sequence();
    //test_BVS_insertsearch(p);
    test_AVL_insertsearch(p);
    test_RB_insertsearch(p);
    test_OpenAdressingHash_insertsearch(p);
    test_LinkedListHash_insertsearch(p);
    free(p);

    p =  test3_random_sequence();
    //test_BVS_insertsearch(p);
    test_AVL_insertsearch(p);
    test_RB_insertsearch(p);
    test_OpenAdressingHash_insertsearch(p);
    test_LinkedListHash_insertsearch(p);
    free(p);

    return 0;
}
