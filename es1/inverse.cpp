/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica:...

...

*****************************************************************
****************************************************************/
#include <iostream>
#include <vector>

#include "funzioni.h"
#include "random.h"

int main(){
	double M=10000;
	Random rnd;
	init_rand(rnd);

	std::vector<unsigned int> N{1,2,10,100};

	for (unsigned int i=0; i<4 ;i++){
		print_std(rnd,N[i],M);
		print_exp(rnd,N[i],M);
		print_ltz(rnd,N[i],M);
	}

	return 0;
}





/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
