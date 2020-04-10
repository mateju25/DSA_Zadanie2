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
        return NULL;
    }
    paAct->rank = 0;
    paAct->right = paAct->left = NULL;
    return paAct;
};

void insertBVS(NODE_BVS** root, int paVal)
{
    NODE_BVS ** newRoot = root;
    while ((*newRoot) != NULL)  {
        //hodnota sa nasla
        (*newRoot)->rank = MAX_RANK(*newRoot);
        (*newRoot)->rank++;
        if ((*newRoot)->value == paVal) return;
        if ((*newRoot)->value > paVal) {
            //vlozi do laveho podstromu
            newRoot = &((*newRoot)->left);

        } else
            {
                  //vlozi do praveho podstromu
                 newRoot = &((*newRoot)->right);

            }
    }
    *newRoot = createBVS();
    if (*root == NULL) {
        printf("Malo pamate");
        return;
    }
    (*newRoot)->value = paVal;
}

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
    while (*root != NULL) {
        if ((*root)->value > paVal) {
            root = &((*root)->left);
            continue;
        }
        if ((*root)->value < paVal){
            root = &((*root)->right);
            continue;
        }
        if ((*root)->value == paVal) return (*root);
    }
    return NULL;
}

int deleteBVS(NODE_BVS** root)
{
    if ((*root)->rank >= 65000) {
            return 0;
    }
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
    return 1;
}
