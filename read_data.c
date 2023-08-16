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

int read_frame(int fd, uint8_t *payload, unsigned int len) {
    long unsigned int pos = 0;
    int stx = -1, etx = -1;
    uint8_t buf[MAX_PAYLOAD_SIZE];

    while (etx == -1) {
        int n = read(fd, buf + pos, sizeof(buf) - pos);

        if (n < 0) {
            return n;
        }

        for (long unsigned int i = pos; i < (pos + n); i++) {
            if (stx < 0) {
                if (buf[i] == STX) {
                    stx = i;
                }
            } else if (etx < 0) {
                if (buf[i] == ETX) {
                    etx = i;
                    break;
                }
            }
        }

        if (etx >= 0 && stx >= 0) {
            break;
        }

        pos += n;

        if (pos >= sizeof(buf)) {
            pos = 0;
            memset(buf, 0, sizeof(buf));
        }
    }

    if (len < (unsigned int)(etx - stx - 1)) {
        printf("Payload too large.\n");
        return -2;
    }

    memcpy(payload, buf + stx + 1, etx - stx - 1);

    return etx - stx - 1;
}