#include <stdio.h>
#include "fractions.h"
#include "fractions.c"

void print_fraction(struct fraction_t a)
{
    printf("%d / %d\n", a.numerator, a.denominator);
}



int main()
{
    struct fraction_t a;
    struct fraction_t b;
    a.numerator = 256;
    a.denominator = 128;
    print_fraction(a);
    a = fraction_simplify(a);
    print_fraction(a);
    b.numerator = 1;
    b.denominator = 3;
    print_fraction(b);
    printf("/===================================/\n");
    print_fraction(fraction_add(a, b));
    print_fraction(fraction_mul(a, b));
    print_fraction(fraction_sub(a, b));
    print_fraction(fraction_div(a, b));
    printf("/===================================/\n");
    a.numerator = -1;
    a.denominator = 2;
    b.numerator = -2;
    b.denominator = 3;
    print_fraction(a);
    print_fraction(b);
    print_fraction(fraction_add(a, b));
    print_fraction(fraction_mul(a, b));
    print_fraction(fraction_sub(a, b));
    print_fraction(fraction_div(a, b));
    printf("/===================================/\n");
    a.numerator = 9;
    a.denominator = 14;
    b.numerator = -7;
    b.denominator = 3;
    print_fraction(fraction_div(a, b));
}