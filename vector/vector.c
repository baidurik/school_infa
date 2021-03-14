#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct vector_t * vector_create(size_t size)
{
    struct vector_t * vect = malloc(sizeof(struct vector_t));
    if(vect == NULL) exit(3);
    vect->capacity = size;
    vect->length = size;
    vect->data = malloc(size * sizeof(int));
    if(vect->data == NULL) exit(3);
    return vect;
}

struct vector_t * vector_from_array(int * array, size_t n)
{
    struct vector_t * vect = malloc(sizeof(struct vector_t));
    if(vect == NULL) exit(3);
    vect->capacity = n;
    vect->length = n;
    vect->data = malloc(n * sizeof(int));
    if(vect->data == NULL) exit(3);
    for(int i = 0; i < n; i++) vect->data[i] = array[i];
    return vect;
}

struct vector_t * vector_clone(struct vector_t * v)
{
    struct vector_t * vect = malloc(sizeof(struct vector_t));
    if(vect == NULL) exit(3);
    vect->capacity = v->capacity;
    vect->length = v->length;
    vect->data = malloc(v->capacity * sizeof(int));
    if(vect->data == NULL) exit(3);
    for(int i = 0; i < v->length; i++) vect->data[i] = v->data[i];
    return vect;
}

void vector_destroy(struct vector_t * v)
{
    free(v->data);
    free(v);
    v = NULL;
}

int vector_getnth(struct vector_t * v, int n)
{
    if(n > v->length || n < 0) exit(2);
    return v->data[n];
}

int * vector_getnthptr(struct vector_t * v, int n)
{
    if(n > v->length || n < 0) exit(2);
    return v->data + n;
}

void vector_append(struct vector_t * v, int x)
{
    if(v->length == v->capacity)
    {
        if(v->capacity == 0) v->capacity = 1;
        else v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        if(v->data == NULL) exit(3);
    }
    v->data[v->length] = x;
    v->length ++;
}

void vector_insert(struct vector_t * v, int i, int x)
{
    if(i < 0 || i > v->length) exit(2);
    if(v->length == v->capacity)
    {
        if(v->capacity == 0) v->capacity = 1;
        else v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(int));
        if(v->data == NULL) exit(3);
    }
    for(int j = v->length; j > i; j --) v->data[j] = v->data[j-1];
    v->data[i] = x;
    v->length ++;
}

void vector_delete(struct vector_t * v, int i)
{
    if(i < 0 || i >= v->length) exit(2);
    for(int j = i; j < v->length-1; j++) v->data[j] = v->data[j+1];
    v->length --;
}

void vector_extend(struct vector_t * v1, struct vector_t * v2)
{
    for(int i = 0; i < v2->length; i++)
    {
        vector_append(v1, v2->data[i]);
    }
}

int vector_resize(struct vector_t * v1, size_t new_size)
{
    v1->data = realloc(v1->data, new_size * sizeof(int));
    if(v1->data == NULL)
    {
        return 1;
        exit(3);
    }
    v1->length = new_size;
    v1->capacity = new_size;
}

void vector_clear(struct vector_t * v)
{
    v->data = realloc(v->data, 0);
    v->length = 0;
    v->capacity = 0;
}

int partition(struct vector_t * v, int l, int r)
{
    int m = v->data[(l + r) / 2];
    int i = l;
    int j = r;
    while(i < j)
    {
        printf("%d %d\n", i, j);
        while(v->data[i] < m) i ++;
        while(v->data[j] > m) j --;
        if(i >= j) break;
        int tmp = v->data[i];
        v->data[i] = v->data[j];
        v->data[j] = tmp;
        i++;
        j--;
    }
    return j;
}

void quicksort(struct vector_t * v, int l, int r)
{
    if(l < r)
    {
        int m = partition(v, l, r);
        quicksort(v, l, m);
        quicksort(v, m+1, r);
    }
}

void vector_sort(struct vector_t * v)
{
    quicksort(v, 0, v->length-1);
}

int * vector_bsearch(struct vector_t * v, int x)
{
    int l = -1;
    int r = v->length;
    while(l < r-1)
    {
        int m = (l+r) / 2;
        if(v->data[m] <= x) l = m;
        else r = m;
    }
    if(l >= 0 && l < v->length && v->data[l] == x) return v->data + l;
    return NULL;
}

int vector_process(struct vector_t * v, Processor * func, void * metadata, size_t metadata_size)
{
    for(int i = 0; i < v->length; i++)
    {
        func(i, metadata, metadata_size);
    }
}