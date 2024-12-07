CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra

all: businessdb

businessdb: businessdb_lib.o businessdb.o
	$(CC) businessdb_lib.o businessdb.o -o businessdb

businessdb_lib.o: businessdb_lib.c businessdb_lib.h
	$(CC) $(CFLAGS) -c businessdb_lib.c

businessdb.o: businessdb.c businessdb_lib.h
	$(CC) $(CFLAGS) -c businessdb.c

clean:
	rm -f businessdb.o businessdb_lib.o businessdb

format:
	clang-format -i -style=file *.[ch]
