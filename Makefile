CC = clang++
CFLAGS = -g -Wall

PROG = assembler
HDRS = assembler.h
SRCS = main.cpp

OBJS = main.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp $(HDRS)
	$(CC) $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -f $(PROG) $(OBJS)