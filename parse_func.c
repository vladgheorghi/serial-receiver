/* source file for all parse functions */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "serial_receiver.h"
#include "parse_func.h"

void parse_data(void *data, uint8_t *payload, uint32_t *index, data_type type, size_t string_size) {

    switch (type) {
        case UINT8:
            *(uint8_t *)data = parse_uint8(payload, index);
            break;
        case UINT16:
            *(uint16_t *)data = parse_uint16(payload, index);
            break;
        case UINT32:
            *(uint32_t *)data = parse_uint32(payload, index);
            break;
        case UINT64:
            *(uint64_t *)data = parse_uint64(payload, index);
            break;
        case INT8:
            *(int8_t *)data = parse_int8(payload, index);
            break;
        case INT16:
            *(int16_t *)data = parse_int16(payload, index);
            break;
        case INT32:
            *(int32_t *)data = parse_int32(payload, index);
            break;
        case INT64:
            *(int64_t *)data = parse_int64(payload, index);
            break;
        case FLOAT:
            *(float *)data = parse_float(payload, index);
            break;
        case DOUBLE:
            *(double *)data = parse_double(payload, index);
            break;
        case STRING:
            parse_string(data, payload, index, string_size);
            break;
        default:
            printf("Invalid data type.\n");
            break;
    }
}

uint8_t parse_uint8(uint8_t *hex, uint32_t *index) {

    uint8_t val = 0;

    for (long unsigned int i = 0; i < 2 * sizeof(uint8_t); i++) {

        uint8_t byte = hex_to_nibble(hex[*index]);
        (*index)++;

        val = (val << 4) | (byte & 0xF);
    }

    return val;
}

uint16_t parse_uint16(uint8_t *hex, uint32_t *index) {

    uint16_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < sizeof(uint16_t); i++) {

        uint8_t byte = parse_uint8(hex, index); 

        val = val | (byte << shift);
        shift += 8;
    }

    return val;
}

uint32_t parse_uint32(uint8_t *hex, uint32_t *index) {

    uint32_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < sizeof(uint32_t); i++) {

        uint8_t byte = parse_uint8(hex, index);

        val = val | (byte << shift);
        shift += 8;
    }

    return val;
}

uint64_t parse_uint64(uint8_t *hex, uint32_t *index) {

    uint64_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < sizeof(uint64_t); i++) {

        uint8_t byte = parse_uint8(hex, index);

        val = val | byte << shift;
        shift += 8;
    }

    return val;
}

int8_t parse_int8(uint8_t *hex, uint32_t *index) {

    int8_t val = 0;

    for (long unsigned int i = 0; i < 2 * sizeof(int8_t); i++) {

        uint8_t byte = hex_to_nibble(hex[*index]);
        (*index)++;

        val = (val << 4) | (byte & 0xF);
    }

    return val;
}

int16_t parse_int16(uint8_t *hex, uint32_t *index) {

    int16_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < 2 * sizeof(int16_t); i++) {

        uint8_t byte = parse_int8(hex, index);

        val = val | (byte << shift);
        shift += 8;
    }

    return val;
}

int32_t parse_int32(uint8_t *hex, uint32_t *index) {

    int32_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < 2 * sizeof(int32_t); i++) {

        uint8_t byte = parse_int8(hex, index);

        val = val | (byte << shift);
        shift += 8;
    }

    return val;
}

int64_t parse_int64(uint8_t *hex, uint32_t *index) {

    int64_t val = 0;
    int shift = 0;

    for (long unsigned int i = 0; i < 2 * sizeof(int64_t); i++) {

        uint8_t byte = parse_int8(hex, index);

        val = val | (byte << shift);
        shift += 8;
    }

    return val;
}

float parse_float(uint8_t *payload, uint32_t *index) {
    float result = 0.0;

    uint32_t val = parse_uint32(payload, index);

    result = *((float *)&val);

    return result;
}

double parse_double(uint8_t *payload, uint32_t *index) {
    double result = 0.0;

    uint64_t val = parse_uint64(payload, index);

    result = *((double *)&val);

    return result;
}

void parse_string(char *dest, uint8_t *hex, uint32_t *index, int len) {

    for (int i = 0; i < len; i++) {
        dest[i] = parse_uint8(hex, index);
    }
}

// Convert a hex character to a nibble
uint8_t hex_to_nibble(uint8_t hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'a' && hex <='f') {
        return hex - 'a' + 10;
    } else if (hex >= 'A' && hex <='F') {
        return hex - 'A' + 10;
    }

    return 0;
}