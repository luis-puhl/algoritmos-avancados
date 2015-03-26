main.c.exe: main.c
	gcc -Wall -o main.c.exe main.c -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE

ctest: main.c.exe input expected
	./main.c.exe < input > output
	diff -y output expected

runc: main.c.exe
	./main.c.exe



main.cpp.exe: main.cpp
	g++ -Wall -o "main.cpp.exe" "main.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE

cpptest: main.cpp.exe input expected
	./main.cpp.exe < input > output
	diff -y output expected



simpler.c.exe: simpler.c
	gcc -Wall -o "simpler.c.exe" "simpler.c" -lm -lcrypt -O2 -pipe -ansi -DONLINE_JUDGE

simplertest: simpler.c.exe input expected
	./simpler.c.exe < input > output
	diff -y output expected

