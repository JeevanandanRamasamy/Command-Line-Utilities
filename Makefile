CFLAGS = -g -Wall -Wvla -fsanitize=address

ls: ls.c
	gcc $(CFLAGS) -o $@ $^

find: find.c
	gcc $(CFLAGS) -o $@ $^

tree: tree.c
	gcc $(CFLAGS) -o $@ $^

all: ls.c find.c tree.c
	gcc $(CFLAGS) -o ls ls.c
	gcc $(CFLAGS) -o find find.c
	gcc $(CFLAGS) -o tree tree.c

clean:
	rm -rf ls find tree