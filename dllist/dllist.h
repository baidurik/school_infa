#ifndef DLLIST_H_DEFINED
#define DLLIST_H_DEFINED

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

typedef struct list_t {
    int value;
    struct list_t * prev;
    struct list_t * next;
} list_t;

list_t * list_create(int value);
list_t * list_appendleft(list_t * head, int value);
list_t * list_appendright(list_t * tail, int value);
list_t * list_popleft(list_t * head);
list_t * list_popright(list_t * tail);
list_t * list_insert_left(list_t * head, int value, int i);
list_t * list_insert_right(list_t * tail, int value, int i);
list_t * list_insert_after(list_t * curr, int value);
list_t * list_insert_before(list_t * curr, int value);
list_t * list_delete_left(list_t * head, int i);
list_t * list_delete_right(list_t * tail, int i);
list_t * list_delete_after(list_t * curr);
list_t * list_delete_before(list_t * curr);
list_t * list_get_left(list_t * head, int i);
list_t * list_get_right(list_t * tail, int i);

size_t list_length_left(list_t * head);
size_t list_length_right(list_t * tail);
void list_destroy(list_t * head, list_t * tail);
void list_print_left(list_t * head);
void list_print_right(list_t * tail);

typedef int Processor(list_t *, void * metadata);
void list_foreach_left(list_t * head, Processor func, void * metadata);
void list_foreach_right(list_t * tail, Processor func, void * metadata);

typedef struct bds_t
{
    list_t * head;
    list_t * tail;
} bds_t;

typedef int Transformer(int);
bds_t * list_map_left(list_t * head, Transformer func);
bds_t * list_map_right(list_t * tail, Transformer func);

#endif