#include <stdio.h>
#include <string.h>

#define MAX_AUTHORS 10001
#define MAX_NAME_LEN 101 
#define MAX_PAPER_AUTHORS 5001 
#define MAX_INPUT_LEN 10001 
#define MAX_LINKS 501 
typedef unsigned int nat; // stands for natural

// bitfield
struct bit{
	unsigned int b: 1; // range: 0 - 1
};
const bit bittrue{1};
const bit bitfalse{0};

class bitmap{
	/**
	 * Matriz simétrica com diagonal zero
	 **/
	#define _MAX_MAP ( (MAX_AUTHORS * MAX_AUTHORS) / 2 ) - 2
	bit map[_MAX_MAP];
	
	nat serialize(nat x, nat y){
		printf("\tserialize\n");
		if (x == y) return 0;
		if (x > y) return serialize(y, x);
		nat k = (x*y) / 2;
		if (k >= _MAX_MAP) return 0;
		printf("\tserialize(%d, %d) in to %u\n", x, y, k);
		return k;
	}
	public:
	bit get(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return bitfalse;
		return map[ se ];
	}
	bool put(nat x, nat y, bit k){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = k;
		return true;
	}
	bool set(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = bittrue;
		return true;
	}
	bool clear(nat x, nat y){
		nat se = serialize(x, y);
		if (se == 0) return false;
		map[ se ] = bittrue;
		return true;
	}
	bitmap(){
		memset(map, 0, _MAX_MAP * ( sizeof(bit) * sizeof(int) ));
	}
};

bitmap yay;
void publicouCom(nat x, nat y){
	yay.set(x, y);
}

int main(int argc, char **argv){
	
	printf("teste\n");
	yay.set(MAX_AUTHORS - 2, MAX_AUTHORS - 1) ? : printf("\tfaild\n");
	printf("yay\n");
	bit x = yay.get(MAX_AUTHORS - 2, MAX_AUTHORS - 1);
	printf("yay\n");
	printf("%x\n", x.b);
	
	scanf("%*c");
	
	return 0;
}

