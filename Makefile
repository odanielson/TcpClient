CC = gcc
CFLAGS = -Wall -Werror -O2

TARGET = TcpClient

all: $(TARGET).a example

$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) $(TARGET).c -c -o $(TARGET).o

$(TARGET).a: $(TARGET).o
	$(AR) rcs lib$(TARGET).a $(TARGET).o

example: $(TARGET).a example.c
	$(CC) example.c lib$(TARGET).a -o example

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *~
