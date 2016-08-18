CFLAGS = -O3 -g -Wall -march=native

CC = gcc

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

OBJS = ggets.o ll.o tac.o

SRCS = ggets.c ll.c tac.c

all: tac

tac: $(OBJS)
	$(CC) $(OBJS) -o tac

clean:
	rm *.o tac
