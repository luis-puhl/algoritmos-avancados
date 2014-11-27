all: src/706.cpp
	g++ -Wall -o bin/706 src/706.cpp

test: bin/706
	bin/706 < test/input > test/output

test1: bin/706
	bin/706 < test/input1 > test/output1

clean:
	rm bin/706
