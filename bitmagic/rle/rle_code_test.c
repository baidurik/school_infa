#include "rle_code.h"

int main()
{
    uint32_t * num = malloc(sizeof(uint32_t));
    *num = UINT32_MAX;
    uint8_t * to = malloc(256);
    printf("%d\n", rle_encode((uint8_t * )num, 4, to, 256));
    printf("%u\n", to[0]);      // 160 = 10100000 - единичка 32 раза
    *num = 0xAAAAAAAA;          // 0b101010 ... 1010
    printf("%d\n", rle_encode((uint8_t * )num, 4, to, 256));
    for(int i = 0; i < 32; i++) printf("%u ", to[i]);   // 129 - 0b10000001, 1 - 0b00000001
    printf("\n");
    *num = 0;
    printf("%d\n", rle_decode(to, 32, (uint8_t*)num, 4));
    printf("%u", *num);         // Переводит обратно исправно.
}