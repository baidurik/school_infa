#include "rle_code.h"
#include <string.h>

int main(int argc, char * argv[])
{
    if(argc >= 3)
    {
        if(strcmp("encode", argv[1]) == 0)
        {
            FILE * fin = fopen(argv[2], "rb");
            uint8_t * input = malloc(100000);
            size_t count = fread(input, 1, 100000, fin);
            uint8_t * output = malloc(800000);
            // for(int i = 0; i < count; i++) printf("%u", input[i]);
            size_t enc_count = rle_encode(input, count, output, 800000);
            // printf("\n%d\n", enc_count);
            strcat(argv[2], ".rle");
            FILE * fout = fopen(argv[2], "wb");
            // for(int i = 0; i < enc_count; i++) printf("%u", output[i]);
            fwrite(output, 1, enc_count, fout);
        }
        else if(strcmp("decode", argv[1]) == 0)
        {
            FILE * fin = fopen(argv[2], "rb");
            uint8_t * input = malloc(100000);
            size_t count = fread(input, 1, 100000, fin);
            uint8_t * output = malloc(800000);
            size_t dec_count = rle_decode(input, count, output, 800000);
            // printf("%d", dec_count);
            strcat(argv[2], ".decoded");
            FILE * fout = fopen(argv[2], "wb");
            fwrite(output, 1, dec_count, fout);
        }
        else 
        {
            printf("Usage: rle_file <command> <filename>");
        }
    }
    else 
    {
        printf("Usage: rle_file <command> <filename>");
    }
}