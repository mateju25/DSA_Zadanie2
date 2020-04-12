//
// Created by Matej on 7. 4. 2020.
//

#ifndef ZADANIE2_BVSTREE_H
#define ZADANIE2_BVSTREE_H

#endif //ZADANIE2_BVSTREE_H

#define MAX_RANK(base) ((((base)->right == NULL) && ((base)->left == NULL)) ? 0 : (    ((base)->right == NULL) ? ((base)->left->rank + 1) :  (    ((base)->left == NULL) ? ((base)->right->rank+1) :  (((base)->right->rank) > ((base)->left->rank)) ? ((base)->right->rank+1) : ((base)->left->rank+1)    )      )    )


typedef struct nodeBVS{
    int value;
    int rank;
    struct nodeBVS* left;
    struct nodeBVS* right;
}NODE_BVS;

void insertBVS(NODE_BVS** root, int paVal);
void printBVS(NODE_BVS *root, int space);
NODE_BVS* searchBVS(NODE_BVS** root, int paVal);
int deleteBVS(NODE_BVS** root);