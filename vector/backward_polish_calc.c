#include <stdio.h>
#include <stdlib.h>

struct stack
{
    int * data;
    size_t size;
    size_t capacity;
};

struct stack * create(size_t size)
{
    struct stack * st = malloc(sizeof(struct stack));
    st->size = size;
    st->capacity = size;
    st->data = malloc(size * sizeof(int));
    return st;
}

void push_back(struct stack * st, int x)
{
    if(st->size == st->capacity)
    {
        if(st->capacity == 0) st->capacity ++;
        else
        {
            st->capacity *= 2;
            st->data = realloc(st->data, st->capacity * sizeof(int));
            if(st->data == NULL) exit(3);
        }
    }
    st->data[st->size++] = x;
}

int back(struct stack * st)
{
    if(st->size > 0) return st->data[st->size-1];
}

int pop_back(struct stack * st)
{
    int el = back(st);
    if(st->size > 0) st->size --;
    return el;
}

int * back_ptr(struct stack * st)
{
    if(st->size > 0) return st->data + st->size - 1;
}

int main()
{
    struct stack * st = create(0);
    while(1)
    {
        int c = getchar();
        if(c == '\n')
        {
            if(st->size == 1) printf("%d", st->data[0]);
            else printf("INVALID EXPRESSION");
            break;
        }
        else if(c == '+')
        {
            if(st->size > 1)
            {
                int el = pop_back(st);
                *(back_ptr(st)) += el;
            }
            else
            {
                printf("INVALID EXPRESSION");
                break;
            }
        }
        else if(c == '*')
        {
            if(st->size > 1)
            {
                int el = pop_back(st);
                *(back_ptr(st)) *= el;
            }
            else
            {
                printf("INVALID EXPRESSION");
                break;
            }
        }
        else if(c == '-')
        {
            if(st->size > 1)
            {
                int el = pop_back(st);
                *(back_ptr(st)) -= el;
            }
            else
            {
                printf("INVALID EXPRESSION");
                break;
            }
        }
        else if(c == '/')
        {
            if(st->size > 1)
            {
                int el = pop_back(st);
                *(back_ptr(st)) /= el;
            }
            else
            {
                printf("INVALID EXPRESSION");
                break;
            }
        }
        else if(c == ' ') continue;
        else 
        {
            ungetc(c, stdin);
            int x;
            scanf("%d", &x);
            push_back(st, x);
        }
    }
}