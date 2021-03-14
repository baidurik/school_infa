#include "tree.h"

size_t tree_height(tree_t * root)
{
    if(root == NULL) return 0;
    return root->height;
}

tree_t * tree_balance(tree_t * node)
{
    tree_fix_height(node);
    if(tree_get_balance(node) == 2)
    {
        if(tree_get_balance(node->right) < 0) node->right = tree_rotate_right(node->right);
        return tree_rotate_left(node);
    }
    if(tree_get_balance(node) == -2)
    {
        if(tree_get_balance(node->left) > 0) node->left = tree_rotate_left(node->left);
        return tree_rotate_right(node);
    }
    return node;
}

void tree_fix_height(tree_t * node)
{
    node->height = max(tree_height(node->left), tree_height(node->right)) + 1;
}

int tree_get_balance(tree_t * node)
{
    return (int)tree_height(node->right) - (int)tree_height(node->left);
}

tree_t * tree_create(int value)
{
    tree_t * new = malloc(sizeof(tree_t));
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    new->height = 1;
    return new;
}

tree_t * tree_rotate_left(tree_t * node)
{
    tree_t * right = node->right;
    node->right = right->left;
    right->left = node;
    tree_fix_height(node);
    tree_fix_height(right);
    return right;
}

tree_t * tree_rotate_right(tree_t * node)
{
    tree_t * left = node->left;
    node->left = left->right;
    left->right = node;
    tree_fix_height(node);
    tree_fix_height(left);
    return left;
}

tree_t * tree_insert(tree_t * root, int value)
{
    if(value > root->value)
    {
        if(root->right == NULL)
        {
            tree_t * new = malloc(sizeof(tree_t));
            new->value = value;
            new->left = NULL;
            new->right = NULL;
            new->height = 1;
            root->right = new;
        }
        else
        {
            root->right = tree_insert(root->right, value);
        }
        root->height = max(root->height, root->right->height + 1);
    }
    else 
    {
        if(root->left == NULL)
        {
            tree_t * new = malloc(sizeof(tree_t));
            new->value = value;
            new->left = NULL;
            new->right = NULL;
            new->height = 1;
            root->left = new;
        }
        else 
        {
            root->left = tree_insert(root->left, value);
        }
        root->height = max(root->height, root->left->height + 1);
    }
    return tree_balance(root);
}

tree_t * tree_min(tree_t * root)
{
    if(root->left == NULL) return root;
    else return tree_min(root->left);
}

tree_t * tree_max(tree_t * root)
{
    if(root->right == NULL) return root;
    else return tree_max(root->right)
;}

tree_t * tree_find(tree_t * root, int value)
{
    if(root == NULL || root->value == value) return root;
    if(value < root->value) return tree_find(root->left, value);
    else return tree_find(root->right, value);
}

tree_t * tree_delete(tree_t * node)
{
    if(node->left != NULL && node->right != NULL)
    {
        tree_t * leftmost = node->right;
        tree_t * leftmost_parent = node;
        if(leftmost->left == NULL)
        {
            leftmost->left = node->left;
            free(node);
            return leftmost;
        }
        while(leftmost->left != NULL)
        {
            leftmost_parent = leftmost;
            leftmost = leftmost->left;
        }
        if(leftmost_parent != node)
        {
            leftmost_parent->left = leftmost->right;
        }
        leftmost->right = node->right;
        leftmost->left = node->left;
        free(node);
        return leftmost;
    }
    else if(node->left != NULL)
    {
        tree_t * tmp = node->left;
        free(node);
        return tmp;
    }
    else if(node->right != NULL)
    {
        tree_t * tmp = node->right;
        free(node);
        return tmp;
    }
    else 
    {
        free(node);
        return NULL;
    }
}

tree_t * tree_find_delete(tree_t * root, int value)
{
    if(value < root->value)
    {
        if(root->left != NULL)
        {
            if(root->left->value == value) root->left = tree_delete(root->left);
            else tree_find_delete(root->left, value);
        }
        return root;
    }
    else if(value > root->value)
    {
        if(root->right != NULL)
        {
            if(root->right->value == value) root->right = tree_delete(root->right);
            else tree_find_delete(root->right, value);
        }
        return root;
    }
    else return tree_delete(root);
}

void tree_destroy(tree_t * root)
{
    if(root->left != NULL) tree_destroy(root->left);
    if(root->right != NULL) tree_destroy(root->right);
    free(root);
}

void tree_print(tree_t * root)  // Очень стремный вывод, но показывает, что всё вроде бы работает
{
    if(root == NULL) printf("# ");
    else
    {
        printf("%d ", root->value);
        tree_print(root->left);
        tree_print(root->right);
    }     
}