#include <stdio.h>
#include "vector.h"
#include "vector.c"

struct metadata_for_mean
{
    int count;
    int sum;
};

struct metadata_for_variance
{
    double mean;
    double curr_var;
};


int get_sum_and_count(int el, void * metadata, size_t metadata_size)
{
    struct metadata_for_mean * typed_metadata = (struct metadata_for_mean *) metadata;
    typed_metadata->count += 1;
    typed_metadata->sum += el;
}

int get_variance(int el, void * metadata, size_t metadata_size)
{
    struct metadata_for_variance * typed_metadata = (struct metadata_for_variance *) metadata;
    typed_metadata->curr_var += (el - typed_metadata->mean) * (el - typed_metadata->mean);
}

int main()
{
    struct metadata_for_mean * mdata = malloc(sizeof(struct metadata_for_mean));
    mdata->count = 0;
    mdata->sum = 0;
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct vector_t * vec = vector_from_array(arr, 10);
    vector_process(vec, get_sum_and_count, (void *)mdata, sizeof(struct metadata_for_mean));
    printf("%d %d ", mdata->count, mdata->sum);
    double mean = mdata->sum / (double)mdata->count;
    struct metadata_for_variance * mdata2 = malloc(sizeof(struct metadata_for_variance));
    mdata2->mean = mean;
    mdata2->curr_var = 0;
    vector_process(vec, get_variance, (void*)mdata2, sizeof(mdata2));
    printf("%f", mdata2->curr_var);
}