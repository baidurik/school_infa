#include <stdio.h>
#include "slist.c"
#include <math.h>

#define MAX_SIZE 32

list_t * list_merge(list_t * head1, list_t * head2)
{
    list_t * new;
    if(head1 == NULL) return head2;
    if(head2 == NULL) return head1;
    if(head1->data < head2->data)
    {
        new = head1;
        head1 = head1->next;
    }
    else 
    {
        new = head2;
        head2 = head2->next;
    }
    list_t * head = new;
    while(head1 != NULL && head2 != NULL)
    {
        if(head1->data < head2->data)
        {
            new->next = head1;
            head1 = head1->next;
        }
        else 
        {
            new->next = head2;
            head2 = head2->next;
        }
        new = new->next;
    }
    if(head1 == NULL) new->next = head2;
    if(head2 == NULL) new->next = head1;
    return head;
}

list_t * list_merge_sort(list_t * head)
{
    int size = MAX_SIZE;
    list_t ** hooks = malloc(size * sizeof(list_t *));
    for(int i = 0; i < size; i++) 
    {
        hooks[i] = malloc(sizeof(list_t));
        hooks[i]->next = NULL;
    }
    while(head != NULL)
    {
        list_t * off = head;
        head = head->next;
        off->next = NULL;
        for(int i = 0; i < size; i++)
        {
            if(hooks[i] == NULL)
            {
                hooks[i]->next = off;
                break;
            }
            if(i > 0) hooks[i-1]->next = NULL;
            hooks[i]->next = list_merge(off, hooks[i]->next);
            off = hooks[i]->next;
        }
    }
    for(int i = 1; i < size; i++)
    {
        hooks[i]->next = list_merge(hooks[i-1]->next, hooks[i]->next);
    }
    list_t * ret = hooks[size-1]->next;
    for(int i = 0; i < size; i++) free(hooks[i]);
    free(hooks);
    return ret;
}

int main()
{
    int n;
    scanf("%d", &n);
    int first;
    scanf("%d", &first);
    list_t * head = list_create(first);
    list_t * tail = head;
    for(int i = 0; i < n-1; i++)
    {
        int new;
        scanf("%d", &new);
        list_append(tail, new);
        tail = tail->next;
    }
    // printf("Flex");
    head = list_merge_sort(head);
    list_print(head);
}