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
#include "counters.h"
#include "memory.h"

/**************** local types ****************/
// general counter node
typedef struct counternode
{
    int count;           //count (or value) corresponding to key
    int key;            //key for the counter
    struct counternode *next; // link to next node
} counternode_t;

/**************** global types ****************/
//counter header
typedef struct counters
{
    struct counternode *head; // head of the list of items in counters
} counters_t;

/**************** local functions ****************/
/* not visible outside this file */
static counternode_t *counternode_new(int key, int count);

static counternode_t *key_exists(counters_t *counter, const int key);

/**************** counters_new() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
counters_t *counters_new(void){

    //allocate memory
    counters_t *counter = count_malloc(sizeof(counters_t));

    if (counter == NULL)
    {
        return NULL; // error allocating counter
    }
    else
    {
        // initialize contents of counter structure
        counter->head = NULL;
        return counter;
    }
}

/**************** counters_add() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
int counters_add(counters_t *ctrs, const int key){

    //return 0 if invalid inputs
    if ((ctrs == NULL) || (key < 0)){
        return 0;
    }

    //get the node if there exists one with the specified key
    counternode_t *node = key_exists(ctrs, key);

    if (node == NULL){
        //if there isn't a key already, make a new node and add it
        counternode_t *new = counternode_new(key, 1);
        new->next = ctrs->head;
        ctrs->head = new;
        return 1;
    }
    else{
        //if there's already a node with that key increase its count
        node->count += 1;
        return node->count;
    }
}

/**************** counters_get() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
int counters_get(counters_t *ctrs, const int key){

    //return 0 if invalid inputs
    if ((ctrs == NULL) || (key < 0)){
        return 0;
    }

    //get ptr to node the key already exists
    counternode_t *node = key_exists(ctrs, key);

    if (node == NULL){
        //if it doesn't exist
        return 0;
    }
    else{
        //otherwise return the count
        return node->count;
    }
}

/**************** counters_set() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
bool counters_set(counters_t *ctrs, const int key, const int count){

    //return 0 if invalid inputs
    if ((ctrs == NULL) || (key < 0) || (count < 0)){
        return false;
    }

    //get node with key if it exists
    counternode_t *node = key_exists(ctrs, key);

    if (node == NULL)
    {
        //if node doesn't exist make one and set count to specified value
        counternode_t *new = counternode_new(key, count);

        //if out of mem return false
        if (new == NULL){
            return false;
        }

        //add to counter
        new->next = ctrs->head;
        ctrs->head = new;
    }
    else
    {
        //if it exists just update count
        node->count = count;
    }

    return true;
}

/**************** counters_print() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
void counters_print(counters_t *ctrs, FILE *fp){

    //if file doesn't exist do nothing
    if (fp != NULL)
    {
        //if null pointer print none
        if (ctrs != NULL)
        {
            fputc('{', fp);
            //loop through nodes and print key=count,
            for (counternode_t *node = ctrs->head;node != NULL; node = node->next)
            {
                // print this node
                fprintf(fp,"%d",node->key);
                fputc('=', fp);
                fprintf(fp,"%d",node->count);
                fputc(',', fp);
            }
            fputc('}', fp);
        }
        else
        {
            fputs("(null)", fp);
        }
    }
}

/**************** counters_iterate() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
void counters_iterate(counters_t *ctrs, void *arg,
                      void (*itemfunc)(void *arg,
                                       const int key, const int count)){
    
    //check for valid inputs                                       
    if (ctrs != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each key, count
        for (counternode_t *node = ctrs->head; node != NULL; node = node->next)
        {
            (*itemfunc)(arg, node->key, node->count);
        }
    }
}

/**************** counters_delete() ****************/
/* see counters.h for description */
/*  adapted from bag.c  */
void counters_delete(counters_t *ctrs){
    
    //ignore NULL ctrs
    if (ctrs != NULL){

        //loop through each node and free it
        for (counternode_t *node = ctrs->head; node != NULL;)
        {
            counternode_t *next = node->next; // remember what comes next
            count_free(node);             // free the node
            node = next;                  // and move on to next
        }

        //free header
        count_free(ctrs);
    }
}

/**************** key_exists() ****************/
/* check to see if a node witha  specified key exists 
and return its pointer, else return NULL */
counternode_t *key_exists(counters_t *counter, const int key){

    //loop through nodes
    for (counternode_t *node = counter->head; node != NULL;
        node = node->next){
            //if the node's key is equal to the inputted one return true
            if (node->key == key){
                return node; //return node pointer
            }
    }
    return NULL;
}

/**************** counternode_new() ****************/
/* allocate and initialize a counternode */
/*  adapted from bag.c  */
static counternode_t *counternode_new(int key, int count)
{
    counternode_t *node = count_malloc(sizeof(counternode_t));

    if (node == NULL)
    {
        return NULL; //error allocating node
    }
    else
    {
        //initialize values of ndoe
        node->key = key;
        node->count = count;
        node->next = NULL;
        return node;
    }
}
