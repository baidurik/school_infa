#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node_t
{
    int n;
    int * keys;
    struct node_t ** children;
    struct node_t * parent;
    bool is_leaf;
} node_t;

typedef struct btree_t
{
    node_t * root;
    int t;
} btree_t;

typedef struct search_result_t
{
    node_t * node;
    int pos;
} search_result_t;

// Private
void move_right(node_t * node, int pos);
void move_left(node_t * node, int pos);
void swap(node_t ** n1, node_t ** n2);
int get_parent_pos(node_t * node);

node_t * node_create(int t, node_t * parent, bool is_leaf);
node_t * node_split_up(node_t * node, btree_t * tree);
void node_partition(node_t * node, btree_t * tree);

void node_combine(node_t * n1, node_t * n2);
void node_repair(node_t * node, btree_t * tree);
void node_destroy(node_t * node);

int btree_insert_into(node_t * node, int key, btree_t * tree);
void btree_insert_rec(node_t * node, int key, btree_t * tree);

void btree_remove_from_leaf(node_t * node, int pos, btree_t * tree);
void btree_remove_from_mid(node_t * node, int pos, btree_t * tree);
void btree_remove_rec(node_t * node, int pos, btree_t * tree);

search_result_t * btree_search_rec(node_t * node, int key);

void btree_bypass_rec(node_t * node);

void btree_destroy_rec(node_t * node);


// Public
btree_t * btree_create(int t);
void btree_insert(btree_t * tree, int key);
search_result_t * btree_search(btree_t * tree, int key);
void btree_bypass(btree_t * tree);
void btree_remove(btree_t * tree, int key);
void btree_destroy(btree_t * btree);

#endif