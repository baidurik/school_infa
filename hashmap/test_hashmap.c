#include "hashmap.c"
#include <stdio.h>
int main()
{
    hashmap_t * dict = hashmap_create(1e9+7, 31);
    hashmap_insert(dict, "hello", 15);
    hashmap_insert(dict, "nou", 92);
    hashmap_insert(dict, "freedom", 33);
    hashmap_insert(dict, "yeet", 111);
    hashmap_insert(dict, "hohohohoho", 192);
    pair_t * got = hashmap_get(dict, "hello");
    printf("%s -> %d\n", got->key, got->value);
    pair_t * got_one_more = hashmap_get(dict, "hohohohoho");
    printf("%s -> %d\n", got_one_more->key, got_one_more->value);
    printf("================================\n");
    hashmap_update(dict, "hohohohoho", 122);
    got_one_more = hashmap_get(dict, "hohohohoho");
    printf("%s -> %d\n", got_one_more->key, got_one_more->value);
    hashmap_insert(dict, "hello", 225);
    got = hashmap_get(dict, "hello");
    printf("%s -> %d\n", got->key, got->value);
    printf("================================\n");
    got = hashmap_get(dict, "nothere");
    printf("%p\n", got);
    hashmap_delete(dict, "hello");
    got = hashmap_get(dict, "hello");
    printf("%p\n", got);
    printf("================================\n");
    printf("Done :3");
}