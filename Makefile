CC = gcc
CFLAGS = -Wall -O2

TARGET = TcpSocket

all: $(TARGET).a test

$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) $(TARGET).c -c -o $(TARGET).o

$(TARGET).a: $(TARGET).o
	$(AR) rcs lib$(TARGET).a $(TARGET).o

test: $(TARGET).a test.c
	$(CC) test.c lib$(TARGET).a -o test

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *~
