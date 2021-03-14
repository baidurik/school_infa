#include "heap.h"

void swap(int * a, int * b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

heap_t * heap_create(int value)
{
    heap_t * heap = malloc(sizeof(heap_t));
    heap->capacity = 2;
    heap->size = 2;
    heap->arr = malloc(sizeof(int) * heap->capacity);
    heap->arr[1] = value;
}

heap_t * heap_from_arr(int * arr, int size)
{
    heap_t * heap = malloc(sizeof(heap_t));
    heap->capacity = 2 *size + 2;
    heap->size = size + 1;
    heap->arr = malloc(sizeof(int) * heap->capacity);
    for(int i = 0; i < heap->size-1; i++)
    {
        heap->arr[i+1] = arr[i];
    }
    for(int i = heap->size / 2; i >= 1; i--)
    {
        heapify_down(heap, i);
    }
    return heap;
}

void append(heap_t * heap, int value)
{
    if(heap->size == heap->capacity)
    {
        heap->capacity *= 2;
        heap->arr = realloc(heap->arr, sizeof(int) * heap->capacity);
    }
    heap->arr[heap->size++] = value;
}

void heapify_up(heap_t * heap, int index)
{
    while(index > 1 && heap->arr[index/2] < heap->arr[index])
    {
        swap(&heap->arr[index / 2], &heap->arr[index]);
        index /= 2;
    }
}

void heapify_down(heap_t * heap, int index)
{
    if(2 * index >= heap->size) return;
    if(2 * index == heap->size - 1)
    {
        if(heap->arr[2 * index] > heap->arr[index]) swap(&heap->arr[2 * index], &heap->arr[index]);
        return;
    }
    if(heap->arr[2 * index] > heap->arr[2 * index + 1])
    {
        if(heap->arr[2 * index] > heap->arr[index])
        {
            swap(&heap->arr[2 * index], &heap->arr[index]);
            heapify_down(heap, 2 * index);
        }
    }
    else 
    {
        if(heap->arr[2 * index + 1] > heap->arr[index])
        {
            swap(&heap->arr[2 * index + 1], &heap->arr[index]);
            heapify_down(heap, 2 * index + 1);
        }
    }
}

void heap_insert(heap_t * heap, int value)
{
    append(heap, value);
    heapify_up(heap, heap->size-1);
}

int heap_max(heap_t * heap)
{
    return heap->arr[1];
}

void heap_delete_max(heap_t * heap)
{
    heap->size --;
    heap->arr[1] = heap->arr[heap->size];
    heapify_down(heap, 1);
}

int heap_extract_max(heap_t * heap)
{
    int max = heap_max(heap);
    heap_delete_max(heap);
    return max;
}

void heap_destroy(heap_t * heap)
{
    free(heap->arr);
    free(heap);
}