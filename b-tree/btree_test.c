#include "btree.c"

int main()
{
    btree_t * btree = btree_create(2);
    btree_insert(btree, 8);
    btree_insert(btree, 7);
    btree_insert(btree, 6);
    btree_insert(btree, 5);
    // btree_bypass(btree);
    btree_insert(btree, 4);
    btree_insert(btree, 9);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 9);
    btree_bypass(btree);
    printf("===========================\n");
    btree_insert(btree, 9);
    btree_remove(btree, 6);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 4);
    btree_bypass(btree);
    printf("===========================\n");
    btree_insert(btree, 4);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 9);
    btree_bypass(btree);
    printf("===========================\n");
    printf("Из листьев поудаляли, ща попробуем из середины дерева\n");
    btree_insert(btree, 10);
    btree_insert(btree, 11);
    btree_insert(btree, 12);
    btree_insert(btree, 1);
    btree_insert(btree, 2);
    btree_insert(btree, 3);
    btree_insert(btree, 13);
    btree_insert(btree, 14);
    btree_insert(btree, 15);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 13);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 5);
    btree_bypass(btree);
    printf("===========================\n");
    btree_remove(btree, 4);
    btree_bypass(btree);
    printf("===========================\n");
    printf("Вроде всё работает, я считаю это успех\n");
    btree_destroy(btree);
    printf("Done :3");
}