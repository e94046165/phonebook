#include <stdlib.h>

#include "phonebook_hash_djb2_2.h"

/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

entry *findName(char lastName[], entry **pHead)
{
    //printf("get into find func\n");
    entry *e = pHead[hash(lastName)%HASH_TABLE_SIZE];
    while (e != NULL) {
        if (strcasecmp(lastName, e->lastName) == 0) {
            //printf("I find :%s!!\n", e->lastName) ;
            return e;
        }
        //printf("not the word : %s\n", e->lastName);
        e = e->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry **pHead)
{
    //printf("get into append func\n");
    /* allocate memory for the new entry and put lastName */
    unsigned long index = hash(lastName)%HASH_TABLE_SIZE;
    entry *e = (entry *) malloc(sizeof(entry));
    e->pNext = pHead[index]->pNext;
    pHead[index]->pNext = e;
    strcpy(e->lastName, lastName);

    return e;
}
