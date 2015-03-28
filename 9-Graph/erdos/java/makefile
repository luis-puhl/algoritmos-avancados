.SUFFIXES: .cpp .exe .out

.cpp.exe:
	g++ -Wall -o "$*.exe" "$*.cpp" -lm -lcrypt -O2 -std=c++11 -pipe -pthread -DMAKEFILE

.exe.out: ../in
	./$*.exe mke < ../in > $*.out

test: other.exe
	./other.exe mke < ../in | less

clean:
	-rm *.o
