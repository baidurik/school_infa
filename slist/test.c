#include "slist.c"
#include <stdio.h>

int square(int x)
{
    return x * x;
}

struct sum_st
{
    int s;
};

int sum(list_t * list, void * metadata)
{
    struct sum_st * conv = (struct sum_st *)metadata;
    conv->s += list->data;
}

int main()
{
    list_t * list = list_create(6);
    list_print(list);
    printf("=========================================\n");

    list = list_prepend(list, 8);
    list_print(list);
    list = list_prepend(list, 6);
    list_print(list);
    printf("=========================================\n");

    list_append(list, 12);
    list_print(list);
    list_append(list, -2);
    list_print(list);
    printf("=========================================\n");

    list_insert_i(list, 2, 18);
    list_print(list);
    list_insert_i(list, 0, 16);
    list_print(list);
    printf("=========================================\n");

    list_t * fifth = list_getnth(list, 5);
    printf("%d\n", fifth->data);
    list_t * first = list_getnth(list, 0);
    printf("%d\n", first->data);
    list_insert_after(fifth, 17);
    list_print(fifth);
    list_print(list);
    printf("=========================================\n");

    // list_insert_i(list, list_length(list), 5);
    // printf("Didn't get here :)");

    list_insert_i(list, list_length(list)-1, 5);
    printf("Got here :)\n");
    list_print(list);
    printf("=========================================\n");

    list_delete_i(list, 2);
    list_print(list);
    list_delete_i(list, 1);
    list_print(list);
    list_delete_i(list, 0);
    list_print(list);
    printf("=========================================\n");
    // list_delete_i(list, 9999);
    // printf("Didn't get here :)\n");
    
    list_t * second = list_getnth(list, 2);
    list_delete_after(second, -1);   // Серьезно не понимаю, зачем нужен второй параметр
    list_print(list);
    printf("=========================================\n");

    list_t * new_list = list_map(list, square);
    list_print(new_list);
    printf("=========================================\n");

    struct sum_st * sm = malloc(sizeof(struct sum_st));
    sm->s = 0;
    list_foreach(list, sum, (void *)sm);
    printf("%d\n", sm->s);
    printf("=========================================\n");

    list_destroy(list);
    printf("Done :3");
}