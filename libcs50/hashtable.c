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
#include "jhash.h"
#include "memory.h"

/**************** global types ****************/
typedef struct hashtable
{
    int num_slots; //number of slots or bins in hashtable
    set_t** table; // head of the list of sets in hashtable
} hashtable_t;

/**************** hashtable_new() ****************/
/* see hashtable.h for description */
hashtable_t *hashtable_new(const int num_slots)
{
    if (num_slots < 1){
        return NULL; //wrong input
    }

    hashtable_t *hashtable = count_malloc(sizeof(hashtable_t));

    if (hashtable == NULL)
    {
        return NULL; // error allocating counter
    }
    else
    {

        // initialize contents of counter structure
        hashtable->num_slots = num_slots;
        hashtable->table = calloc(num_slots, sizeof(set_t *));
        if (hashtable->table == NULL){
            return NULL; //error allocating array
        }
        
        //loop through and make empty sets
        for (int i = 0; i < num_slots; i += 1)
        {
            hashtable->table[i] = set_new();
            if (hashtable->table[i] == NULL){
                return NULL; //error allocating set
            }
        }
        return hashtable;
    }
}

/**************** hashtable_insert() ****************/
/* see hashtable.h for description */
bool hashtable_insert(hashtable_t *ht, const char *key, void *item)
{

    // return NULL if invalid inputs
    if ((ht == NULL) || (key == NULL) || (item == NULL))
    {
        return false;
    }

    //hash key
    unsigned long bin = JenkinsHash(key, ht->num_slots);

    //return if successfully inserted into correct set
    return set_insert(ht->table[bin], key, item);
}

/**************** hashtable_find() ****************/
/* see hashtable.h for description */
void *hashtable_find(hashtable_t *ht, const char *key)
{

    // return NULL if invalid inputs
    if ((ht == NULL) || (key == NULL))
    {
        return NULL;
    }

    //hash key
    unsigned long bin = JenkinsHash(key, ht->num_slots);

    //check the set it would be in and return it
    return set_find(ht->table[bin], key);
}

/**************** hashtable_print() ****************/
/* see hashtable.h for description */
void hashtable_print(hashtable_t *ht, FILE *fp,
                     void (*itemprint)(FILE *fp, const char *key, void *item))
{

    // if file doesn't exist do nothing
    if (fp != NULL)
    {
        // if null pointer print none
        if (ht != NULL)
        {
            // loop through nodes and print the set
            for (int i = 0; i < ht->num_slots; i += 1)
            {
                // print this node
                set_print(ht->table[i],fp,itemprint);
                fprintf(fp,"\n");

            }
        }
        else
        {
            fputs("(null)", fp);
        }
    }
}

/**************** hashtable_iterate() ****************/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t *ht, void *arg,
                       void (*itemfunc)(void *arg, const char *key, void *item))
{

    // check for valid inputs
    if (ht != NULL && itemfunc != NULL)
    {
        // call itemfunc with arg, on each set
        for (int i = 0; i < ht->num_slots; i += 1)
        {
            // print this set
            set_iterate(ht->table[i], arg, itemfunc);
        }
    }
}

/**************** hashtable_delete() ****************/
/* see hashtable.h for description */
/*  adapted from bag.c  */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item))
{

    // ignore NULL set
    if (ht != NULL)
    {

        // loop through each set in array and free it
        for (int i = 0; i < ht->num_slots; i += 1)
        {
            // print this node
            set_delete(ht->table[i], itemdelete);
        }

        // free array and hashtable
        count_free(ht->table);
        count_free(ht);
    }
}