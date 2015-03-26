problem: 10198-Gustavo.cxx
	g++ -Wall -o "problem" "10198-Gustavo.cxx"

out: problem in
	./problem < in > out

attak:
	g++ -Wall -o "problem" "10198-Gustavo.cxx" -lm -lcrypt -O2 -std=c++11 -pipe -DONLINE_JUDGE
	./problem < in > out
	diff -y out exp
