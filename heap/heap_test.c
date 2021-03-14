#include "heap.c"
#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);
    int * arr = malloc(sizeof(int) * n);
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    heap_t * heap = heap_from_arr(arr, n);
    heap_insert(heap, 19);
    printf("%d\n", heap_max(heap));
    heap_delete_max(heap);
    heap_delete_max(heap);
    printf("%d\n", heap_max(heap));
    heap_destroy(heap);
}