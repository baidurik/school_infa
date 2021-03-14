#include "tree.c"
#include <stdio.h>

int main()
{
    tree_t * root = tree_create(7);
    root = tree_insert(root, 8);
    root = tree_insert(root, 9);
    root = tree_insert(root, 10);
    root = tree_insert(root, 11);
    tree_print(root);
    printf("\n");


    printf("%d\n", root->value);
    tree_t * nine = tree_find(root, 10);
    printf("%d %d %d\n", nine->value, nine->right->value, nine->left->value);
    nine->right = tree_delete(nine->right);
    tree_print(root);
    printf("\n");

    root = tree_find_delete(root, 9);
    for(int i = 0; i < 7; i++) root = tree_insert(root, i);
    tree_print(root);
    printf("\n%d\n", tree_height(root));

    tree_destroy(root);
    printf("Done :3");
}