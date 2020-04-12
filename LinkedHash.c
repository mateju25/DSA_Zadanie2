//created by Manish Bhojasia
//https://www.sanfoundry.com/c-program-implement-hash-tables-chaining-with-singly-linked-lists/

#include <stdio.h>
#include <stdlib.h>

#pragma GCC optimize("01")
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

HASHTABLELINKED* array;
int size;         /* Determines the no. of elements present in Hash Table */
int max;	      /* Determines the maximum capacity of Hash Table array */

void insertLinkedHS(int value);

/* This function creates an index corresponding to the every given key */
int hashcode(int key)
{
    return (key % max);
}


/* Returns the node (Linked List item) located at given find_index  */
DATA* get_element(DATA *list, int find_index)
{
    int i = 0;
    DATA *temp = list;
    while (i != find_index)
    {
        temp = temp->next;
        i++;
    }
    return temp;
}

/* For initializing the Hash Table */
void init_array()
{

    int i = 0;
    for (i = 0; i < max; i++)
    {
        (array+i)->head = NULL;
        (array+i)->tail = NULL;
    }

}

/* Returns size of Hash Table */
int size_of_array()
{
    return size;
}

/*
 *This function finds the given key in the Linked List
 *Returns it's index
 *Returns -1 in case key is not present
*/
int* searchLinkedHS(int value)
{
    DATA *temp = (DATA*) (array + hashcode(value))->head;
    while (temp != (array + hashcode(value))->tail)
    {
        if (temp->value == value)
        {
            return &(temp->value);
        }
        temp = temp->next;
    }
    if (temp->value != value)
        return NULL;
    else
        return &(temp->value);

}

void rehash()
{
    HASHTABLELINKED *temp = array;
    /* temp pointing to the current Hash Table array */

    int i = 0, n = max;
    size = 0;
    max = 2 * max;

    /*
     *array variable is assigned with newly created Hash Table
     *with double of previous array size
    */
    array = (HASHTABLELINKED*) malloc(max * sizeof(HASHTABLELINKED));
    init_array();

    for (i = 0; i < n; i++)
    {

        /* Extracting the Linked List at position i of Hash Table array */
        DATA* list = (DATA*) temp[i].head;

        if (list == NULL)
        {

            /* if there is no Linked List, then continue */
            continue;

        }
        else
        {
            /*
             *Presence of Linked List at i
             *Keep moving and accessing the Linked List item until the end.
             *Get one key and value at a time and add it to new Hash Table array.
            */

            while (list != NULL)
            {
                insertLinkedHS(list->value);
                list = list->next;
            }

        }

    }

    for (i = 0; i < n; i++)
    {
        HASHTABLELINKED tempX = temp[i];
        DATA* first = tempX.head;
        if (first != NULL)
        {
            while (first->next != NULL)
            {
                DATA* old = first;
                if (first->next != NULL)
                    first = first->next;
                else
                    first = NULL;
                free(old);
            }
            free(first);
            first = NULL;
        }
        i++;
        i--;
        tempX.head = NULL;
        tempX.tail = NULL;
    }
    free(temp);
    temp = NULL;
}



void insertLinkedHS(int value)
{
    float n = 0.0;
    /* n => Load Factor, keeps check on whether rehashing is required or not */

    int index = hashcode(value);

    /* Extracting Linked List at a given index */
    DATA *list = (DATA*) (array + index)->head;

    /* Creating an item to insert in the Hash Table */
    DATA *item  = (DATA *)malloc(sizeof(DATA));
    if (item == NULL) {
        printf("Malo pamate. \n");
        return;
    }
    item->key = hashcode(value);
    item->value = value;
    item->next = NULL;

    if (list == NULL)
    {
        /* Absence of Linked List at a given Index of Hash Table */

        array[index].head = item;
        array[index].tail = item;
        size++;

    }
    else
    {
        /* A Linked List is present at given index of Hash Table */

        int* find_index = searchLinkedHS(value);
        if (find_index == NULL)
        {
            /*
             *Key not found in existing linked list
             *Adding the key at the end of the linked list
            */

            array[index].tail->next = item;
            array[index].tail = item;
            size++;

        }else
        {
            /*
             *Value already present in linked list
            */
            free(item);
            return;

        }

    }

    //Calculating Load factor
    n = (1.0 * size) / max;
    if (n >= 0.75)
    {
        //rehashing

        rehash();

    }

}






/* To display the contents of Hash Table */
void display()
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        DATA *temp = array[i].head;
        printf("%d: ", i);
        if (temp != NULL)
        {
            while (temp != NULL)
            {
                printf("%d ->", temp->value);
                temp = temp->next;
            }

        }
        printf("\n");

    }
}

/* Delete Hash Table */
void deleteLinkedHash()
{
    int i = 0;
    for (i = 0; i < max; i++)
    {
        HASHTABLELINKED temp = array[i];
        DATA* first = temp.head;
        if (first != NULL)
        {
            while (first->next != NULL)
            {
                DATA* old = first;
                first = first->next;
                free(old);
            }
            free(first);
            first = NULL;
        }
        i++;
        i--;
        temp.head = NULL;
        temp.tail = NULL;
    }
    free(array);
    array = NULL;
}

