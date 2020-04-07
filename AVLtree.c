//
// Created by Matej on 24. 3. 2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "AVLtree.h"
#pragma GCC optimize("01")//optimalizacia kompilera

NODE_AVL* createAVL()
{
    NODE_AVL* paAct = (NODE_AVL*)malloc(sizeof(NODE_AVL));
    paAct->rank = 0;
    paAct->right = paAct->left = NULL;
    return paAct;
};

void rotateLeft(NODE_AVL** paAct)
{
    NODE_AVL* rightleftBase = (*paAct)->right->left;
    (*paAct)->right->left = *paAct;
    *paAct = (*paAct)->right;
    (*paAct)->left->right = rightleftBase;
    (*paAct)->left->rank -= 2;
};

void rotateRight(NODE_AVL** paAct)
{
    NODE_AVL* leftrightBase = (*paAct)->left->right;
    (*paAct)->left->right = *paAct;
    *paAct = (*paAct)->left;
    (*paAct)->right->left = leftrightBase;
    (*paAct)->right->rank -= 2;
};

void balanceAVL(NODE_AVL** root)
{
    static int this, left, right;
    this = DIFF_RANK((*root));
    right = DIFF_RANK((*root)->right);
    if ((this == 2) && (right == 1)) { //ll rotacia
        rotateLeft(root);
        return;
    }
    if ((this == 2) && (right == -1)) {  //rl rotacia
        rotateRight(&((*root)->right));
        rotateLeft(root);
        return;
    }
    left = DIFF_RANK((*root)->left);
    if ((this == -2) && (left == -1)) { //rr rotacia
        rotateRight(root);
        return;
    }
    if ((this == -2) && (left == 1)) {  //lr rotacia
        rotateLeft(&((*root)->left));
        rotateRight(root);
        return;
    }
}

void insertAVL(NODE_AVL** root, int paVal)
{
    if (*root == NULL)
    {
        *root = createAVL();
        (*root)->value = paVal;
    }
    else
    {
        if ((*root)->value > paVal) {
            insertAVL(&((*root)->left), paVal);
        }
        if ((*root)->value < paVal){
            insertAVL(&((*root)->right), paVal);
        }
        if ((*root)->value == paVal) return;
    }
    if (NEED_BALANCE(*root) == -1) return;
    (*root)->rank = MAX_RANK(*root);//aktualizacia max hlbky
    if (((*root)->rank == 1) || ((*root)->rank == -1) || ((*root)->rank == 0)) return;

    //zaciatok vyvazovania
    if (((DIFF_RANK((*root)) == 2)) || ((DIFF_RANK((*root)) == -2))) balanceAVL(root);
};

void printAVL(NODE_AVL *root, int space) {
    if (root == NULL)
        return;

    space += 10;
    printAVL(root->right, space);
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    printAVL(root->left, space);
}
NODE_AVL* searchAVL(NODE_AVL** root, int paVal) {
    if (*root == NULL) {
        return NULL;
    } else {
        if ((*root)->value == paVal)  return (*root);
        if ((*root)->value > paVal)
            return searchAVL(&((*root)->left), paVal);
        else
            return searchAVL(&((*root)->right), paVal);

    }
}

void deleteAVL(NODE_AVL** root)
{
    if ((*root)->right != NULL) {
        deleteAVL(&((*root)->right));
        (*root)->right = NULL;
    }
    if ((*root)->left != NULL) {
        deleteAVL(&((*root)->left));
        (*root)->left = NULL;
    }
    free((*root));
    *root = NULL;
}