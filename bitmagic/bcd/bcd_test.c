#include "bcd_numbers.c"
int main()
{
    bcdnum_t bcd1 = bcd_from_int(194284);
    // for(int i = 0; i < 4; i++) printf("%d \n", bcd.digits[i]);
    bcd_print(bcd1);
    // printf("anime");
    bcdnum_t bcd2 = bcd_from_int(22905);
    bcd_print(bcd2);
    bcdnum_t bcd3 = bcd_add(bcd1, bcd2);
    // for(int i = 0; i < 4; i++) printf("%u ", bcd3.digits[i]);
    bcd_print(bcd3);
    bcdnum_t bcd4 = bcd_from_int(-122);
    bcdnum_t bcd5 = bcd_from_int(69);
    bcd_print(bcd4);
    bcd_print(bcd_add(bcd4, bcd5));
    bcd_print(bcd_add(bcd5, bcd4));
    printf("\n\n");
    bcd1 = bcd_from_int(223);
    bcd2 = bcd_from_int(23);
    bcd3 = bcd_mul(bcd1, bcd2);
    bcd_print(bcd3);

    bcd1 = bcd_from_int(220);
    bcd2 = bcd_from_int(11);
    bcd3 = bcd_div(bcd1, bcd2);
    bcd_print(bcd3);
}
