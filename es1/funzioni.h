/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 05 Mar 2023

Dichiarazione delle funzioni.

*****************************************************************
****************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <assert.h>
#include <armadillo>

#include "../random_lsn/random.h"

//Test funzioni
bool are_close(double oss,
		double calc,
		double eps=1e-7);		//I valori sono abbastanza vicini
void test_function(); 			//Testo le mie funzioni

//Lettura dati
void fillR(std::vector<double>& r, unsigned int throws);	//Riempie il vettore e stampa i dati a file

//Statistica
double average_block(const std::vector<double>& r,
		unsigned int dens,
		unsigned int index);								//Media del blocco
double rms(double AV, double AV2, unsigned int n);			//Deviazione standard
double var_block(const std::vector<double>& r,
		unsigned int dens,
		unsigned int index,
		double xTrue=0.5);									//Varianza blocco
double chi2(const std::vector<double>& r,
		unsigned int xi, unsigned int xf,
		unsigned int nBloks);					//Test del chi2



//Generazione di numeri casuali
void init_rand(Random& rnd);		//Prendo una classe Random fissanodo i seeds

void print_std(Random& rnd,unsigned int n, unsigned int M);
void print_exp(Random& rnd,unsigned int n, unsigned int M);
void print_ltz(Random& rnd,unsigned int n, unsigned int M);


//Esperimento di Buffon
double buffon_exp( Random& rnd , double leng , double d , unsigned int L );
//Segno di x
int sign(double x);


void find_buffon(double& x, double& y, Random& rnd);
double norm(double x, double y);


//Esperimento di Buffon
class Buffon{
	public:
		Buffon(double in_L , double in_d);
		~Buffon(){;}

		void Simula(unsigned int N);		//Simula l'esperimento di Buffon
		double pi() const{ return m_pi; }		//Restituisce la stima di pi
		double err_pi() const{ return m_err_pi; }	//Restituisce l'errore di pi, utilizzando il valore vero (M_PI)

	private:
		void angle();		//Genera uniformemente angoli da [0,2pi)

		double L , d ;		//Lunghezza ago , distanza tra le linee
		double m_pi , m_err_pi ;	//Stima di pi ed il suo errore
		Random rnd;

		double y1 , x2 , y2 ;	//Coordinate degli estremi dell'ago
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
