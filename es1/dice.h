/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 09 May 2023

Empirical proof of Central Limit Theorem, using different kind 
of dices:
-Standard
-Gaussian
-Exponential
-Lorentzian

*****************************************************************
****************************************************************/

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>

#include "random.h"


//Virtual class to define the different extractions
class Extraction{
    public:
        Extraction(std::string name):
        m_name{name}{;}
        virtual ~Extraction(){;}
        //Evaluate the extraction
        virtual double Eval(Random& rnd) const =0;
        
        //Return the tipe of distibution
        std::string get_extr() const {return m_name;}
    
    protected:
        //Tipe of distibution
        std::string m_name;
};


//Standard dice extraction
class Standard: public Extraction{
    public:
        //Initializing the class by the extreams values
        Standard(double a, double b):
            Extraction{"standard_"},
            m_a{a}, m_b{b}{;}
        ~Standard() override{;}

        //Evaluation of the extraction
        double Eval(Random& rnd) const override{return rnd.Rannyu(m_a,m_b);}
    
    private:
        double m_a, m_b;
};

//Exponential dice extraction
class Exponential: public Extraction{
    public:
        //Initializing the class by the extreams values
        Exponential(double lambda):
            Extraction{"exponential_"},
            m_lambda{lambda}{;}
        ~Exponential() override{;}

        //Evaluation of the extraction
        double Eval(Random& rnd) const override{return rnd.Exponential(m_lambda);}
    
    private:
        double m_lambda;
};


//Exponential dice extraction
class Lorentz: public Extraction{
    public:
        //Initializing the class by the extreams values
        Lorentz(double Gamma,double mu):
            Extraction{"lorentz_"},
            m_Gamma{Gamma}, m_mu{mu}{;}
        ~Lorentz() override{;}

        //Evaluation of the extraction
        double Eval(Random& rnd) const override{return rnd.Lorentz(m_Gamma,m_mu);}
    
    private:
        double m_Gamma, m_mu;
};


//Simulation of dice and extractions
class Dice{
    public:
        Dice(void);
        ~Dice(){;}

        //Evolution of the sistem
        void Evol(Extraction& ext, unsigned int N);
    
    private:
        Random rnd;
        unsigned int M;
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/