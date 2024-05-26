#ifndef SLLIST_H
#define SLLIST_H

#define NOME 1
#define NUM_CAMISA 2
#define ALTURA 3

#define TRUE 1
#define FALSE 0

typedef struct _SLNode_
{
    struct _SLNode_ *next;
    void *data;
} SLNode;

typedef struct _SLList_
{
    SLNode *first;
    SLNode *cur;
} SLList;

SLList *sllCreate();
int sllDestroy(SLList *sll);
int sllInsertFirst(SLList *sll, void *data);
void *sllQuery(SLList *sll, void *key, int (*cmp)(void *, void *));
void *sllRemoveSpec(SLList *sll, void *key, int (*cmp)(void *, void *));
void *sllRemoveFirst(SLList *sll);
void *sllGetFirst(SLList *sll);
void *sllGetNext(SLList *sll);

#endif
