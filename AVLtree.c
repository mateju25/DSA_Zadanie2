//
// Created by Matej on 24. 3. 2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "AVLtree.h"

int i = 0;

NODE_AVL* create(NODE_AVL* paAct)
{
    paAct = (NODE_AVL*)malloc(sizeof(NODE_AVL));
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

void insertAVL(NODE_AVL** root, int paVal)
{
    char balance = 1;
    if (*root == NULL)
    {
        *root = create(*root);
        (*root)->value = paVal;
    }
    else
    {
        balance = NEED_BALANCE(*root);
        if ((*root)->rank > paVal) {
            //if (DIFF_RANK(*root) == 1) balance = -1;
            insertAVL(&((*root)->left), paVal);
        }
        if ((*root)->rank < paVal){
            //if (DIFF_RANK(*root) == -1) balance = -1;
            insertAVL(&((*root)->right), paVal);
        }
        if ((*root)->rank == paVal) return;
    }
    //zaciatok vyvazovania
    if (balance == -1) return;
    (*root)->rank = MAX_RANK(*root);//aktualizacia max hlbky

    if (((*root)->rank == 1) || ((*root)->rank == -1) || ((*root)->rank == 0)) return;

    //printf("%d ", i++);
    static int this, left, right;
    this = DIFF_RANK((*root));
    left = DIFF_RANK((*root)->left);
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
    if ((this == -2) && (left == -1)) { //rr rotacia
        rotateRight(root);
        return;
    }
    if ((this == -2) && (left == 1)) {  //lr rotacia
        rotateLeft(&((*root)->left));
        rotateRight(root);
        return;
    }
};

void printAVL(NODE_AVL *root, int space)
{
    #define COUNT 10
    if (root == NULL)
        return;

    space += COUNT;
    printAVL(root->right, space);
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->value);

    printAVL(root->left, space);
}

NODE_AVL* searchAVL(NODE_AVL** root, int paVal) {
    if (*root == NULL) {
        return NULL;
    } else {
        if ((*root)->rank > paVal)  return searchAVL(&((*root)->left), paVal);
        if ((*root)->rank < paVal)  return searchAVL(&((*root)->right), paVal);
        if ((*root)->rank == paVal)  return (*root);
    }

}