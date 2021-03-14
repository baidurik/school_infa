#ifndef BTREE_C
#define BTREE_C

#include "btree.h"

// Private
// ============================================================ //

void move_right(node_t * node, int pos)
{
    node->n ++;
    node->children[node->n] = node->children[node->n-1];
    for(int i = node->n-1; i > pos; i --)
    {
        node->keys[i] = node->keys[i-1];
        node->children[i] = node->children[i-1];
    }
}

void move_left(node_t * node, int pos)
{
    for(int i = pos; i < node->n-1; i++)
    {
        node->keys[i] = node->keys[i+1];
        node->children[i] = node->children[i+1];
    }
    node->children[node->n-1] = node->children[node->n];
    node->n --;
}

void swap(node_t ** n1, node_t ** n2)
{
    node_t * tmp = *n1;
    *n1 = *n2;
    *n2 = tmp;
}

int get_parent_pos(node_t * node)
{
    if(node->parent == NULL) return -1;
    else
    {
        for(int i = 0; i < node->parent->n; i++)
        {
            if(node->parent->keys[i] > node->keys[0]) return i;
        }
        return node->parent->n;
    }
}

// ============================================================ //

node_t * node_create(int t, node_t * parent, bool is_leaf)
{
    node_t * node = malloc(sizeof(node_t));
    node->n = 0;
    node->parent = parent;
    node->keys = malloc(sizeof(int) * (2 * t - 1));
    node->children = malloc(sizeof(node_t) * (2 * t));
    node->is_leaf = is_leaf;
    return node;
}

node_t * node_split_up(node_t * node, btree_t * tree)
{
    int mid = tree->t - 1;
    node_t * new_friend = node_create(tree->t, node->parent, node->is_leaf);
    new_friend->n = tree->t - 1;
    for(int i = 0; i < new_friend->n; i++)
    {
        new_friend->keys[i] = node->keys[i+tree->t];
        if(!node->is_leaf)
        {
            new_friend->children[i] = node->children[i+tree->t];
            node->children[i+tree->t]->parent = new_friend;
        }
    }
    if(!node->is_leaf)
    {
        new_friend->children[new_friend->n] = node->children[2 * tree->t - 1];
        node->children[2 * tree->t - 1]->parent = new_friend;
    }
    node->n = tree->t - 1;
    return new_friend;
}

void node_partition(node_t * node, btree_t * tree)
{
    int mid = tree->t - 1;
    if(node->parent == NULL)
    {
        node_t * new_root = node_create(tree->t, NULL, false);
        new_root->n = 1;
        new_root->keys[0] = node->keys[mid];
        node_t * new_node = node_split_up(node, tree);
        new_root->children[1] = new_node;
        new_node->parent = new_root;
        node->parent = new_root;
        new_root->children[0] = node;
        tree->root = new_root;
    }
    else 
    {
        int pos = btree_insert_into(node->parent, node->keys[mid], tree);
        // btree_bypass(tree);
        node_t * new_node = node_split_up(node, tree);
        for(int i = 0; i < node->parent->n; i++)
        {
            if(node->parent->children[i] == node)
            {
                node->parent->children[i+1] = new_node;
                break;
            }
        }
        node->parent->children[pos+1] = new_node;
        new_node->parent = node->parent;
    }
}

void node_combine(node_t * n1, node_t * n2)
{
    for(int i = 0; i < n2->n; i++)
    {
        n1->keys[i+n1->n+1] = n2->keys[i];
        n1->children[i+n1->n+1] = n2->children[i];
    }
    n1->children[n1->n + n2->n + 1] = n2->children[n2->n];
    n1->n += n2->n;
    n1->n ++;
    node_destroy(n2);
}

void node_repair(node_t * node, btree_t * tree)
{
    int pos = get_parent_pos(node);
    if(pos != -1)
    {
        if(pos < node->parent->n && node->parent->children[pos+1]->n > tree->t-1)
        {
            node_t * neighbor = node->parent->children[pos+1];
            node->n ++;
            node->keys[node->n-1] = node->parent->keys[pos];
            node->children[node->n] = neighbor->children[0];
            node->parent->keys[pos] = neighbor->keys[0];
            move_left(neighbor, 0);
        }
        else if(pos > 0 && node->parent->children[pos-1]->n > tree->t -1)
        {
            node_t * neighbor = node->parent->children[pos-1];
            move_right(node, 0);
            node->keys[0] = node->parent->keys[pos-1];
            node->children[0] = neighbor->children[neighbor->n];
            node->parent->keys[pos-1] = neighbor->keys[neighbor->n - 1];
            neighbor->n --;
        }
        else 
        {
            node_t * neighbor;
            int insertion_pos = tree->t-1;
            if(pos < node->parent->n)
            {
                neighbor = node->parent->children[pos+1];
                insertion_pos --;
            }
            else 
            {
                neighbor = node->parent->children[pos-1];
                swap(&node, &neighbor);
                pos --;
            }
            node_combine(node, neighbor);
            node->keys[insertion_pos] = node->parent->keys[pos];
            node_t * tmp = node->parent->children[pos];
            move_left(node->parent, pos);
            node->parent->children[pos] = tmp;
            if(node->parent->n == tree->t-2) node_repair(node->parent, tree);
        }
    }
    else 
    {
        if(node->n == 0)
        {
            tree->root = node->children[0];
            node_destroy(node);
        }
    }
}

