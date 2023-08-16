/*
    gheorghiuvlad21@gmail.com
    Vlad Gheorghiu, 2023

    This program is meant to be used on the receiving end of the serial
    communication. It reads the serial port and parses the data into a struct.

    Feel free to modify this program to fit your needs.
    If you want to contribute to this project, you can do so by pushing your
    changes in the GitHub repository.
*/

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
#include "read_data.h"

/*
   consider:
    1. the size of each field should match the size of the corresponding field
    in the struct from the transmitting end

    2. consider using uint8_t, uint16_t etc. instead of int, long etc.

    3. the number of fields should match the number of fields in the struct

    4. use static allocation for the struct and for the transmitting hardware
*/

// TODO: modify this struct for your needs (this is an example)
typedef struct your_struct {
    uint8_t x;
    uint16_t y;
    uint32_t z;
    uint64_t w;
    char list[30];
    float num;
    float num2;
    char list2[100];
    uint32_t a[10][10];
} your_struct;


// use this function to parse the payload into the struct fields
// make sure to match the order of the fields
void parse_struct(your_struct *package, uint8_t *payload) {
    uint32_t index = 0;

    // TODO: parse the payload into the struct fields

    parse_data(&package->x, payload, &index, UINT8, 0);
    parse_data(&package->y, payload, &index, UINT16, 0);
    parse_data(&package->z, payload, &index, UINT32, 0);
    parse_data(&package->w, payload, &index, UINT64, 0);

    parse_data(package->list, payload, &index, STRING, 30);

    parse_data(&package->num, payload, &index, FLOAT, 0);
    parse_data(&package->num2, payload, &index, FLOAT, 0);

    parse_data(package->list2, payload, &index, STRING, 100);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            parse_data(&package->a[i][j], payload, &index, UINT32, 0);
        }
    }
}

int main() {
    int fd, len, wait_to_calibrate = 0;
    struct termios options;
    memset(&options, 0, sizeof(options));

    fd = open(SERIAL_PORT, O_RDWR | O_NDELAY | O_NOCTTY);
    if (fd < 0) {
        perror("Error opening serial port.\n");
        return -1;
    }

    // set up serial port
    options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;
    options.c_iflag = 0;
    options.c_oflag = 0;
    options.c_lflag = 0;  

    // apply settings
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    your_struct test;

    uint8_t payload[2 * sizeof(your_struct)];

    while (1) {
        len = read_frame(fd, payload, sizeof(payload));

        if (len == 0)
            continue;

        if (len < 0) {
            printf("Error reading from serial port.\n");
            continue;
        }

        if (len > 0 && wait_to_calibrate < PACKETS_TO_IGNORE) {
            wait_to_calibrate++;
            memset(payload, 0, 2 * sizeof(your_struct));
            continue;
        }

        parse_struct(&test, payload);

        // your_struct is parsed and ready to be used (print as example)
        printf("len = %d\n", len);

        printf("x: %d\n", test.x);
        printf("y: %d\n", test.y);
        printf("z: %d\n", test.z);
        printf("w: %ld\n", test.w);
        printf("list: %s\n", test.list);
        printf("num: %f\n", test.num);
        printf("num2: %f\n", test.num2);
        printf("list2: %s\n", test.list2);
        printf("a: \n");
        for (int i = 0; i < 10; i++) {
            printf("\t");
            for (int j = 0; j < 10; j++) {
                printf("%d ", test.a[i][j]);
            }
            printf("\n");
        }

        memset(payload, 0, 2 * sizeof(your_struct));

        // TODO: entry point to your program

    }

    return 0;
}