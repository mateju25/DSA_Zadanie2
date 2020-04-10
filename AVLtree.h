//
// Created by Matej Delincak on 24. 3. 2020.
//

#ifndef ZADANIE2_AVLTREE_H
#define ZADANIE2_AVLTREE_H

#endif //ZADANIE2_AVLTREE_H

//zisti ci treba balancovat vrchol
#define NEED_BALANCE(base)     ((((base)->right == NULL) || ((base)->left == NULL)) ? 1 : (((base)->right->rank == (base)->left->rank) ? -1 : 1))
//prerata hlbku podstromov
#define MAX_RANK(base) ((((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? ((base)->left->rank + 1) :  (    ((base)->left == NULL) ? ((base)->right->rank+1) :  (((base)->right->rank) > ((base)->left->rank)) ? ((base)->right->rank+1) : ((base)->left->rank+1)    )      )    )
//zisti balance faktor
#define DIFF_RANK(base) ((base == NULL) ? 0 : (    (((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? 0-((base)->left->rank+1) :  (    ((base)->left == NULL) ? ((base)->right->rank+1) :  ((base)->right->rank) - ((base)->left->rank)   )      )    ))

typedef struct nodeAVL{
    int value;
    int rank;
    struct nodeAVL* left;
    struct nodeAVL* right;
}NODE_AVL;

void insertAVL(NODE_AVL** root, int paVal);
void printAVL(NODE_AVL *root, int space);
NODE_AVL* searchAVL(NODE_AVL* root, int paVal);
void deleteAVL(NODE_AVL** root);
