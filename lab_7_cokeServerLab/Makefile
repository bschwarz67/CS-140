all: cp_tester

cp_tester: code_processor.o cp_tester.o
	g++ -o cp_tester code_processor.o cp_tester.o
	rm *.o

cp_tester.o: cp_tester.cpp
	g++ -c cp_tester.cpp

code_processor.o: code_processor.cpp
	g++ -c code_processor.cpp
