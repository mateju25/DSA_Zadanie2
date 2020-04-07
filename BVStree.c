//
// Created by Matej on 7. 4. 2020.
//

#include <stdlib.h>
#include <stdio.h>
#include "BVStree.h"
#pragma GCC optimize("01")//optimalizacia kompilera

NODE_BVS* createBVS()
{
    NODE_BVS* paAct = (NODE_BVS*)malloc(sizeof(NODE_BVS));
    if (paAct == NULL){
        printf("Malo pamate.");
        return NULL;
    }
    paAct->right = paAct->left = NULL;
    return paAct;
};

void insertBVS(NODE_BVS** root, int paVal)
{
    if (*root == NULL)
    {
        *root = createBVS();
        if ((*root)!=NULL)
            (*root)->value = paVal;
    }
    else
    {
        if ((*root)->value > paVal) {
            insertBVS(&((*root)->left), paVal);
        }
        if ((*root)->value < paVal){
            insertBVS(&((*root)->right), paVal);
        }
        if ((*root)->value == paVal) return;
    }
};

void printBVS(NODE_BVS *root, int space) {
    if (root == NULL)
        return;

    space += 10;
    printBVS(root->right, space);
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);
    printBVS(root->left, space);
}
NODE_BVS* searchBVS(NODE_BVS** root, int paVal) {
    if (*root == NULL) {
        return NULL;
    } else {
        if ((*root)->value == paVal)  return (*root);
        if ((*root)->value > paVal)
            return searchBVS(&((*root)->left), paVal);
        else
            return searchBVS(&((*root)->right), paVal);

    }
}

void deleteBVS(NODE_BVS** root)
{
    if ((*root)->right != NULL) {
        deleteBVS(&((*root)->right));
        (*root)->right = NULL;
    }
    if ((*root)->left != NULL) {
        deleteBVS(&((*root)->left));
        (*root)->left = NULL;
    }
    free((*root));
    *root = NULL;
}
