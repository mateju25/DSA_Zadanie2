//
// Created by Matej Delincak on 24. 3. 2020.
//
#include <stdlib.h>
#include <stdio.h>
#include "AVLtree.h"
#pragma GCC optimize("01")//optimalizacia kompilera

//vytvor vrchol
NODE_AVL* createAVL()
{
    NODE_AVL* paAct = (NODE_AVL*)malloc(sizeof(NODE_AVL));
    if (paAct == NULL)
        return NULL;
    paAct->rank = 0;
    paAct->right = paAct->left = NULL;
    return paAct;
};
//rotacia dolava
void rotateLeft(NODE_AVL** paAct)
{
    NODE_AVL* rightleftBase = (*paAct)->right->left;
    (*paAct)->right->left = *paAct;
    *paAct = (*paAct)->right;
    (*paAct)->left->right = rightleftBase;
    //prerataj hlbky
    (*paAct)->left->rank = MAX_RANK((*paAct)->left);
    (*paAct)->rank = MAX_RANK((*paAct));
}
//rotacia doprava dolava
void rotateRightLeft(NODE_AVL** paAct)
{
    NODE_AVL* base = *paAct;
    NODE_AVL* rightleftBase = (*paAct)->right->left;
    (*paAct)->right->left = rightleftBase->right;
    rightleftBase->right = (*paAct)->right;
    (*paAct)->right = rightleftBase->left;
    rightleftBase->left = base;
    (*paAct) = rightleftBase;
    //prerataj hlbky
    if ((*paAct)->right != NULL)
        (*paAct)->right->rank = MAX_RANK((*paAct)->right);
    if ((*paAct)->left != NULL)
        (*paAct)->left->rank = MAX_RANK((*paAct)->left);
    (*paAct)->rank = MAX_RANK((*paAct));
}
//rotacia doprava
void rotateRight(NODE_AVL** paAct)
{
    NODE_AVL* leftrightBase = (*paAct)->left->right;
    (*paAct)->left->right = *paAct;
    *paAct = (*paAct)->left;
    (*paAct)->right->left = leftrightBase;
    //prerataj hlbky
    (*paAct)->right->rank = MAX_RANK((*paAct)->right);
    (*paAct)->rank = MAX_RANK((*paAct));
}
//rotacia doprava dolava
void rotateLeftRight(NODE_AVL** paAct)
{
    NODE_AVL* base = *paAct;
    NODE_AVL* leftrightBase = (*paAct)->left->right;
    (*paAct)->left->right = leftrightBase->left;
    leftrightBase->left = (*paAct)->left;
    (*paAct)->left = leftrightBase->right;
    leftrightBase->right = base;
    (*paAct) = leftrightBase;
    //prerataj hlbky
    if ((*paAct)->right != NULL)
        (*paAct)->right->rank = MAX_RANK((*paAct)->right);
    if ((*paAct)->left != NULL)
        (*paAct)->left->rank = MAX_RANK((*paAct)->left);
    (*paAct)->rank = MAX_RANK((*paAct));
}
//vyvazovanie stromu
void balanceAVL(NODE_AVL** root)
{
    static int this, left, right;
    //zisti rozdiely hlbok podstromov
    this = DIFF_RANK((*root));
    right = DIFF_RANK((*root)->right);
    if ((this == 2) && (right == 1)) { //rr rotacia
        rotateLeft(root);
        return;
    }
    if ((this == 2) && (right == -1)) {  //lr rotacia
        rotateRight(&((*root)->right));
        rotateLeft(root);
        //rotateRightLeft(root);
        return;
    }
    left = DIFF_RANK((*root)->left);
    if ((this == -2) && (left == -1)) { //ll rotacia
        rotateRight(root);
        return;
    }
    if ((this == -2) && (left == 1)) {  //rl rotacia
        rotateLeft(&((*root)->left));
        rotateRight(root);
        //rotateLeftRight(root);
        return;
    }
}
//vlozi do stromu hodnotu
void insertAVL(NODE_AVL** root, int paVal)
{
    if (*root == NULL)
    {
        //vytvori na konci novy vrchol
        *root = createAVL();
        if (*root == NULL) {
           printf("Malo pamate");
           return;
        }
        (*root)->value = paVal;
    }
    else
    {
        if ((*root)->value > paVal) {
            //vlozi do laveho podstromu
            insertAVL(&((*root)->left), paVal);
        }
        if ((*root)->value < paVal){
            //vlozi do praveho podstromu
            insertAVL(&((*root)->right), paVal);
        }
        //hodnota sa nasla
        if ((*root)->value == paVal) return;
    }

    if (NEED_BALANCE(*root) == -1) return;
    //aktualizacia max. hlbky podstromu
    (*root)->rank = MAX_RANK(*root);
    //ak je vyvazeny tak ukonci
    if (((*root)->rank == 1) || ((*root)->rank == -1) || ((*root)->rank == 0)) return;

    //ak je vrchol nevyvazeny, tak ho vyvaz
    if (((DIFF_RANK((*root)) == 2)) || ((DIFF_RANK((*root)) == -2))) balanceAVL(root);
}
//funkcia vypise strom
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
//hladanie v strome
NODE_AVL* searchAVL(NODE_AVL* root, int paVal) {
    while (root != NULL){
        if (root->value == paVal)
            return (root);//hodnota sa nasla
        if (root->value > paVal)
            //prehladaj lavy podstrom
            root = root->left;
        else
            //prehladaj pravy podstrom
            root = root->right;
    }
    //ak program skonci tu, hodnota sa nenasla
    return NULL;
}
//vymazanie stromu
void deleteAVL(NODE_AVL** root)
{
    if ((*root)->right != NULL) {
        //vymaz pravy podstrom
        deleteAVL(&((*root)->right));
        (*root)->right = NULL;
    }
    if ((*root)->left != NULL) {
        //vymaz lavy podstrom
        deleteAVL(&((*root)->left));
        (*root)->left = NULL;
    }
    //uvolni aktualny vrchol
    free((*root));
    *root = NULL;
}
