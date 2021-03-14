#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED

#include <stdlib.h>

// Домашка-максимум.
// Реализовать всё вот это в виде библиотеки.
// Заголовочный файл -- этот.

typedef struct list_t {
    int data; // полезная нагрузка
    struct list_t * next; // метаданные
} list_t;


// Создание списка из одного элемента
// Сложность -- O(1)
list_t * list_create(int data);

// Вставка нового элемента в начало списка.
// Сложность -- O(1)
// Поскольку голова списка в процессе меняется, мы возвращаем
// указатель на новую голову
list_t * list_prepend(list_t * head, int data); // O(1)

// Добавляет новый элемент в конец списка.
// Сложность -- O(n)
list_t * list_append(list_t * head, int data); // O(n)

// Вставляет элемент по индексу index.
// Сложность -- O(index)
list_t * list_insert_i(list_t * head, int index, int data); // O(index)

// Вставляет новый элемент сразу после previous
// Новый элемент -- list_getnth(head, index);
// Было: []->[previous]->[X]->[]->[]->...
// Хотим: []->[previous]->[N]->[X]->[]->[]->...
// N = prepend(previous->next, ...)
// []->[previous]->[X]->[]->[]->...
//                  ^
//                  |
//                 [N]
// previous->next = N;
// []->[previous]->[N]->[X]->[]->[]->...
list_t * list_insert_after(list_t * previous, int data); // O(1)


// Функция удаления из списка.
// Первая удаляет по индексу за O(n)
list_t * list_delete_i(list_t * head, int index); //O(index)
// Вторая удаляет по указателю на предка
// Было: []->[previous]->[D]->[X]->[]->...
// Хотим: []->[previous]->[X]->[]->...
// list_t * to_delete = previous->next; // D
// previous->next = to_delete->next // X
// []->[previous]->[X]->[]->...
//                  ^
//                  |
//                 [D]
// Ну и теперь D можно удалить, никто не пострадает.
// free(D);
list_t * list_delete_after(list_t * previous, int after); // O(1)

// Функция доступа к элементу по индексу
// Возвращает указатель на n-тый элемент
list_t * list_getnth(list_t * head, int n); // O(n)

// Функция расчёта длины
size_t list_length(list_t * head); // O(n)
// Полное удаление всего списка
void list_destroy(list_t * head); // O(n)
// Отладочный вывод для списков
void list_print(list_t * head); // O(n)

typedef int Processor(list_t *, void * metadata);
// Применяет последовательно func ко всем элементам
void list_foreach(list_t * head, Processor func, void * metadata); 
//func(L[0], metadata)
//func(L[1], metadata)
//func(L[2], metadata)
//...

typedef int Transformer(int);
// Формирует список из f(list[0])-> f(list[1]) -> ...
list_t * list_map(list_t * head, Transformer func);
// Пусть был список L=1->2->3->4->5->6
// list_map(L, x->x*x) 
// 1->4->9->16->25->36

// Задача со звёздочкой.
// Сделать list_map через list_foreach.
//


#endif // SLIST_H_INCLUDED
