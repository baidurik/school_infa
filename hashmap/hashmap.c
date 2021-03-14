#include "hashmap.h"

long long hash(char * s, long long mod, int p)
{
    long long res = 0;
    long long p_pow = 1;
    while(*s)
    {
        res += ((*s - 'a' + 1) * p_pow) % mod;
        res %= mod;
        p_pow *= p;
        p %= mod;
        s ++;
    }
    return res;
}

list_t * list_create(pair_t * value)
{
    list_t * head = malloc(sizeof(list_t));
    head->value = value;
    head->next = NULL;
    return head;
}

void list_append(list_t * head, pair_t * value)
{
    while(head->next != NULL) head = head->next;
    list_t * new = malloc(sizeof(list_t));
    new->next = NULL;
    new->value = value;
    head->next = new;
}

pair_t * list_get(list_t * head, char * key)
{
    while(head != NULL)
    {
        if(strcmp(head->value->key, key) == 0) return head->value;
        head = head->next;
    }
    return NULL;
}

list_t * list_delete(list_t * head, char * key)
{
    if(head == NULL) return NULL;
    if(strcmp(head->value->key, key) == 0)
    {
        list_t * tmp = head->next;
        free(head->value);
        free(head);
        return tmp;
    }
    head->next = list_delete(head->next, key);
    return head;
}

void list_destroy(list_t * head)
{
    if(head->next != NULL) list_destroy(head->next);
    free(head->value);
    free(head);
}

pair_t * pair_create(char * key, int value)
{
    pair_t * new = malloc(sizeof(pair_t));
    new->key = key;
    new->value = value;
    return new;
}

hashmap_t * hashmap_create(long long mod, int alphabetic)
{
    hashmap_t * hashmap = malloc(sizeof(hashmap));
    hashmap->mod = mod;
    hashmap->p = alphabetic;
    hashmap->array = malloc(sizeof(list_t *) * mod);
    return hashmap;
}

pair_t * hashmap_get(hashmap_t * hashmap, char * key)
{
    long long hashed = hash(key, hashmap->mod, hashmap->p);
    if(hashmap->array[hashed] == NULL) return NULL;
    return list_get(hashmap->array[hashed], key);
}

void hashmap_update(hashmap_t * hashmap, char * key, int value)
{
    pair_t * found = hashmap_get(hashmap, key);
    if(found == NULL) return;
    found->value = value;
}

void hashmap_insert(hashmap_t * hashmap, char * key, int value)
{
    long long hashed = hash(key, hashmap->mod, hashmap->p);
    if(hashmap_get(hashmap, key) == NULL)
    {
        if(hashmap->array[hashed] == NULL) hashmap->array[hashed] = list_create(pair_create(key, value));
        else list_append(hashmap->array[hashed], pair_create(key, value));
    }
    else hashmap_update(hashmap, key, value);
}

void hashmap_delete(hashmap_t * hashmap, char * key)
{
    long long hashed = hash(key, hashmap->mod, hashmap->p);
    if(hashmap->array[hashed] == NULL) return;
    hashmap->array[hashed] = list_delete(hashmap->array[hashed], key);
}

void hashmap_destroy(hashmap_t * hashmap)
{
    for(int i = 0; i < hashmap->mod; i++) list_destroy(hashmap->array[i]);
    free(hashmap->array);
    free(hashmap);
}
