/*
 * counters.c - CS50 'counter' module
 *
 * see counters.h for more information.
 *
 * CS50
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "memory.h"

/**************** local types ****************/
// general set node
typedef struct setnode
{
    void* item; // pointer to data for this item
    char* key; // pointer to the key
    struct setnode *next; // link to next node
} setnode_t;

/**************** global types ****************/
// head of set
typedef struct set
{
    struct setnode *head; // head of the list of items in counters
} set_t;

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t *setnode_new(char* key, void* value);
static setnode_t *key_exists(set_t *set, const char *key);

/**************** set_new() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
set_t *set_new(void)
{
    //allocate memory for set
    set_t *set = count_malloc(sizeof(set_t));

    if (set == NULL)
    {
        return NULL; // error allocating set
    }
    else
    {
        // initialize contents of set structure
        set->head = NULL;
        return set;
    }
}

/**************** set_insert() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
bool set_insert(set_t *set, const char *key, void *item)
{
    // return false if invalid inputs
    if ((set == NULL) || (key == NULL) || (item == NULL)){
        return false;
    }

    // get the node if there exists one with the specified key
    setnode_t *node = key_exists(set, key);

    if (node == NULL)
    {
        // if there isn't a key already, make a new node and add it
        char *key_copy = count_malloc(strlen(key) + 1);
        strcpy(key_copy, key);

        //add to set
        setnode_t *new = setnode_new(key_copy, item);
        new->next = set->head;
        set->head = new;
        return true;
    }
    else
    {
        // if there's already a node with that key return false
        return false;
    }
}

/**************** set_find() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
void *set_find(set_t *set, const char *key)
{
    // return NULL if invalid inputs
    if ((set == NULL) || (key == NULL))
    {
        return NULL;
    }

    setnode_t* node = key_exists(set,key);

    //if no node with that key return NULL
    if (node == NULL){
        return NULL;
    }

    //return nodes item
    return node->item;
}

/**************** set_print() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
void set_print(set_t *set, FILE *fp,
               void (*itemprint)(FILE *fp, const char *key, void *item)){

    // if file doesn't exist do nothing
    if (fp != NULL){
        // if null pointer print none
        if (set != NULL){
            fputc('{', fp);
            // loop through nodes and print using specified function
            for (setnode_t *node = set->head; node != NULL; node = node->next)
            {
                // print this node
                if (itemprint != NULL) {
                    (*itemprint)(fp,node->key, node->item);
                    fputc(',', fp);
                }
            }
            fputc('}', fp);
        }
        else
        {
            fputs("(null)", fp);
        }
    }
}

/**************** set_iterate() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
void set_iterate(set_t *set, void *arg,
                 void (*itemfunc)(void *arg, const char *key, void *item))
{
    // check for valid inputs
    if (set != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each key, item
        for (setnode_t *node = set->head; node != NULL; node = node->next)
        {
            (*itemfunc)(arg, node->key, node->item);
        }
    }
}

/**************** set_delete() ****************/
/* see set.h for description */
/*  adapted from bag.c  */
void set_delete(set_t *set, void (*itemdelete)(void *item))
{
    // ignore NULL set
    if (set != NULL)
    {
        // loop through each node and free it
        for (setnode_t *node = set->head; node != NULL;)
        {
            //free key
            count_free(node->key);

            // delete node's item
            if (itemdelete != NULL){
                (*itemdelete)(node->item); 
            }

            setnode_t *next = node->next; // remember what comes next
            count_free(node);                 // free the node
            node = next;                      // and move on to next
        }

        // free header
        count_free(set);
    }
}

/**************** key_exists() ****************/
/* check to see if a node witha  specified key exists
and return its pointer, else return NULL */
setnode_t *key_exists(set_t *set, const char *key)
{

    // loop through nodes
    for (setnode_t *node = set->head; node != NULL;
         node = node->next)
    {
        // if the node's key is equal to the inputted one return the node
        if (strcmp((node->key), (key)) == 0)
        {
            return node;
        }
    }

    //if not found return NULL
    return NULL;
}

/**************** setnode_new() ****************/
/* allocate and initialize a setnode */
/*  adapted from bag.c  */
setnode_t *setnode_new(char* key, void* item)
{
    setnode_t *node = count_malloc(sizeof(setnode_t));

    if (node == NULL)
    {
        return NULL; //error allocating memory
    }
    else
    {
        //initialize node's variables
        node->key = key;
        node->item = item;
        node->next = NULL;
        return node;
    }
}
