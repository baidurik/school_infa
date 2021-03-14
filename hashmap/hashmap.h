#include <stdlib.h>
#include <string.h>

typedef struct pair_t
{
    char * key;
    int value;

} pair_t;

typedef struct list_t 
{
    pair_t * value;
    struct list_t * next;

} list_t;

typedef struct hashmap_t 
{
    long long mod;
    int p;
    list_t ** array;

} hashmap_t;


// Всякие функции других типов, необходимые для работы хешмапа
// Можно считать их приватными, наверное ))
// ================================================================
long long hash(char * s, long long mod, int p);

list_t * list_create(pair_t * value);
void list_append(list_t * head, pair_t * value);
pair_t * list_get(list_t * head, char * key);
list_t * list_delete(list_t * head, char * key);
void list_destroy(list_t * head);
pair_t * pair_create(char * key, int value);
void pair_destroy(pair_t * pair);
// ================================================================

hashmap_t * hashmap_create(long long mod, int alphabetic);
pair_t * hashmap_get(hashmap_t * hashmap, char * key);
void hashmap_insert(hashmap_t * hashmap, char * key, int value);
void hashmap_update(hashmap_t * hashmap, char * key, int value);
void hashmap_delete(hashmap_t * hashmap, char * key);
void hashmap_destroy(hashmap_t * hashmap);