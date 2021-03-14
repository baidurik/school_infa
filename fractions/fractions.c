#include "fractions.h"
#include <stdlib.h>

struct fraction_t fraction_simplify(struct fraction_t a)
{
    int d = 2;
    int num = a.numerator;
    if(num == 0)
    {
        a.denominator = 1;
        return a;
    }
    a.numerator = abs(a.numerator);
    while(d * d <= a.numerator)
    {
        while(a.numerator % d == 0 && a.denominator % d == 0)
        {
            a.numerator /= d;
            a.denominator /= d;
        }
        d++;
    }
    if(a.denominator % a.numerator == 0)
    {
        a.denominator /= a.numerator;
        a.numerator = 1;
    }
    if(num < 0) a.numerator *= -1;
    return a;
}

struct fraction_t fraction_mul(struct fraction_t a, struct fraction_t b)
{
    a.numerator *= b.numerator;
    a.denominator *= b.denominator;
    return fraction_simplify(a);
}

struct fraction_t fraction_div(struct fraction_t a, struct fraction_t b)
{
    if(b.numerator < 0)
    {
        b.numerator *= -1;
        a.numerator *= -1;
    }
    a.numerator *= b.denominator;
    a.denominator *= b.numerator;
    return fraction_simplify(a);
}

struct fraction_t fraction_add(struct fraction_t a, struct fraction_t b)
{
    a.numerator *= b.denominator;
    b.numerator *= a.denominator;
    a.denominator *= b.denominator;
    a.numerator += b.numerator;
    return fraction_simplify(a);
}

struct fraction_t fraction_sub(struct fraction_t a, struct fraction_t b)
{
    b.numerator *= -1;
    return fraction_add(a, b);
}

int fraction_cmp(struct fraction_t a, struct fraction_t b) // Если больше нуля, то >, если ноль, то =, если меньше нуля, то <
{
    a = fraction_sub(a, b);
    return a.numerator;
}