CC = clang++
CFLAGS = -g -Wall

PROG = assembler
HDRS = assembler.h parser.h
SRCS = main.cpp parser.cpp

OBJS = main.o parser.o

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

main.o: main.cpp $(HDRS)
	$(CC) $(CFLAGS) -c main.cpp -o main.o

parser.o: parser.cpp $(HDRS)
	$(CC) $(CFLAGS) -c parser.cpp -o parser.o

clean:
	rm -f $(PROG) $(OBJS)