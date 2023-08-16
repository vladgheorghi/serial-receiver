#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

uint8_t hex_to_nibble(uint8_t hex);

uint8_t parse_uint8(uint8_t *hex, uint32_t *index);

uint16_t parse_uint16(uint8_t *hex, uint32_t *index);

uint32_t parse_uint32(uint8_t *hex, uint32_t *index);

uint64_t parse_uint64(uint8_t *hex, uint32_t *index);

int8_t parse_int8(uint8_t *hex, uint32_t *index);

int16_t parse_int16(uint8_t *hex, uint32_t *index);

int32_t parse_int32(uint8_t *hex, uint32_t *index);

int64_t parse_int64(uint8_t *hex, uint32_t *index);

float parse_float(uint8_t *payload, uint32_t *index);

double parse_double(uint8_t *payload, uint32_t *index);

void parse_string(char *dest, uint8_t *hex, uint32_t *index, int len);

void parse_data(void *data, uint8_t *payload, uint32_t *index, data_type type, size_t string_size);
