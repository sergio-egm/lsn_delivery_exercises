/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

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



//Specific method to test the random generator
class TestRandom: public Method{
    public:
	    TestRandom(void);
		~TestRandom() override;

		//Run the simulation
		void Run(void) override;
		//Update block averages
		void Accumulate(void) override;
		//Reset variables
		void Reset(void) override;
		//Print output to file
		void Print(void);
		//Chi2 test
		void Chi2(void);
		//Set number of samples per block
		void SetChi2(unsigned int in_nblk){nblk_chi2=in_nblk;}


	private:
        //Indices
        unsigned int nsam;  	//Sample
        unsigned int nblk;  	//Block
		unsigned int nblk_chi2;	//Number of samples per block (chi2)
        
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


//Initialize my system
void Input(unsigned int& nsam, unsigned int& nblk, TestRandom& in_test);




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
