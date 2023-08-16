#ifndef READ_DATA_H_
#define READ_DATA_H_
#endif

#include <stdint.h>
#include <stdio.h>

int read_frame(int fd, uint8_t *payload, unsigned int len);