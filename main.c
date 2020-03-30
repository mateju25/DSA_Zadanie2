#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "AVLtree.h"
#include "RBtree.h"

#define COUNT 10000000

struct node *ROOT;
struct node *NILL;

void test1(NODE_AVL* paRootAVL)
{
    NODE_AVL* searchIAVL = NULL;
    struct node* searchRB = NULL;

    clock_t start_t, end_t, total_t;

    start_t = clock();
    for(int i = 0; i < COUNT; i++){
        insertAVL(&paRootAVL, i);
    }
    end_t = clock();
    printf("INSERT AVL  %20f\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);

    start_t = clock();
    for (int i = 0; i < COUNT; i++) {
        red_black_insert(i);
    }
    end_t = clock();
    printf("INSERT RB  %20f\n", (double)(-start_t + end_t) / CLOCKS_PER_SEC);

    start_t = clock();
    for(int i = 0; i < COUNT; i++){
        searchIAVL = searchAVL(&paRootAVL, i);
    }
    end_t = clock();
    printf("SEARCH AVL  %20f\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);

    start_t = clock();
    for (int i = 0; i < COUNT; i++) {
        searchRB = tree_search(i);
    }
    end_t = clock();
    printf("SEARCh RB  %20f\n", (double)(-start_t + end_t) / CLOCKS_PER_SEC);
}
void test2(NODE_AVL* paRootAVL)
{

    clock_t start_t, end_t, total_t;

    start_t = clock();
    for(int i = COUNT; i > 0; i--){
        insertAVL(&paRootAVL, i);
    }
    end_t = clock();
    printf("INSERT AVL  %20f\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);

    start_t = clock();
    for(int i = COUNT; i > 0; i--){
        red_black_insert(i);
    }
    end_t = clock();
    printf("INSERT RB  %20f\n", (double)(-start_t + end_t) / CLOCKS_PER_SEC);
}
void test3(NODE_AVL* paRootAVL)
{
    NODE_AVL* searchIAVL = NULL;
    struct node* searchRB = NULL;

    clock_t start_t, end_t, total_t;

    start_t = clock();
    for(int i = COUNT, j = 0; i > j; i--, j++){
        insertAVL(&paRootAVL, i);
    }
    end_t = clock();
    printf("INSERT AVL  %20f\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);

    start_t = clock();
    for(int i = COUNT, j = 0; i > j; i--, j++){
        red_black_insert(i);
    }
    end_t = clock();
    printf("INSERT RB  %20f\n", (double)(-start_t + end_t) / CLOCKS_PER_SEC);

    start_t = clock();
    for(int i = COUNT, j = 0; i > j; i--, j++){
        searchIAVL = searchAVL(&paRootAVL, i);
    }
    end_t = clock();
    printf("SEARCH AVL  %20f\n", (double)(-start_t + end_t)/ CLOCKS_PER_SEC);

    start_t = clock();
    for(int i = COUNT, j = 0; i > j; i--, j++){
        searchRB = tree_search(i);
    }
    end_t = clock();
    printf("SEARCh RB  %20f\n", (double)(-start_t + end_t) / CLOCKS_PER_SEC);
}
void test4(NODE_AVL* paRootAVL)
{
    double first = 0, second = 0;
    long long int val;
    clock_t start_t, end_t, total_t;
    srand(1);

    for(int i = 0; i < COUNT; i++){
        val = (rand()*rand()) % COUNT;
        start_t = clock();
        insertAVL(&paRootAVL, val);
        end_t = clock();
        first += (-start_t + end_t);
        start_t = clock();
        //red_black_insert(val);
        end_t = clock();
        second += (-start_t + end_t);
    }

    printf("INSERT AVL  %20f\n", first/ CLOCKS_PER_SEC);
    printf("INSERT RB  %20f\n", second / CLOCKS_PER_SEC);

}

int main() {
    NODE_AVL* rootAVL = NULL;

    /*Treba pre cudziu implementaciu*/
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;
    /**/

    test4(rootAVL);
    /*for(int i = 20; i > 0; i--){
        insertAVL(&rootAVL, i);
    }*//*
    printAVL(rootAVL, 10);*/
    return 0;
}
