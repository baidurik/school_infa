#include "dllist.c"
#include <stdio.h>

struct sum{int s;};

int sq(int x)
{
    return x * x;
}

int calc_sum(list_t * head, void * metadata)
{
    struct sum * conv = (struct sum *) metadata;
    conv->s += head->value;
}

int main()
{
    list_t * head = list_create(7);
    list_t * tail = head;
    list_print_left(head);
    printf("===========================================\n");

    head = list_appendleft(head, 3);
    tail = list_appendright(tail, 6);
    list_print_right(tail);
    printf("===========================================\n");

    head = list_popleft(head);
    list_print_left(head);
    head = list_appendleft(head, 17);
    list_print_left(head);

    tail = list_popright(tail);
    list_print_right(tail);
    tail = list_appendright(tail, 18);
    list_print_right(tail);
    printf("===========================================\n");

    head = list_appendleft(head, 8);
    head = list_appendleft(head, 12);
    tail = list_appendright(tail, 19);
    list_print_right(tail);

    list_insert_left(head, 15, 2);
    list_print_left(head);
    // list_insert_left(head, 15, 188);
    // printf("didn't get here");

    list_insert_right(tail, 192, 2);
    list_print_right(tail);
    printf("===========================================\n");

    list_t * third = list_get_left(head, 2);
    list_print_left(third);
    list_insert_after(third, 111);
    list_print_left(head);

    list_t * third_right = list_get_right(tail, 2);
    list_print_right(third_right);
    list_insert_before(third_right, 121);
    list_print_left(head);
    printf("===========================================\n");

    list_delete_left(head, 4);
    list_print_left(head);
    list_delete_right(tail, 1);
    list_print_left(head);
    // list_delete_left(head, 188);
    // printf("didn't get here");
    printf("===========================================\n");


    printf("%d\n", list_length_left(head));
    third = list_get_left(head, 2);
    list_delete_after(third);
    list_delete_before(third);
    list_print_left(head);
    printf("%d\n", list_length_right(tail));
    printf("===========================================\n");

    struct sum * metadata_left = malloc(sizeof(struct sum));
    metadata_left->s = 0;
    list_foreach_left(head, calc_sum, (void *)metadata_left);
    printf("%d\n", metadata_left->s);

    head = list_appendleft(head, 6);
    struct sum * metadata_right = malloc(sizeof(struct sum));
    metadata_right->s = 0;
    list_foreach_right(tail, calc_sum, (void *)metadata_right);
    printf("%d\n", metadata_right->s);
    printf("===========================================\n");

    bds_t * bds = list_map_left(head, sq);
    list_print_left(bds->head);

    bds_t * bds_right = list_map_right(tail, sq);
    list_print_left(bds_right->head);
    printf("===========================================\n");

    list_destroy(head, tail);
    printf("Done :3");
}