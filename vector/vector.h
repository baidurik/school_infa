#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED
// #include <stddef.h>

struct vector_t { // std::vector<int>
    int * data; // Указатель на данные. Его мы будем маллочить.
    size_t capacity; // Размер замаллоченного массива под данные
    size_t length; // Количество реально существующих элементов.
};


typedef int Processor(int, void * metadata, size_t metadata_size);

struct vector_t * vector_create(size_t capacity);
struct vector_t * vector_from_array(int * array, size_t n);
struct vector_t * vector_clone(struct vector_t * v);

void vector_destroy(struct vector_t * v);

// Доступ с проверкой границ.
int vector_getnth(struct vector_t *v, int n);
int * vector_getnthptr(struct vector_t *v, int n);

void vector_append(struct vector_t * v, int x); // Дописываем x в конец вектора
void vector_insert(struct vector_t * v, int i, int x); // Записываем x в позицию i, хвост сдвигаем на шаг.
void vector_delete(struct vector_t * v, int i); // Удаляем i-тый элемент, хвост сдвигаем
void vector_extend(struct vector_t * v1, struct vector_t * v2);
int vector_resize(struct vector_t * v, size_t new_size);
void vector_clear(struct vector_t *v);

int vector_process(struct vector_t *v, Processor * func, void * metadata, size_t metadata_size);
// ***
// Применяет func ко всем элементам вектора.
// Эту функцию нужно будет не только реализовать, но и применить.
// Пример применения -- рассчитать за один вызов vector_process() среднее и дисперсию элементов вектора.

void vector_sort(struct vector_t *v);
int * vector_bsearch(struct vector_t * v, int x); // Бинарный поиск


#endif // VECTOR_H_INCLUDED
