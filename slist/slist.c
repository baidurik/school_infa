#include "slist.h"
#include <stdio.h>

list_t * list_create(int data)
{
    list_t * list = malloc(sizeof(list_t));
    list->data = data;
    list->next = NULL;
    return list;
}

list_t * list_prepend(list_t * head, int data)
{
    list_t * list = malloc(sizeof(list_t));
    list->data = data;
    list->next = head;
    return list;
}

list_t * list_append(list_t * head, int data)
{
    list_t * tail = malloc(sizeof(list_t));
    tail->data = data;
    tail->next = NULL;
    while(head->next)
        head = head->next;
    head->next = tail;
    return tail;
}

list_t * list_insert_i(list_t * head, int index, int data)
{
    for(int i = 0; i < index; i++)
    {
        if(head->next == NULL)
        {
            exit(1);
        }
        head = head->next;
    }
    list_t * new = malloc(sizeof(list_t));
    new->data = data;
    new->next = head->next;
    head->next = new;
}

list_t * list_insert_after(list_t * previous, int data)
{
    list_t * new = malloc(sizeof(list_t));
    new->data = data;
    new->next = previous->next;
    previous->next = new;
}

list_t * list_delete_i(list_t * head, int index)
{
    while(index-- > 1)
    {
        if(head->next == NULL)
        {
            exit(1);
        }
        head = head->next;
    }
    if(head->next == NULL) exit(1);
    list_t * tmp = head->next;
    head->next = head->next->next;
    free(tmp);
}

list_t * list_delete_after(list_t * previous, int after)
{
    if(previous->next == NULL) exit(1);
    list_t * tmp = previous->next;
    previous->next = previous->next->next;
    free(tmp);
}

list_t * list_getnth(list_t * head, int n)
{
    while(n --)
    {
        if(head->next == NULL) exit(1);
        head = head->next;
    }
    return head;
}

size_t list_length(list_t * head)
{
    size_t ct = 1;
    while(head->next != NULL)
    {
        head = head->next;
        ct ++;
    }
    return ct;
}

void list_destroy(list_t * head)
{
    if(head->next != NULL) list_destroy(head->next);
    free(head);
}

void list_print(list_t * head)
{
    printf("%d ", head->data);
    if(head->next != NULL) list_print(head->next);
    else printf("\n");
}

void list_foreach(list_t * head, Processor func, void * metadata)
{
    func(head, metadata);
    if(head->next != NULL) list_foreach(head->next, func, metadata);
}

list_t * list_map(list_t * head, Transformer func)
{
    list_t * new = malloc(sizeof(list_t));
    new->data = func(head->data);
    if(head->next == NULL) new->next = NULL;
    else new->next = list_map(head->next, func);
    return new;
}