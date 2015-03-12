test: expected untitled.cpp
	g++ -Wall -o "untitled" "untitled.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE
	./untitled > out
	diff -y expected out

four: expected untitled.cpp
	g++ -Wall -o "untitled" "untitled.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D DEBUG
	./untitled > out

fourreaproveita: expected reaproveita.cpp
	g++ -Wall -o "reaproveita" "reaproveita.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D DEBUG
	./reaproveita > out
	cat out | less

fourreaproveitaSHOW: expected reaproveita.cpp
	g++ -Wall -o "reaproveita" "reaproveita.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D SHOW_RESULT
	./reaproveita > out
	diff -y expected out

testreaproveita: expected reaproveita.cpp
	g++ -Wall -o "reaproveita" "reaproveita.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE
	./reaproveita > out
	diff -y expected out

time: expected nova.cxx
	g++ -Wall -o "nova" "nova.cxx" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D SHOW_RESULT
	time ./nova > out
	diff -y expected out
