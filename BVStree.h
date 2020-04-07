//
// Created by Matej on 7. 4. 2020.
//

#ifndef ZADANIE2_BVSTREE_H
#define ZADANIE2_BVSTREE_H

#endif //ZADANIE2_BVSTREE_H

typedef struct nodeBVS{
    int value;
    struct nodeBVS* left;
    struct nodeBVS* right;
}NODE_BVS;

void insertBVS(NODE_BVS** root, int paVal);
void printBVS(NODE_BVS *root, int space);
NODE_BVS* searchBVS(NODE_BVS** root, int paVal);
void deleteBVS(NODE_BVS** root);