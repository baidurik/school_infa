#include <stdio.h>
#include "heap.c"
int main()
{
    int n;
    scanf("%d", &n);
    int * arr = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++) scanf("%d", &arr[i]);
    heap_t * heap = heap_from_arr(arr, n);
    for(int i = 0; i < n; i++) arr[i] = heap_extract_max(heap);
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
}