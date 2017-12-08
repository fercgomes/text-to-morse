all: src/txtToMorse.o src/bst.o src/splay.o
	gcc src/txtToMorse.o src/bst.o src/splay.o -o txtToMorse

src/txtToMorse.o:
	gcc -c src/txtToMorse.c -o src/txtToMorse.o

src/bst.o:
	gcc -c src/bst.c -o src/bst.o

src/splay.o:
	gcc -c src/splay.c -o src/splay.o

clean:
	rm -rf txtToMorse src/*.o
