all: bstree_test

bstree_test: bstree_test.o bstree.o
	g++ -o bstree_test bstree_test.o bstree.o
	rm *.o

bstree_test.o: bstree_test.cpp
	g++ -c bstree_test.cpp

bstree.o: bstree.cpp
	g++ -c bstree.cpp

