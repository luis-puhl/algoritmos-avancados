#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>

using namespace std;

class BigInteger{
	
#define MAXDIGITS 100
#define PLUS      1
#define MINUS     -1

private:
	struct BigInt{
	char digits[MAXDIGITS];
	int  signbit;
	int  lastdigit;
	} num;

	void numero2vet(int src, BigInt &dst){
		inicializaBigInt(dst);
		int pos = 0;
		if (src > 0)
			dst.signbit = PLUS;
		else {
			dst.signbit = MINUS;
			src *= -1; //Deixa o numero positivo
		}
		do {
			dst.digits[pos] = src % 10;
			pos++;
			src /= 10;
		}while (src > 0);
		dst.lastdigit = pos-1;
	}

	void inicializaBigInt(BigInt &a){
		for (int i=0; i< MAXDIGITS; i++){
			a.digits[i] = 0;
		}
		a.signbit = PLUS;
		a.lastdigit = 0;
	}

	void justificaBigInt(BigInt &a){
		while ((a.lastdigit > 0) && (a.digits[a.lastdigit] == 0)){
			a.lastdigit--;
		}
		if ((a.lastdigit == 0) && (a.digits[0] == 0))
			a.signbit = PLUS;
	}

	void digit_shift(BigInt &a, int d){
		if ((a.lastdigit == 0) && (a.digits[0] == 0))
			return;
		
		for (int i=a.lastdigit; i>=0; i--)
			a.digits[i+d] = a.digits[i];
		
		for (int i=0; i<d; i++)
			a.digits[i] = 0;
		
		a.lastdigit = a.lastdigit + d;
	}

	int compara(BigInt a, BigInt b){
		if ((a.signbit == MINUS) && (b.signbit == PLUS))
			return PLUS;
		if ((a.signbit == PLUS) && (b.signbit == MINUS))
			return MINUS;
		if (b.lastdigit > a.lastdigit) return (PLUS*a.signbit);
		if (b.lastdigit < a.lastdigit) return (MINUS*a.signbit);
		
		for (int i = a.lastdigit; i>=0; i--){
			if (a.digits[i] > b.digits[i])
				return (MINUS * a.signbit);
			if (a.digits[i] < b.digits[i])
				return (PLUS * a.signbit);
		}
		return 0;
	}

	void subtrai(BigInt a, BigInt b, BigInt &c){
		int borrow,i,v;
		
		if ((a.signbit == MINUS) && (b.signbit == MINUS)){
			b.signbit = PLUS;
			soma(a,b,c);
			b.signbit = MINUS;
			return;
		}
		
		if (compara(a,b) == PLUS){
			subtrai(b,a,c);
			c.signbit = MINUS;
			return;
		}
		
		c.lastdigit = max(a.lastdigit,b.lastdigit);
		borrow = 0;
		
		for (i = 0; i<=(c.lastdigit); i++){
			v = (a.digits[i] - borrow - b.digits[i]);
			if (a.digits[i] > 0)
				borrow = 0;
			if (v < 0){
				v = v + 10;
				borrow = 1;
			}
			c.digits[i] = (char) v % 10;
		}
		
		justificaBigInt(c);
	}


	void soma(BigInt a, BigInt b, BigInt &c){
		int carry;
		
		inicializaBigInt(c);
		
		if (a.signbit == b.signbit)
			c.signbit = a.signbit;
		else{
			if (a.signbit == MINUS){
				a.signbit = PLUS;
				subtrai(b,a,c);
				a.signbit = MINUS;
			} else {
				b.signbit = PLUS;
				subtrai(a,b,c);
				a.signbit = MINUS;
			}
			return;
		}
		
		c.lastdigit = max(a.lastdigit,b.lastdigit)+1;
		carry = 0;
		
		for (int i=0; i<=(c.lastdigit); i++){
			c.digits[i] = (char) (carry + a.digits[i] + b.digits[i]) % 10;
			carry = (carry + a.digits[i] + b.digits[i]) / 10;
		}
		
		justificaBigInt(c);
	}

	void multiplica(BigInt a, BigInt b, BigInt &c){
		BigInt row, tmp;
		
		inicializaBigInt(c);
		inicializaBigInt(row);
		inicializaBigInt(tmp);
		
		row = a;
		
		for (int i=0; i<=b.lastdigit; i++){
			for (int j=1; j <=b.digits[i];j++){
				soma(c,row,tmp);
				c = tmp;
			}
			digit_shift(row,1);
		}
		
		c.signbit = a.signbit * b.signbit;
		
		justificaBigInt(c);
	}

	void divide(BigInt a, BigInt b, BigInt &c){
		BigInt row,tmp;
		int asign,bsign;
		
		inicializaBigInt(c);
		inicializaBigInt(tmp);
		inicializaBigInt(row);
		
		c.signbit = a.signbit * b.signbit;
		
		asign = a.signbit;
		bsign = b.signbit;
		
		a.signbit = PLUS;
		b.signbit = PLUS;
		
		c.lastdigit = a.lastdigit;
		
		for (int i=a.lastdigit;i>=0;i--){
			digit_shift(row,1);
			row.digits[0] = a.digits[i];
			c.digits[i] = 0;
			while (compara(row,b) != PLUS){
				c.digits[i]++;
				subtrai(row,b,tmp);
				row = tmp;
			}
		}
		
		justificaBigInt(c);
		
		a.signbit = asign;
		b.signbit = bsign;
	}
	
public:
	BigInteger operator=(const int &n){
		BigInteger c;
		numero2vet(n,c.num);
		this->num = c.num;
		return c;
	}
	
	BigInteger operator+(const BigInteger &b){
		BigInteger a,c;
		a.num = this->num;
		soma(a.num,b.num,c.num);
		return c;
	}
	
	BigInteger operator-(const BigInteger &b){
		BigInteger a,c;
		a.num = this->num;
		subtrai(a.num,b.num,c.num);
		return c;
	}
	
	BigInteger operator*(const BigInteger &b){
		BigInteger a,c;
		a.num = this->num;
		multiplica(a.num,b.num,c.num);
		return c;
	}
	
	BigInteger operator/(const BigInteger &b){
		BigInteger a,c;
		a.num = this->num;
		divide(a.num,b.num,c.num);
		return c;
	}
	
	void print(){
		if (num.signbit == MINUS)
			printf("-");
		for (int i=num.lastdigit;i>=0;i--){
			printf("%d",num.digits[i]);
		}
		printf("\n");
	}
};


int main(){
	BigInteger a;
	BigInteger b;
	BigInteger c;
	a = 9;
	b = 4;
	c = a / b;
	a.print();
	b.print();
	c.print();	
}
