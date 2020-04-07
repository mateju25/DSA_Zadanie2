//
// Created by Matej on 5. 4. 2020.
//

#ifndef ZADANIE2_LINKEDHASH_H
#define ZADANIE2_LINKEDHASH_H

#endif //ZADANIE2_LINKEDHASH_H
/* Node for storing an item in a Linked List */
typedef struct nodeHS
{
    int key;
    int value;
    struct nodeHS *next;
}DATA;

/* For storing a Linked List at each index of Hash Table  */
typedef struct arrayitem
{

    DATA *head;
    /* head pointing the first element of Linked List at an index of Hash Table */

    DATA *tail;
    /* tail pointing the last element of Linked List at an index of Hash Table */

}HASHTABLELINKED;

void init_array();
void display();
void insertLinkedHS(int value);
int* searchLinkedHS(int value);
void deleteLinkedHash();