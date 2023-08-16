CFLAGS= -Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-functi
CC=gcc

compile:
	$(CC) $(CFLAGS) *.c -o serial_receiver

clean:
	rm -f *.o serial_receiver


