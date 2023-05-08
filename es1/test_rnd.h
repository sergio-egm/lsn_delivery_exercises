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

#include "BlockAnalisys.h"

using namespace arma;

class TestRandom: public Method{
    public:
	    TestRandom(void);
		~TestRandom() override {;}
		void Run(void) override;
		void Accumulate(void) override;
		void Reset(void) override;
		void Print(void);
		void Chi2(void);
	private:
        //Indices
        unsigned int nsam;  //Sample
        unsigned int nblk;  //Block
        
		//Random Number generetor
		Random rnd;
        //Generated random numbers
        std::vector<double> number;

		//Averasges in the block
		vec walker{2,fill::zeros};
		//Averege of the blocks
		vec ave{2,fill::zeros};
		vec ave2{2,fill::zeros};
		
		//Chi square
		double chi2;
        uvec h;

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
