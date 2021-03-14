#include "slist.c"
#include <stdio.h>

struct metadata 
{
    list_t * head;
    list_t * curr;
};

int square(list_t * head, void * metadata)
{
    struct metadata * mdata = (struct metadata *)metadata;
    list_t * appending = malloc(sizeof(list_t));
    appending->next = NULL;
    mdata->curr->data = head->data * head->data;
    if(head->next != NULL)
    {
        mdata->curr->next = appending;
        mdata->curr = appending;    
    }
}

list_t * list_map_2(list_t * head, Processor func)
{
    struct metadata * mdata = malloc(sizeof(mdata));
    mdata->head = malloc(sizeof(list_t));
    mdata->head->next = NULL;
    mdata->curr = mdata->head;
    list_foreach(head, func, (void *)mdata);
    return mdata->head;
}

int main()
{
    list_t * list = list_create(10);
    list_append(list, 8);
    list_append(list, 4);
    list_append(list, 3);
    list_print(list);
    list_t * anime = list_map_2(list, square);
    list_print(anime);                          // Первый элемент списка - фиктивный
}           