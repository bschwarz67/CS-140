all: dl_hash_test

dl_hash_test: dl_hash.o dl_hash_test.o dlist.o
	g++ -o dl_hash_test dl_hash.o dl_hash_test.o dlist.o
	rm *.o

dl_hash_test.o: dl_hash_test.cpp
	g++ -c dl_hash_test.cpp

dl_hash.o: dl_hash.cpp
	g++ -c dl_hash.cpp

dlist.o: dlist.cpp
	g++ -c dlist.cpp
