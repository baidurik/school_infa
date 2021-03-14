#include <stdlib.h>

typedef struct heap_t
{
    int size;
    int * arr;
    int capacity;
} heap_t;

void swap(int * a, int * b);

void heapify_up(heap_t * heap, int index);
void heapify_down(heap_t * heap, int index);

heap_t * heap_create(int value);
heap_t * heap_from_arr(int * arr, int size);
void heap_insert(heap_t * heap, int value);
int heap_max(heap_t * heap);
void heap_delete_max(heap_t * heap);
int heap_extract_max(heap_t * heap);
void heap_destroy(heap_t * heap);