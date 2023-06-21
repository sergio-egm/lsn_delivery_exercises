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

class Dice {
    public:
        Dice(void);
        virtual ~Dice(){;}
        virtual void Fill(void) = 0;
        double get_number(unsigned int i) const{
            if (i>=extraction.size()){
                std::cerr<<"PROBLEM: Index out of range."<<std::endl;
                exit(-1);
            }
            return extraction[i];
        }
        std::string get_name(void) const{return name;}
        unsigned int get_dimension(void) const{return dim;}

    protected:
        unsigned int dim;               //Namber of extraction

        std::vector<double> extraction; //Nuber extracted
        Random m_rnd;                   //Random number generetor

        std::string name;               //Kind of dice
};

class Block{
    public:
        Block(void):N{1,2,10,100},suffix{".dat"}{;}
        ~Block(){;}

        //Analize different dices
        void Analize(const Dice& in_dice) const;

    private:
        std::vector<unsigned int> N;    //Block dimension
        
        std::string suffix;
};


//Constants of ditributions

class Constants{
    public:
        Constants(void);
        ~Constants(){;}

        //Uniform Distribution
        double get_min(void) const {return min_unif;}
        double get_max(void) const {return max_unif;}
        //Gaussian
        double get_mu(void) const {return mu_gauss;}
        double get_sigma(void) const {return sigma_gauss;}

    private:
        //Uniform Distribution
        double min_unif, max_unif;
        //Gaussian
        double mu_gauss, sigma_gauss;
};


//Specific dices

//Gaussian dice
class Gaussian: public Dice{
    public:
        Gaussian(double in_mu,double in_sigma);
        ~Gaussian() override{;}

        //Fill method
        void Fill(void) override;
    
    private:
        //Mu and sigma parameters of gaussian distribution
        double m_mu, m_sigma;

};


//Satndard dice(continous)
//Uniform distribution between given values
class Standard: public Dice{
    public:
        Standard(double in_min,double in_max);
        ~Standard() override{;}

        //Fill method
        void Fill(void) override;

    private:
        //Minimum value and range
        double m_min , m_range;
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/