#include <Arduino.h>

typedef struct your_struct {
    uint8_t x;
    uint16_t y;
    uint32_t z;
    uint64_t w;
    char list[30];
    float num;
    float num2;
    uint32_t a[10][10];
} your_struct;