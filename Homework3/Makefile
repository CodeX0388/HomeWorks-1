all: init destroy print set

init: init.c
	$(CC) $(CFLAGS) -o init init.c

destroy: destroy.c
	$(CC) $(CFLAGS) -o destroy destroy.c

print: print.c
	$(CC) $(CFLAGS) -o print print.c

set: set.c
	$(CC) $(CFLAGS)-o set set.c

clean:
	rm -f init destroy print set
