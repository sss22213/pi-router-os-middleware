CC := gcc
CFLAGS := -g -std=gnu11 -Werror

all: clean main

main: main.o list.o queue.o tree.o wireless.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^ -o $@

pi_uci.o: pi_uci.c
	$(CC) $(CFLAGS) -c $^ -o $@

list.o: list.c
	$(CC) $(CFLAGS) -c $^ -o $@

queue.o: queue.c
	$(CC) $(CFLAGS) -c $^ -o $@

tree.o: tree.c
	$(CC) $(CFLAGS) -c $^ -o $@

wireless.o: wireless.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f *.o main
