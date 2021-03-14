#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

uint8_t get_bit(uint8_t * data, int pointer)
{
    // printf("%u\n", data[pointer / 8] & (1 << (7 - pointer % 8)));
    return (data[pointer / 8] & (1 << (7 - pointer % 8))) > 0;
}

void write(uint8_t * to, int out_pointer, uint8_t state, uint8_t counter)
{
    to[out_pointer] = 0;
    to[out_pointer] |= counter;
    to[out_pointer] |= (state << 7);
}

int rle_encode(uint8_t * from, size_t from_length, uint8_t * to, size_t to_length)
{
    uint8_t curr_state = 2;
    int out_pointer = 0;
    uint8_t counter = 0;
    for(size_t pointer = 0; pointer < from_length * 8; pointer++)
    {
        if(curr_state == 2)
        {
            curr_state = get_bit(from, pointer);
            counter ++;
        }
        else 
        {
            // printf("%d", get_bit(from, pointer));
            if(get_bit(from, pointer) == curr_state)
            {
                counter ++;
                if(counter == 127)
                {
                    // printf("animeanime");
                    write(to, out_pointer++, curr_state, counter);
                    counter = 0;
                    curr_state = 2;
                }
            }
            else 
            {
                // printf("anime");
                write(to, out_pointer++, curr_state, counter);
                curr_state = get_bit(from, pointer);
                counter = 1;
            }
        }
        if(out_pointer >= to_length) return out_pointer;
    }
    write(to, out_pointer++, curr_state, counter);
    return out_pointer;
}

void write_bit(uint8_t * to, int pointer, uint8_t state)
{
    uint8_t mask = 255 - (1 << (7 - pointer % 8));
    to[pointer / 8] &= mask;
    to[pointer / 8] |= (state << (7 - pointer % 8));
}

int rle_decode(uint8_t * from, size_t from_length, uint8_t * to, size_t to_length)
{
    int pointer = 0;
    for(int i = 0; i < from_length; i++)
    {
        uint8_t state = (from[i] & 128) > 0;
        uint8_t size = from[i] & 127;
        for(int j = 0; j < size; j++)
        {
            write_bit(to, pointer++, state);
            if(pointer >= to_length * 8) return to_length;
        }
    }
    return pointer / 8;
}