void node_destroy(node_t * node)
{
    free(node->children);
    free(node->keys);
    free(node);
}

// ============================================================ //

int btree_insert_into(node_t * node, int key, btree_t * tree)
{
    int where = 0;
    while(where < node->n)
    {
        if(node->keys[where] > key) break;
        where ++;
    }
    for(int i = node->n; i > where; i--)
    {
        node->keys[i] = node->keys[i-1];
        node->children[i+1] = node->children[i];
    }
    node->keys[where] = key;
    node->n ++;
    node->children[where+1] = node->children[where];
    if(node->n == 2 * tree->t - 1) node_partition(node, tree);
    return where;
}

void btree_insert_rec(node_t * node, int key, btree_t * tree)
{
    if(node->is_leaf) btree_insert_into(node, key, tree);
    else 
    {
        int where = 0;
        for(; where < node->n; where++)
        {
            if(node->keys[where] > key) break;
        }
        btree_insert_rec(node->children[where], key, tree);
    }
}

// ============================================================ //

void btree_remove_from_leaf(node_t * node, int pos, btree_t * tree)
{
    move_left(node, pos);
    if(node->n == tree->t - 2) node_repair(node, tree);
}

void btree_remove_from_mid(node_t * node, int pos, btree_t * tree)
{
    if(node->children[pos]->n > tree->t - 1)
    {
        node_t * child = node->children[pos];
        node->keys[pos] = child->keys[child->n-1];
        btree_remove_rec(child, child->n-1, tree);
    }
    else if(node->children[pos+1]->n > tree->t-1)
    {
        node_t * child = node->children[pos+1];
        node->keys[pos] = child->keys[0];
        btree_remove_rec(child, 0, tree);
    }
    else 
    {
        node_t * child = node->children[pos];
        node_combine(child, node->children[pos+1]);
        child->keys[tree->t-1] = node->keys[pos];
        move_left(node, pos);
        node->children[pos] = child;
        btree_remove_rec(child, tree->t-1, tree);
    }
}

void btree_remove_rec(node_t * node, int pos, btree_t * tree)
{
    if(node->is_leaf) btree_remove_from_leaf(node, pos, tree);
    else btree_remove_from_mid(node, pos, tree);
}

// ============================================================ //

search_result_t * btree_search_rec(node_t * node, int key)
{
    if(node == NULL) return NULL;
    for(int i = 0; i < node->n; i++)
    {
        if(node->keys[i] == key)
        {
            search_result_t * result = malloc(sizeof(search_result_t));
            result->node = node;
            result->pos = i;
            return result;
        }
        if(node->keys[i] > key) return btree_search_rec(node->children[i], key);
    }
    return btree_search_rec(node->children[node->n], key);
}

// ============================================================ //

void btree_bypass_rec(node_t * node)
{
    for(int i = 0; i < node->n; i++) printf("%d ", node->keys[i]);
    printf("\n");
    if(!node->is_leaf)
        for(int i = 0; i <= node->n; i++) btree_bypass_rec(node->children[i]);
}

// ============================================================ //

void btree_destroy_rec(node_t * node)
{
    if(!node->is_leaf)
    {
        for(int i = 0; i < node->n+1; i++)
        {
            btree_destroy_rec(node->children[i]);
        }
    }
    node_destroy(node);
}

// ============================================================ //
// Public

btree_t * btree_create(int t)
{
    btree_t * btree = malloc(sizeof(btree_t));
    btree->t = t;
    btree->root = node_create(t, NULL, true);
    return btree;
}

void btree_insert(btree_t * tree, int key)
{
    btree_insert_rec(tree->root, key, tree);
}

search_result_t * btree_search(btree_t * tree, int key)
{
    return btree_search_rec(tree->root, key);
}

void btree_bypass(btree_t * tree)
{
    btree_bypass_rec(tree->root);
}

void btree_remove(btree_t * tree, int key)
{
    search_result_t * found = btree_search(tree, key);
    if(found == NULL) return;
    btree_remove_rec(found->node, found->pos, tree);
}

void btree_destroy(btree_t * btree)
{
    btree_destroy_rec(btree->root);
    free(btree);
}

#endif