#include "dllist.h"

list_t * list_create(int value)
{
    list_t * list = malloc(sizeof(list_t));
    list->value = value;
    list->next = NULL;
    list->prev = NULL;
}

list_t * list_appendleft(list_t * head, int value)
{
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->next = head;
    new->prev = NULL;
    head->prev = new;
    return new;
}

list_t * list_appendright(list_t * tail, int value)
{
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->prev = tail;
    new->next = NULL;
    tail->next = new;
    return new;
}

list_t * list_popleft(list_t * head)
{
    list_t * tmp = head->next;
    free(head);
    tmp->prev = NULL;
    return tmp;
}

list_t * list_popright(list_t * tail)
{
    list_t * tmp = tail->prev;
    free(tail);
    tmp->next = NULL;
    return tmp;
}

list_t * list_insert_left(list_t * head, int value, int i)
{
    while(i--)
    {
        if(head->next == NULL) exit(1);
        head = head->next;
    }
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->next = head->next;
    if(head->next != NULL) head->next->prev = new;
    new->prev = head;
    head->next = new;
    return new;
}

list_t * list_insert_right(list_t * tail, int value, int i)
{
    while(i--)
    {
        if(tail->prev == NULL) exit(1);
        tail = tail->prev;
    }
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->prev = tail->prev;
    if(tail->prev != NULL) tail->prev->next = new;
    new->next = tail;
    tail->prev = new;
}

list_t * list_insert_after(list_t * curr, int value)
{
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->next = curr->next;
    if(curr->next != NULL) curr->next->prev = new;
    new->prev = curr;
    curr->next = new;
    return new;
}

list_t * list_insert_before(list_t * curr, int value)
{
    list_t * new = malloc(sizeof(list_t));
    new->value = value;
    new->prev = curr->prev;
    if(curr->prev != NULL) curr->prev->next = new;
    new->next = curr;
    curr->prev = new;
}

list_t * list_delete_left(list_t * head, int i)
{
    while(i--)
    {
        if(head->next == NULL) exit(1);
        head = head->next;
    }
    if(head->next != NULL) head->next->prev = head->prev;
    if(head->prev != NULL) head->prev->next = head->next;
    free(head);
}

list_t * list_delete_right(list_t * tail, int i)
{
    while(i--)
    {
        if(tail->prev == NULL) exit(1);
        tail = tail->prev;
    }
    if(tail->next != NULL) tail->next->prev = tail->prev;
    if(tail->prev != NULL) tail->prev->next = tail->next;
}

list_t * list_delete_after(list_t * curr)
{
    if(curr->next == NULL) return NULL;
    if(curr->next->next != NULL) curr->next->next->prev = curr;
    list_t * tmp = curr->next;
    curr->next = curr->next->next;
    free(tmp);
}

list_t * list_delete_before(list_t * curr)
{
    if(curr->prev == NULL) return NULL;
    if(curr->prev->prev != NULL) curr->prev->prev->next = curr;
    list_t * tmp = curr->prev;
    curr->prev = curr->prev->prev;
    free(tmp);
}

list_t * list_get_left(list_t * head, int i)
{
    while(i--)
    {
        if(head->next == NULL) exit(0);
        head = head->next;
    }
    return head;
}

list_t * list_get_right(list_t * tail, int i)
{
    while(i--)
    {
        if(tail->prev == NULL) exit(0);
        tail = tail->prev;
    }
    return tail;
}

size_t list_length_left(list_t * head)
{
    size_t ct = 1;
    while(head->next != NULL)
    {
        head = head->next;
        ct ++;
    }
    return ct;
}

size_t list_length_right(list_t * tail)
{
    size_t ct = 1;
    while(tail->prev != NULL)
    {
        tail = tail->prev;
        ct ++;
    }
    return ct;
}

void list_destroy(list_t * head, list_t * tail)
{
    if(head == tail)
    {
        free(head);
    }
    else 
    {
        list_destroy(head->next, tail);
        free(head);
    }
}

void list_print_left(list_t * head)
{
    printf("%d ", head->value);
    if(head->next != NULL) list_print_left(head->next);
    if(head->next == NULL) printf("\n");
}

void list_print_right(list_t * tail)
{
    printf("%d ", tail->value);
    if(tail->prev != NULL) list_print_right(tail->prev);
    if(tail->prev == NULL) printf("\n");
}

void list_foreach_left(list_t * head, Processor func, void * metadata)
{
    func(head, metadata);
    if(head->next != NULL) list_foreach_left(head->next, func, metadata);
}

void list_foreach_right(list_t * tail, Processor func, void * metadata)
{
    func(tail, metadata);
    if(tail->prev != NULL) list_foreach_right(tail->prev, func, metadata);
}

bds_t * list_map_left(list_t * head, Transformer func)
{
    bds_t * bds = malloc(sizeof(bds_t));
    list_t * new_head = malloc(sizeof(list_t *));
    new_head->value = func(head->value);
    new_head->next = NULL;
    new_head->prev = NULL;
    bds->head = new_head;
    list_t * new;
    while(head->next != NULL)
    {
        head = head->next;
        new = malloc(sizeof(list_t));
        new->value = func(head->value);
        new_head->next = new;
        new->prev = new_head;
        new->next = NULL;
        new_head = new;
    }
    bds->tail = new_head;
}

bds_t * list_map_right(list_t * tail, Transformer func)
{
    bds_t * bds = malloc(sizeof(bds_t));
    list_t * new_tail = malloc(sizeof(list_t));
    new_tail->value = func(tail->value);
    new_tail->next = NULL;
    new_tail->prev = NULL;
    bds->tail = new_tail;
    list_t * new;
    while(tail->prev != NULL)
    {
        tail = tail->prev;
        new = malloc(sizeof(list_t));
        new->value = func(tail->value);
        new_tail->prev = new;
        new->next = new_tail;
        new->prev = NULL;
        new_tail = new;
    }
    bds->head = new_tail;
}
