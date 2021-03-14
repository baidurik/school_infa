#include <stdlib.h>
#include <stdio.h>

typedef struct tree_t tree_t;
struct tree_t
{
    int value;
    size_t height;
    tree_t * left;
    tree_t * right;
};

// Вспомогательные приватные функции, нужны для нормальной работы других
// Но можно их заюзать отдельно, если хотите
// ===========================================================
#define max(x, y) ((x) > (y) ? (x) : (y))

tree_t * tree_rotate_left(tree_t * node);
tree_t * tree_rotate_right(tree_t * node);
tree_t * tree_balance(tree_t * node);   // Функция для балансировки поддерева
int tree_get_balance(tree_t * node);  // Разность высот
void tree_fix_height(tree_t * node);    // Пересчитать высоту
// ===========================================================

tree_t * tree_create(int value);
tree_t * tree_insert(tree_t * root, int value);

tree_t * tree_min(tree_t * root);
tree_t * tree_max(tree_t * root);

tree_t * tree_find(tree_t * root, int value);
tree_t * tree_delete(tree_t * node);
tree_t * tree_find_delete(tree_t * root, int value);

size_t tree_height(tree_t * root);
void tree_destroy(tree_t * root);
void tree_print(tree_t * root);