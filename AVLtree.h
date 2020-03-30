//
// Created by Matej on 24. 3. 2020.
//

#ifndef ZADANIE2_AVLTREE_H
#define ZADANIE2_AVLTREE_H

#endif //ZADANIE2_AVLTREE_H
#define NEED_BALANCE2(base) (    (((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? -1 :  (    ((base)->left == NULL) ? 1 :  ((base)->right->rank) - ((base)->left->rank)   )      )    )
#define NEED_BALANCE(base)     ((((base)->right == NULL) || ((base)->left == NULL)) ? 1 : (((base)->right->rank == (base)->left->rank) ? -1 : 1))
#define MAX_RANK(base) ((((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? ((base)->left->rank + 1) :  (    ((base)->left == NULL) ? ((base)->right->rank+1) :  (((base)->right->rank) > ((base)->left->rank)) ? ((base)->right->rank+1) : ((base)->left->rank+1)    )      )    )
#define DIFF_RANK(base) ((base == NULL) ? 0 : (    (((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? 0-((base)->left->rank+1) :  (    ((base)->left == NULL) ? ((base)->right->rank+1) :  ((base)->right->rank) - ((base)->left->rank)   )      )    ))

typedef struct nodeAVL{
    int value;
    int rank;
    struct nodeAVL* left;
    struct nodeAVL* right;
}NODE_AVL;

void insertAVL(NODE_AVL** root, int paVal);
void printAVL(NODE_AVL *root, int space);
NODE_AVL* searchAVL(NODE_AVL** root, int paVal);