/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Calculation of integral using Monte Carlo tecniques.

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <armadillo>

#include "random.h"
#include "BlockAnalisys.h"

using namespace arma;

class BaseFunction{
    public:
        virtual ~BaseFunction(){;}
        virtual double Eval (double x) const =0;
};


//Cosine funcion
class Cos: public BaseFunction{
    public:
        Cos(double omega=1, double A=1, double phi=0):
            m_omega{omega},
            m_A{A},
            m_phi{phi}{;}
        ~Cos() override{;}

        //Return the result of the function
        double Eval(double x) const override{return m_A*std::cos(m_omega*x+m_phi);}

    private:
        double m_omega;
        double m_A;
        double m_phi;
};


//Distribution funcion
class Dist: public BaseFunction{
    public:
        Dist(double A): m_A{A}{;}
        ~Dist() override{;}

        //Return the result of the function
        double Eval(double x) const override{return m_A*(1-x);}
    private:
        double m_A;
};


//Monte Carlo evaluatio
class MonteCarlo: public Method{
    public:
        MonteCarlo(BaseFunction* func, BaseFunction* dist, double a, double b);
        ~MonteCarlo() override
        {
            unif.close();
            imse.close();
        }

        //Update the average
		void Accumulate (void) override;
		//Run the simulation
		void Run(void) override ;
		//Reset the averages
		void Reset(void) override ;

        void Print(void);
    
    private:
        //Extremants
        double m_a, m_b;

        //Function to integrate
        BaseFunction* m_func;
        //Distribution of importance sampling
        BaseFunction* m_dist;

        //Variables
        vec ave, ave2;
        vec blk;
        vec f;

        unsigned int nblk;
        unsigned int index;

        Random rnd;

        std::ofstream unif;
        std::ofstream imse;
};




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/