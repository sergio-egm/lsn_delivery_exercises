/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 1 Mag 2023

Test del generatore di numeri casuali.

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <armadillo>

#include "funzioni.h"
#include "BlockAnalisys.h"

using namespace arma;


class Test{
    public:
        Test(void);
        ~Test(){;}

        //Satmpa i risultati a file
        void Print(unsigned int index);
        //Evolvo la media e la varianza
        void Measure(unsigned int index);
        //Aggiorno la media e la varianza
        void Accumulate(unsigned index);
        //Evolvo le medie
        void Evolve(void);
        //Test di chi2
        void Test_Chi2(void);

    private:
        unsigned int M;     //Numero di numeri generati
        unsigned int N;     //Numero di blocchi
        unsigned int L;     //Numeri per blocco

        //File di output
        std::ofstream Ave;
        std::ofstream Var;
        std::ofstream Chi;

        vec walker{2,fill::zeros};  //Grandezze progressive
        vec summ{2,fill::zeros};    //Somme progressive
        vec summ2{2,fill::zeros};   //Somme progressive dei quadrati

        unsigned int ia, iv;    //Indici delle grandezze

        std::vector<double> r ;     //Numeri generati casualmente
};


class TestRandom: public Method{
    public:
	    TestRandom(void);
		~TestRandom() override {;}
		void Run(void) override;
		void Accumulate(void) override;
		void Reset(void) override;
		void Print(void);
		//void Chi2(void);
	private:
        //Indices
        unsigned int nsam;  //Sample
        unsigned int nblk;  //Block
        
		//Random Number generetor
		Random rnd;
        //Generated random number
        double number;

		//Averasges in the block
		vec walker{2,fill::zeros};
		//Averege of the blocks
		vec ave{2,fill::zeros};
		vec ave2{2,fill::zeros};
		
		//Chi square
		//vec chi2{2,fill::zeros};

		//Print variables
		std::ofstream Ave;
		std::ofstream Var;
		std::ofstream Chi;
		std::ofstream Numb;
};





/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
