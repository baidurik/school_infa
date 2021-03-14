#include <stdio.h>
#include "vector.h"
#include "vector.c"

void print_vector(struct vector_t * vect)
{
    for(int i = 0; i < vect->length; i++)
    {
        printf("%d ", vector_getnth(vect, i));
    }
    printf("\n");
}

int main()
{
    struct vector_t * vec = vector_create(0);
    vector_append(vec, 1);
    vector_append(vec, 2);
    print_vector(vec);
    vector_append(vec, 8);
    print_vector(vec);
    vector_delete(vec, 1);
    print_vector(vec);
    vector_insert(vec, 0, 19);
    print_vector(vec);
    // vector_insert(vec, 18, 14);
    // printf("did not get here");
    vector_clear(vec);
    print_vector(vec);
    vector_append(vec, 16);
    print_vector(vec);
    int arr[4] = {1, 2, 2, 4};
    struct vector_t  * v2 = vector_from_array(arr, 4);
    vector_extend(vec, v2);
    print_vector(vec);
    printf("%p %d\n", vector_getnthptr(vec, 3), *vector_getnthptr(vec, 3));
    vector_sort(vec);
    print_vector(vec);
    printf("%p %d\n", vector_bsearch(vec, 1), *vector_bsearch(vec, 1));
    printf("%p\n", vector_bsearch(vec, -19));

    struct vector_t * v3 = vector_clone(vec);
    vector_append(v3, 17);
    print_vector(vec);
    print_vector(v3);
    vector_destroy(v3);

    printf("%d ", vec->length);
    vector_resize(vec, 100);
    printf("%d\n", vec->length);
}
