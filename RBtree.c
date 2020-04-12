/*
 * [PROG]		: Red Black Tree
 * [AUTHOR]		: Ashfaqur Rahman <sajib.finix@gmail.com>
 * https://gist.github.com/aagontuk/38b4070911391dd2806f/revisions
 * [PURPOSE]		: Red-Black tree is an algorithm for creating a balanced
 * 			  binary search tree data structure. Implementing a red-balck tree
 * 			  data structure is the purpose of this program.
 *
 * [DESCRIPTION]	: Its almost like the normal binary search tree data structure. But
 * 			  for keeping the tree balanced an extra color field is introduced to each node.
 *			  This tree will mantain bellow properties.
 *				  1. Nodes can be either RED or BLACK.
 *				  2. ROOT is BLACK.
 *				  3. Leaves of this tree are null nodes. Here null is represented bya special node NILL.
 *				     Each NILL nodes are BLACK. So each leave is BLACK.
 * 				  4. Each RED node's parent is BLACK
 *				  5. Each simple path taken from a node to descendent leaf has same number of black height.
 *				     That means each path contains same number of BLACK nodes.
 */
#include "RBtree.h"
#pragma GCC optimize("01") //optimalizacia kompilera
/* Global, since all function will access them */
struct node *ROOT;
struct node *NILL;

struct node *tree_search(int key){
    struct node *x;

    x = ROOT;
    while(x != NILL && x->key != key){
        if(key < x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    return x;
}

struct node *tree_minimum(struct node *x){
    while(x->left != NILL){
        x = x->left;
    }
    return x;
}

/*
 * Insertion is done by the same procedure for BST Insert. Except new node is colored
 * RED. As it is coloured RED it may violate property 2 or 4. For this reason an
 * auxilary procedure called red_black_insert_fixup is called to fix these violation.
 */

void red_black_insert(int key){
    struct node *z, *x, *y;
    z = malloc(sizeof(struct node));

    z->key = key;
    z->color = RED;
    z->left = NILL;
    z->right = NILL;

    x = ROOT;
    y = NILL;

    /*
     * Go through the tree untill a leaf(NILL) is reached. y is used for keeping
     * track of the last non-NILL node which will be z's parent.
     */
    while(x != NILL){
        y = x;
        if(z->key <= x->key){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }

    if(y == NILL){
        ROOT = z;
    }
    else if(z->key <= y->key){
        y->left = z;
    }
    else{
        y->right = z;
    }

    z->parent = y;

    red_black_insert_fixup(z);
}

/*
 * Here is the psudocode for fixing violations.
 *
 * while (z's parent is RED)
 *		if(z's parent is z's grand parent's left child) then
 *			if(z's right uncle or grand parent's right child is RED) then
 *				make z's parent and uncle BLACK
 *				make z's grand parent RED
 *				make z's grand parent new z as it may violate property 2 & 4
 *				(so while loop will contineue)
 *
 *			else(z's right uncle is not RED)
 *				if(z is z's parents right child) then
 *					make z's parent z
 *					left rotate z
 *				make z's parent's color BLACK
 *				make z's grand parent's color RED
 *				right rotate z's grand parent
 *				( while loop won't pass next iteration as no violation)
 *
 *		else(z's parent is z's grand parent's right child)
 *			do exact same thing above just swap left with right and vice-varsa
 *
 * At this point only property 2 can be violated so make root BLACK
 */

void red_black_insert_fixup(struct node *z){
    while(z->parent->color == RED){

        /* z's parent is left child of z's grand parent*/
        if(z->parent == z->parent->parent->left){

            /* z's grand parent's right child is RED */
            if(z->parent->parent->right->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->right->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

                /* z's grand parent's right child is not RED */
            else{

                /* z is z's parent's right child */
                if(z == z->parent->right){
                    z = z->parent;
                    left_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(z->parent->parent);
            }
        }

            /* z's parent is z's grand parent's right child */
        else{

            /* z's left uncle or z's grand parent's left child is also RED */
            if(z->parent->parent->left->color == RED){
                z->parent->color = BLACK;
                z->parent->parent->left->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }

                /* z's left uncle is not RED */
            else{
                /* z is z's parents left child */
                if(z == z->parent->left){
                    z = z->parent;
                    right_rotate(z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(z->parent->parent);
            }
        }
    }

    ROOT->color = BLACK;
}

/*
 * Lets say y is x's right child. Left rotate x by making y, x's parent and x, y's
 * left child. y's left child becomes x's right child.
 *
 * 		x									y
 *	   / \                                 / \
 *  STA   y			----------->		  x   STC
 *		 / \							 / \
 *	  STB   STC						  STA   STB
 */

void left_rotate(struct node *x){
    struct node *y;

    /* Make y's left child x's right child */
    y = x->right;
    x->right = y->left;
    if(y->left != NILL){
        y->left->parent = x;
    }

    /* Make x's parent y's parent and y, x's parent's child */
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    /* Make x, y's left child & y, x's parent */
    y->left = x;
    x->parent = y;
}

/*
 * Lets say y is x's left child. Right rotate x by making x, y's right child and y
 * x's parent. y's right child becomes x's left child.
 *
 *			|											|
 *			x											y
 *		   / \										   / \
 *		  y   STA		---------------->			STB	  x
 *		 / \											 / \
 *	  STB   STC										  STC   STA
 */

void right_rotate(struct node *x){
    struct node *y;

    /* Make y's right child x's left child */
    y = x->left;
    x->left = y->right;
    if(y->right != NILL){
        y->right->parent = x;
    }

    /* Make x's parent y's parent and y, x's parent's child */
    y->parent = x->parent;
    if(y->parent == NILL){
        ROOT = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }

    /* Make y, x's parent and x, y's child */
    y->right = x;
    x->parent = y;
}


/* replace node u with node v */
void red_black_transplant(struct node *u, struct node *v){
    if(u->parent == NILL){
        ROOT = v;
    }
    else if(u == u->parent->left){
        u->parent->left = v;
    }
    else{
        u->parent->right = v;
    }

    v->parent = u->parent;
}


/* will delete tree*/
void deleteRB(struct node** root)
{
    if ((*root) == NILL) {
        *root = NULL;
        return;
    }
    if ((*root)->right->key != NILL->key) {
        deleteRB(&((*root)->right));

    } else (*root)->right = NULL;
    if ((*root)->left->key != NILL->key) {
        deleteRB(&((*root)->left));

    } else (*root)->left = NULL;
    free((*root));
    *root = NULL;
}

void printRB(struct node *root, int space) {
    if (root == NILL)
        return;

    space += 10;
    printRB(root->right, space);
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    printRB(root->left, space);
}