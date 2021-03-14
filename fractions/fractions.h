#ifndef FRACTIONS_H_INCLUDED
#define FRACTIONS_H_INCLUDED

struct fraction_t {
    int numerator;
    unsigned int denominator;
};

//typedef struct fraction_t fraction_t;

struct fraction_t fraction_add(struct fraction_t a, struct fraction_t b);
struct fraction_t fraction_mul(struct fraction_t a, struct fraction_t b);
struct fraction_t fraction_sub(struct fraction_t a, struct fraction_t b);
struct fraction_t fraction_div(struct fraction_t a, struct fraction_t b);
int fraction_cmp(struct fraction_t a, struct fraction_t b);

struct fraction_t fraction_simplify(struct fraction_t a);

#endif // FRACTIONS_H_INCLUDED
