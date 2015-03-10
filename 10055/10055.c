/*
 * 

Problem A

Hashmat the brave warrior

Input: standard input

Output: standard output

Hashmat is a brave warrior who with his group of young soldiers 
moves from one place to another to fight against his opponents. 
Before fighting he just calculates one thing, the difference between 
his soldier number and the opponent's soldier number. From this 
difference he decides whether to fight or not. Hashmat's soldier 
number is never greater than his opponent.

Input

The input contains two integer numbers in every line. These two 
numbers in each line denotes the number of soldiers in Hashmat's 
army and his opponent's army or vice versa. The input numbers are 
not greater than 2^32. Input is terminated by End of File.

Output

 For each line of input, print the difference of number of soldiers 
 between Hashmat's army and his opponent's army. Each output should 
 be in seperate line.

Sample Input:
10 12
10 14
100 200

Sample Output:
2
4
100
* 
Shahriar Manzoor
16-12-2000 
* 
 */

#include <stdio.h>

int main(int argc, char **argv){
	long hashmat, enemy;
	
	while (scanf("%ld %ld", &hashmat, &enemy) != EOF){
		printf("%ld\n", enemy - hashmat);
	}
	
	return 0;
}

