#include "bcd_numbers.h"

uint8_t bcd_read_digit(bcdnum_t a, int pos)
{
    if(pos % 2) return a.digits[pos / 2] >> 4;
    else return a.digits[pos / 2] & 15;
}

bcdnum_t bcd_from_int(int a)
{
    bcdnum_t num;
    if(a < 0)
    {
        num.sign = 1;
        a *= -1;
    }
    else num.sign = 0;
    for(int i = 0; i < 4; i++) num.digits[i] = 0;
    int pos = 0;
    while(a > 0)
    {
        if(pos % 2) num.digits[pos / 2] |= (a % 10) << 4;
        else num.digits[pos / 2] |= (a % 10);
        a /= 10;
        pos ++;
    }
    return num;
}

void bcd_print(bcdnum_t a)
{
    uint8_t started = 0;
    if(a.sign == 1) printf("-");
    for(int pos = 7; pos >= 0; pos --)
    {
        uint8_t digit = bcd_read_digit(a, pos);
        if(digit == 0 && started == 0) continue;
        if(digit != 0) started = 1;
        printf("%u", digit);
    }
    printf("\n");
}

int bcd_cmp_module(bcdnum_t a, bcdnum_t b)
{
    for(int pos = 7; pos >= 0; pos --)
    {
        uint8_t d1 = bcd_read_digit(a, pos);
        uint8_t d2 = bcd_read_digit(b, pos);
        if(d1 > d2) return 1;
        else if(d1 < d2) return -1;
    }
    return 0;
}

bcdnum_t bcd_add(bcdnum_t a, bcdnum_t b)
{
    bcdnum_t result;
    for(int i = 0; i < 4; i++) result.digits[i] = 0;
    uint8_t transfer = 0;
    for(int pos = 0; pos < 8; pos++)
    {
        uint8_t d1 = bcd_read_digit(a, pos);
        uint8_t d2 = bcd_read_digit(b, pos);
        // printf("%u %u %u\n", d1, d2, transfer);
        uint8_t d3;
        if(a.sign == b.sign)
        {
            if(10 - d1 - transfer <= d2)
            {
                d3 = d2 + d1 + transfer - 10;
                transfer = 1;
            }
            else 
            {
                d3 = d2 + d1 + transfer;
                transfer = 0;
            }
        }
        else if(bcd_cmp_module(a, b) == 1)
        {
            if(d2 + transfer > d1)
            {
                d3 = d1 + 10 - d2 - transfer;
                transfer = 1;
            }
            else 
            {
                d3 = d1 - d2 - transfer;
                transfer = 0;
            }
        }
        else
        {
            if(d1 + transfer > d2)
            {
                d3 = d2 + 10 - d1 - transfer;
                transfer = 1;
            }
            else 
            {
                d3 = d2 - d1 - transfer;
                transfer = 0;
            }
        }
        // printf("%u\n", d3);
        if(pos % 2) result.digits[pos / 2] |= d3 << 4;
        else result.digits[pos / 2] |= d3;
    }
    if(a.sign == b.sign) result.sign = a.sign;
    else if(bcd_cmp_module(a, b) == 1) result.sign = a.sign;
    else result.sign = b.sign;
    return result;
}

bcdnum_t bcd_sub(bcdnum_t a, bcdnum_t b)
{
    b.sign = (b.sign + 1) % 2;
    return bcd_add(a, b);
}

bcdnum_t bcd_mul_on_digit(bcdnum_t a, uint8_t digit)
{
    bcdnum_t result;
    for(int i = 0; i < 4; i++) result.digits[i] = 0;
    result.sign = 0;
    for(int pos = 0; pos < 8; pos++)
    {
        uint8_t ml = bcd_read_digit(a, pos) * digit;
        bcdnum_t res;
        for(int i = 0; i < 4; i++) res.digits[i] = 0;
        res.sign = 0;
        if(pos % 2) 
        {
            res.digits[pos / 2] |= (ml % 10) << 4;
            // printf("anime %d\n", ml);
            if(pos < 7) res.digits[pos / 2 + 1] |= (ml / 10);
        }
        else 
        {
            res.digits[pos / 2] |= (ml % 10);
            res.digits[pos / 2] |= (ml / 10) << 4;
        }
        // printf("%u\n", res.digits[pos/2]);
        result = bcd_add(result, res);
    }
    return result;
}

bcdnum_t bcd_movleft(bcdnum_t a, int how)
{
    if(how == 0) return a;
    for(int pos=7; pos >= how; pos--)
    {
        if(pos % 2)
        {
            a.digits[pos/2] &= 15;
            a.digits[pos/2] |= bcd_read_digit(a, pos-how) << 4;
        } 
        else 
        {
            a.digits[pos/2] &= 240;
            a.digits[pos/2] |= bcd_read_digit(a, pos-how);
        }
    }
    for(int pos = how-1; pos >= 0; pos --)
    {
        if(pos % 2) a.digits[pos/2] &= 15;
        else a.digits[pos/2] &= 240;
    }
    return a;
}

bcdnum_t bcd_mul(bcdnum_t a, bcdnum_t b)
{
    bcdnum_t result;
    for(int i = 0; i < 4; i++) result.digits[i] = 0;
    if(a.sign == b.sign) result.sign = 0;
    else result.sign = 1;
    for(int pos = 0; pos < 7; pos ++)
    {   
        bcdnum_t on_digit = bcd_mul_on_digit(a, bcd_read_digit(b, pos));
        // bcd_print(on_digit);
        if(bcd_cmp_module(on_digit, bcd_from_int(0)) != 0)
        {
            on_digit = bcd_movleft(on_digit, pos);
            result = bcd_add(result, on_digit);
        }
    }
    return result;
}

bcdnum_t bcd_movright(bcdnum_t a, int how)
{
    if(how == 0) return a;
    for(int pos = 0; pos <= 7-how; pos ++)
    {
        if(pos % 2)
        {
            a.digits[pos / 2] &= 15;
            a.digits[pos / 2] |= bcd_read_digit(a, pos+how) << 4;
        }
        else 
        {
            a.digits[pos / 2] &= 240;
            a.digits[pos / 2] |= bcd_read_digit(a, pos+how);
        }
    }
    for(int pos = 7-how+1; pos < 8; pos++)
    {
        if(pos % 2) a.digits[pos / 2] &= 15;
        else a.digits[pos / 2] &= 240;
    }
}

bcdnum_t bcd_div(bcdnum_t a, bcdnum_t b)
{
    uint8_t new_sign;
    if(a.sign == b.sign) new_sign = 0;
    else new_sign = 1;
    a.sign = 0;
    b.sign = 0;
    bcdnum_t counter = bcd_from_int(0);
    while(bcd_cmp_module(a, b) >= 0)
    {
        a = bcd_sub(a, b);
        counter = bcd_add(counter, bcd_from_int(1));
    }
    return counter;
}

bcdnum_t bcd_neg(bcdnum_t a)
{
    a.sign = (a.sign + 1) % 2;
    return a;
}

int bcd_cmp(bcdnum_t a, bcdnum_t b)
{
    if(a.sign == 0 && b.sign == 1) return 1;
    else if(a.sign == 1 && b.sign == 0) return -1;
    else if(a.sign == 1 && b.sign == 1) return bcd_cmp_module(b, a);
    else return bcd_cmp_module(a, b);
}