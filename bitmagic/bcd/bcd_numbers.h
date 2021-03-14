#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

typedef struct bcdnum_t 
{
    uint8_t digits[4];
    uint8_t sign;
} bcdnum_t;

bcdnum_t bcd_from_int(int a);

bcdnum_t bcd_add(bcdnum_t a, bcdnum_t b);
bcdnum_t bcd_sub(bcdnum_t a, bcdnum_t b);
bcdnum_t bcd_mul(bcdnum_t a, bcdnum_t b);
bcdnum_t bcd_div(bcdnum_t a, bcdnum_t b);
bcdnum_t bcd_neg(bcdnum_t a);

uint8_t bcd_read_digit(bcdnum_t a, int pos);

int bcd_cmp_module(bcdnum_t a, bcdnum_t b);
int bcd_cmp(bcdnum_t a, bcdnum_t b);

void bcd_print(bcdnum_t a);