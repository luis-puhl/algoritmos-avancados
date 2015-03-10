/*
 * 10198-Gustavo.cxx
 * 
 * Copyright 2015 luis puhl <luis@pokebola>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#include <stdio.h>
#include <iostream>
#include <math.h>
#include <iomanip>
#include <limits>

#define DEBUG 1

#ifdef DEBUG
#include <sys/time.h>
#endif

using namespace std;


const unsigned long int pot10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000,
		10000000, 100000000 };
int DIGITOS = 8;

struct Base {
	unsigned long int *v;
	bool negativo;
	int tam;
	Base() {
		v = 0;
		negativo = false;
		tam = 0;
	}

	void inicia(int n = 1, bool neg = false, unsigned long int *_v = 0) {
		if (n != tam) {
			if (tam != 0) {
				delete v;
			}
			v = new unsigned long int[n];
			tam = n;
		}
		if (_v != 0) {
			for (int i = 0; i < tam; i++)
				v[i] = _v[i];
		} else {
			for (int i = 0; i < tam; i++)
				v[i] = 0;
		}
		negativo = neg;
	}

};

struct Inteirao: public Base {

	Inteirao(const char * s) {
		int i = 0;
		while (s[i] != 0)
			i++;
		i--;

		inicia(i / DIGITOS + 1);

		for (int j = 0; i >= 0; i--, j++)
			v[j / DIGITOS] += (s[i] - '0') * pot10[j % DIGITOS];
	}

	Inteirao(const Inteirao &i1) {
		inicia(i1.tam, i1.negativo, i1.v);
	}

	Inteirao(int i = 0) {
		inicia(1, i < 0);
		v[0] = i;
	}

	~Inteirao() {
		delete v;
	}

	Inteirao operator-() const {
		Inteirao resultado(*this);
		resultado.negativo = !resultado.negativo;
		return resultado;
	}

	int compara(const Inteirao & i2) const {
		if (!negativo && i2.negativo) {
			return 1;
		} else if (negativo && !i2.negativo) {
			return -1;
		}
		if (tam > i2.tam) {
			return 1;
		} else if (tam < i2.tam) {
			return -1;
		} else {
			for (int i = tam - 1; i >= 0; i++)
				if (v[i] > i2.v[i])
					return 1;
				else if (v[i] < i2.v[i])
					return -1;
			return 0;
		}
	}

	bool operator>(const Inteirao & i2) const {
		return compara(i2) > 0;
	}

	bool operator==(const Inteirao & i2) const {
		return compara(i2) == 0;
	}

	bool operator<(const Inteirao & i2) const {
		return compara(i2) < 0;
	}

	Inteirao operator-(const Inteirao i2) const {
		Inteirao resultado;

		if (negativo ^ i2.negativo) { // se sinais diferentes
			if (i2.negativo) {
				resultado = *this + -i2;
			} else if (negativo) {
				resultado = -*this + i2;
			}
		} else {
			if (*this < i2) {
				resultado = -(i2 - *this);
			} else {
				Inteirao sub(*this);

				int i = i2.tam - 1;
				while (i >= 0) {
					sub.v[i] -= i2.v[i];
					if (sub.v[i] < 0) {
						sub.v[i] += pot10[DIGITOS];
						sub.v[i + 1] -= 1;
					}
					i--;
				}
				resultado = sub;
			}
		}
		return resultado;
	}

	Inteirao operator+(const Inteirao i2) const {
		Inteirao resultado;
		int carry = 0;

		if (negativo ^ i2.negativo) { // se sinais diferentes
			if (negativo) {
				resultado = (i2 - -*this); // menus unario
			} else {
				resultado = *this - -i2;
			}
		} else {
			Inteirao soma;
			soma.inicia(max(tam, i2.tam));

			int i = 0;
			while (i < tam || i < i2.tam) {
				soma.v[i] = carry;
				if (i < tam)
					soma.v[i] += v[i];
				if (i < i2.tam)
					soma.v[i] += i2.v[i];
				carry = soma.v[i] >= pot10[DIGITOS] ? 1 : 0;
				if (carry)
					soma.v[i] -= pot10[DIGITOS];
				i++;
			}
			if (carry) {
				resultado.inicia(soma.tam + 1, negativo);
				resultado.v[resultado.tam - 1] = 1;
			} else {
				resultado.inicia(soma.tam, negativo);
			}
			for (int i = 0; i < soma.tam; i++)
				resultado.v[i] = soma.v[i];
		}

		return resultado;
	}

	Inteirao operator=(const Inteirao i2) {
		inicia(i2.tam, i2.negativo, i2.v);
		return *this;
	}

	friend ostream & operator<<(ostream & o1, Inteirao & i2);
};

ostream & operator<<(ostream & o1, Inteirao & i2) {
	if (i2.negativo)
		o1 << "-";
	o1 << i2.v[i2.tam - 1];// << " ";
	for (int i = i2.tam - 2; i >= 0; i--) {
		o1.width(DIGITOS);
		o1.fill('0');
		o1 << i2.v[i];// << " ";
	}
	return o1;
}

Inteirao* g(int i);

Inteirao* f(int i){
	Inteirao* ret = new Inteirao();
	switch(i){
		case 0: *ret = 1; break;
		case 1: *ret = 2; break;
		case 2: *ret = 5; break;
		default:{
			if (i <= 0){
				*ret = 0;
			} else {
				*ret = (*g(i-1) + *g(i-1)) + *g(i-2) + *g(i-3);
			}
		}
	}
	return ret;
}

Inteirao *aws[1000];
Inteirao* g(int i){
	if (aws[i] != NULL){
		return aws[i];
	}
	aws[i] = f(i);
	return aws[i];
}

int main(int argc, char **argv){
	Inteirao f;
	int i;
	
	while (scanf("%d", &i) == 1){
		f = *g(i);
		cout << f << endl;
	}
	
	return 0;
}

