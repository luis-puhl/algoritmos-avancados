untitled.exe:
	g++ -Wall -o "untitled.exe" "untitled.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE

untitledD.exe:
	g++ -Wall -o "untitledD.exe" "untitled.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D DEBUG

test: expected untitled.exe
	./untitled > out
	diff -y expected out

four: expected untitledD.exe
	./untitled > out

fourreaproveita: expected reaproveitaD.exe
	./reaproveita > out
	cat out | less

fourreaproveitaSHOW: expected reaproveita.exe
	./reaproveita.exe > out
	diff -y expected out

reaproveita.exe: reaproveita.cpp
	g++ -Wall -o "reaproveita.exe" "reaproveita.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D SHOW_RESULT

reaproveitaD.exe: reaproveita.cpp
	g++ -Wall -o "reaproveitaD.exe" "reaproveita.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D SHOW_RESULT -D DEBUG

testreaproveita: expected reaproveita.exe
	./reaproveita.exe > out
	diff -y expected out

time: expected nova.exe
	time ./nova.exe > out
	diff -y expected out

nova.exe: nova.cxx
	g++ -Wall -o "nova.exe" "nova.cxx" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE -D SHOW_RESULT

clean:
	rm *.o
