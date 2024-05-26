#include <stdlib.h>
#ifndef SLLIST_C
#define SLLIST_C
#include "SLList.h"

SLList *sllCreate()
{
    SLList *sll = (SLList *)malloc(sizeof(SLList));
    if (sll != NULL)
    {
        sll->first = NULL;
        sll->cur = NULL;
    }
    return sll;
}

int sllDestroy(SLList *sll)
{
    if (sll != NULL)
    {
        if (sll->first == NULL)
        {
            free(sll);
            return TRUE;
        }
    }
    return FALSE;
}

int sllInsertFirst(SLList *sll, void *data)
{
    SLNode *newnode;
    if (sll != NULL)
    {
        newnode = (SLNode *)malloc(sizeof(SLNode));
        if (newnode != NULL)
        {
            newnode->data = data;
            newnode->next = sll->first;
            sll->first = newnode;
            return TRUE;
        }
    }
    return FALSE;
}

void *sllQuery(SLList *sll, void *key, int (*cmp)(void *, void *))
{
    SLNode *cur;
    int stat;
    if (sll != NULL)
    {
        if (sll->first != NULL)
        {
            cur = sll->first;
            stat = cmp(key, cur->data);
            while (stat != TRUE && cur->next != NULL)
            {
                cur = cur->next;
                stat = cmp(key, cur->data);
            }
            if (stat == TRUE)
            {
                return cur->data;
            }
        }
    }
    return NULL;
}

void *sllRemoveSpec(SLList *sll, void *key, int (*cmp)(void *, void *))
{
    SLNode *spec;
    SLNode *prev;
    void *data;
    int stat;
    if (sll != NULL)
    {
        if (sll->first != NULL)
        {
            spec = sll->first;
            prev = NULL;
            stat = cmp(key, spec->data);
            while (stat != TRUE && spec->next != NULL)
            {
                prev = spec;
                spec = spec->next;
                stat = cmp(key, spec->data);
            }
            if (stat == TRUE)
            {
                if (prev != NULL)
                {
                    prev->next = spec->next;
                }
                else
                {
                    sll->first = spec->next;
                }
                data = spec->data;
                free(spec);
                return data;
            }
        }
    }
    return NULL;
}

void *sllRemoveFirst(SLList *sll)
{
    SLNode *first;
    void *data;
    if (sll != NULL)
    {
        if (sll->first != NULL)
        {
            first = sll->first;
            data = first->data;
            sll->first = first->next;
            free(first);
            return data;
        }
    }
    return NULL;
}

void *sllGetFirst(SLList *sll)
{
    if (sll != NULL)
    {
        sll->cur = sll->first;
        if (sll->cur != NULL)
        {
            return sll->cur->data;
        }
    }
    return NULL;
}

void *sllGetNext(SLList *sll)
{
    if (sll != NULL)
    {
        if (sll->cur != NULL)
        {
            sll->cur = sll->cur->next;
            if (sll->cur != NULL)
            {
                return sll->cur->data;
            }
        }
    }
    return NULL;
}

#endif
