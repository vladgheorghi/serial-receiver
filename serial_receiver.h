#ifndef SERIAL_RECEIVER_H_
#define SERIAL_RECEIVER_H_
#endif

#include <stdint.h>
#include <stdio.h>

/* serial packets have the format:
    STX <payload> ETX
*/
#define STX (char)2
#define ETX (char)3

/* modify with an maximum estimated payload size (in bytes) */
#define MAX_PAYLOAD_SIZE 10000

// TODO: enter your serial port (e.g. /dev/ttyS0)
#define SERIAL_PORT "your-port-here"

#define PACKETS_TO_IGNORE 4

/* data types that you can use in your struct */
typedef enum data_type {
    UINT8,
    UINT16,
    UINT32,
    UINT64,
    INT8,
    INT16,
    INT32,
    INT64,
    FLOAT,
    DOUBLE,
    STRING,
} data_type;