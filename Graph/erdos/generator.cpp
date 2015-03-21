#include <stdio.h>
#include <iostream>


char *gen(char *mem){
	int i;
	int flag = 1;
	
	i = 0;
	// if overflow
	while (flag) {
		switch (mem[i]){
			case 'Z': mem[i] = 'a'; break;
			case 'z': i++; break;
			default: mem[i]++; flag = 0;
		}
	}
	return mem;
}

char name1[101] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
char name2[101] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
int main(int argc, char **argv){
	
	printf("%s, D., Erdos, P.: A Paper\n", gen(name1));
	
	for (int i = 0; i < 100; i++){
		printf("%s, D., %s, P.: A Paper\n", gen(name1), gen(name2));
	}
	
	return 0;
}

