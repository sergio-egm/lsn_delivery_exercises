/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulation of Buffon's experiment.

*****************************************************************
****************************************************************/
#pragma once

#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>

#include "random.h"
#include "BlockAnalisys.h"

//Initialize data form buffon.input
//M: Total number of throws
//N: Number of blocks
//L: Neadle length
//d: Line distance
int Input(unsigned int& M, unsigned int& N, double& L, double& d);

//Return the sign of a number
int sign(double x);

//System class
class Buffon:public Method{
	public:
        Buffon(double L,double d);
		~Buffon() override{;}

		//Count the number of hits
		void Accumulate(void) override;
		//Run the simulation
		void Run(void) override;
		//Reset the averages
		void Reset(void) override;
    private:
        unsigned int nblk;
        //Length and distance
        double m_L, m_d;
        //Average
        double pi;
        //Average of squares
        double pi2;
        //Number of throws/hits
        double Nthr,Nhit;
        //Does the nidle hit the line?
        bool hit;

        Random rnd;
        std::ofstream fout;

        double Throw(void);
        void Print(void);
};