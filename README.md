# Serial Receiver

### Description

Receive any struct through serial with this simple C program.

### How to

1. Inside `serial_receiver.h`
   1. Set up serial port at: `#define SERIAL_PORT "your-port-here"` *(e.g /dev/ttyS0 or COM ports on Windows)*
   2. Set up the maximum packet size in __bytes__ at: `#define MAX_PAYLOAD_SIZE 10000`
   3. Set up how many packets to ignore when you first open the program at: `#define PACKETS_TO_IGNORE 4` 
   
2. Inside `serial_receiver.c`
   1. Set up your struct with the fields you need
      * `uint8_t`, `uint16_t` etc. data types are recommended over `int`, `long` etc.
      * make sure the data structure you are receiving is identical and has the same size with the data structure inside the program
      * static allocation is recommended
   2. Inside the `parse_struct()` function, call `parse_data()` functions for each field (e.g. for an `uint32_t` field you would call `parse_data(&package->field, payload, &index, UINT32, 0);`)
      * the order of the fields must match the order of the called functions

3. Inside a terminal
   * `cd` to the cloned folder
   * Type `make`
   * Type `./serial_receiver`

4. Now you should be receiving the structure from the selected port. Try printing each field inside `main()`

### More details

   * The format in which data is expected to be received is: `<STX> <payload> <ETX>`, where `<payload>` is a string of hexadecimals (1 byte = 2 hex chars). For reference, check a transmitter example program for **Arduino** Uno inside `arduino_exampleTX/transmitter.cpp`.
   * Conversion from hex string to each data type can be found inside `parse_func.c` source file.

## Please reach out if you have any questions. Also please commit your improvements :\)