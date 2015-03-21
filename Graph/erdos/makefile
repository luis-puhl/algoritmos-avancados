a.exe: a.cpp
	g++ -Wall -o "a.exe" "a.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE

clean.exe: clean.cpp
	g++ -Wall -o "clean.exe" "clean.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE

testclean: clean.exe in expected
	./clean.exe < in > out
	diff -y out expected

atest: a.exe in
	./a.exe < in
