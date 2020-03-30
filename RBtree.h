//
// Created by Matej on 28. 3. 2020.
//

#ifndef ZADANIE2_RBTREE_H
#define ZADANIE2_RBTREE_H

#endif //ZADANIE2_RBTREE_H
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

struct node{
    int key;
    int color;
    struct node *parent;
    struct node *left;
    struct node *right;
};

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void red_black_insert(int key);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
struct node *tree_minimum(struct node *x);
