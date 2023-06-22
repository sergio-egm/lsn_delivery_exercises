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
#include "dice.h"

double M;	//Numero di estrazioni
Random rnd;	//Generatore di numeri casuali

void Input(void);	//Inizializza le variabili

int main(){
	init_rand(rnd);

	//Numero di blocchi
	std::vector<unsigned int> N{1,2,10,100};
	//Number of samples
	double M=10000;

	for (unsigned int i=0; i<4 ;i++){
		print_std(rnd,N[i],M);
		print_exp(rnd,N[i],M);
		print_ltz(rnd,N[i],M);
	}
	//Class Method
	double a,b;
	double lambda;

	//std::vector<unsigned int> N{1,2,10,100};
	std::ifstream fin("dice.input");

	//Getting input data
	fin>>a>>b;
	fin>>lambda;
	fin.close();
	
	//System class
	Dice dice;

	//Extraction kinds
	Standard std(a,b);
	Exponential exp(lambda);

	for(unsigned int i=0; i<N.size() ;i++){
		dice.Evol(std,N[i]);
		dice.Evol(exp,N[i]);
	}

	return 0;
}






//======DICE========//
Dice::Dice(void):
	M{10000}{
	//Initialize random generator
	int seed[4];
	int p1, p2;
	std::ifstream Primes("Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;
	Primes.close();

	std::ifstream input("seed.in");
	std::string property;
	if (input.is_open()){
		while ( !input.eof() ){
			input >> property;
			if( property == "RANDOMSEED" ){
				input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
				rnd.SetRandom(seed,p1,p2);
			}
		}
		input.close();
	} else std::cerr << "PROBLEM: Unable to open seed.in" << std::endl;
}


//Evolution of the sistem
void Dice::Evol(Extraction& ext, unsigned int N){
	double Sn=0;
	std::string suff=".dat";
	
	std::ofstream fout(ext.get_extr()+std::to_string(N)+suff);

	for (unsigned int i=0; i<M ;i++){
		Sn=0;

		for (unsigned int j=0; j<N ;j++)
			Sn+=1./static_cast<double>(N)*ext.Eval(rnd);

		fout<<Sn<<std::endl;
	}
}

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
