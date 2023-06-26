/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulations of RWs:
- On a lactice.
- In a continous space.

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <armadillo>
#include <cmath>

#include "random.h"
#include "BlockAnalisys.h"

using namespace arma;

class RandomWalk: public Method{
    public:
        RandomWalk(double a, unsigned int L);
        ~RandomWalk() override{
            fout.close();
        }

        //Update the average
		void Accumulate(void) override ;
		//Run the simulation
		void Run(void) override ;
		//Reset the averages
		void Reset(void) override ;

        void Print(unsigned int N) ;
    
    private:
        unsigned int nblk, index;
        unsigned int m_L;

        double m_a;

        vec x_c, x_l;
        vec appo;

        mat ave , ave2;
        mat blk, r2;

        Random rnd;

        std::ofstream fout;

        //Make a step
        void continous(void);
        void lactice(void);
};




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
