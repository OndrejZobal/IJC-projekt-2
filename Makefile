CC=gcc
CFLAGS=-g -fPIC -Wextra -Wall -pedantic -std=c11
LIBS=-L. -lhtab

SOURCES := $(wildcard htab*.c)
OBJECTS := $(patsubst %.c, %.o, $(SOURCES))

all: tail wordcount-dynamic wordcount

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail

wordcount: libhtab.a wordcount.o io.o
	$(CC) $(CFLAGS) -static wordcount.o io.o -o $@ $(LIBS)

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) $(CFLAGS) wordcount.o io.o -o $@ $(LIBS)


wordcount.o: wordcount.c
	$(CC) $(CFLAGS) -c $^ -o $@

tail.o: tail.c
	$(CC) $(CFLAGS) -c $^ -o $@

io.o: io.c
	$(CC) $(CFLAGS) -c $^ -o $@

libhtab.a: htab_bucket_count.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o htab_hash_function.o htab_init.o htab_lookup_add.o htab_resize.o htab_size.o
	ar crs $@ $^

libhtab.so: $(OBJECTS)
	$(CC) -shared $^ -o $@

clean:
	rm *.o *.a *.so tail wordcount wordcount-dynamic

 htab_bucket_count.o: htab_bucket_count.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_clear.o: htab_clear.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_erase.o: htab_erase.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_find.o: htab_find.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_for_each.o: htab_for_each.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_free.o: htab_free.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_hash_function.o: htab_hash_function.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_init.o: htab_init.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_lookup_add.o: htab_lookup_add.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_resize.o: htab_resize.c
	$(CC) $(CFLAGS) -c $^ -o $@
 htab_size.o: htab_size.c
	$(CC) $(CFLAGS) -c $^ -o $@
