/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Usa il metodo dell'inversiobne per l'estrazione di numeri

*****************************************************************
****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>

#include "funzioni.h"
#include "random.h"

double M;	//Numero di estrazioni
Random rnd;	//Generatore di numeri casuali

void Input(void);	//Inizializza le variabili

int main(){
	init_rand(rnd);

	//Numero di blocchi
	std::vector<unsigned int> N{1,2,10,100};

	for (unsigned int i=0; i<4 ;i++){
		print_std(rnd,N[i],M);
		print_exp(rnd,N[i],M);
		print_ltz(rnd,N[i],M);
	}

	return 0;
}

void Input(void){
	std::ifstream fin("input.dat");

	if(!fin.is_open()){
		std::cerr<<"File \"input.dat\" non trovato!"<<std::endl;
		exit(-1);
	}

	fin>>M;

	fin.close();
}





/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
