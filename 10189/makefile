all: main.cpp input
	g++ -Wall -o main main.cpp
	./main < input > output
	diff -y output expected

simple: main.cpp
	g++ -Wall -o main main.cpp

run: main.cpp
	g++ -Wall -o main main.cpp
	./main

c: main.c
	gcc -Wall -o main main.c


ctest: main.c
	gcc -Wall -o main main.c -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE
	./main < input > output
	diff -y output expected
