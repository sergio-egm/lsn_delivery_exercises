#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

#include <armadillo>

#include "random.h"

#include "mpi.h"

using namespace arma;

class Cities{
    public:
        Cities(void);
        ~Cities(){;}

        //Evaluate distance between points
        double Distance(unsigned int i, unsigned int j) const;
        //Return number of cities
        unsigned int Nelem(void) const{return coordinates.n_rows;}

        void PrintCity(unsigned int i,std::ostream& os){
            os<<coordinates(i,0)<<'\t'<<coordinates(i,1)<<std::endl;
        }

        vec Get(unsigned int i){return coordinates.row(i);}

    private:
        mat coordinates;
};

class Individual{
    public:
        Individual(Random& rnd,unsigned int num);
        Individual(vec in_vec);
        ~Individual(){;}

        //Evaluate the loss function
        double Eval(int err);

        //Overloading operators
        double operator()(unsigned int i){return genies(i);}
        friend bool operator<(Individual& X1, Individual& X2){return X1.L<X2.L;}

        //Get & Set
        void SetGen(unsigned int i,double x){genies(i)=x;}
        double GetGen(unsigned int i){return genies(i);}
        double GetL(void){return L;}
        vec GetGenies(void){return genies;}

        //Mutation methods
        void shuffle(Random& rnd);
        void permutation(Random &rnd);
        void inversion(Random &rnd);


        //Check if the values are unique and in the range
        void check(int err);
    private:
        double L;
        vec genies;
};


class GeneticAlgorithm{
    public:
        GeneticAlgorithm(int rank,unsigned int& ngen,unsigned int& nmig);
        ~GeneticAlgorithm(){;}

        unsigned int Select(void);
        void Cross(unsigned int X1,unsigned int X2);
        void Run(int rank,unsigned int ngen,unsigned int ninit);

        void PrintBest(int rank);
        
        //Get & Set the best individual
        void get_best(int* output);
        void set_best(int* input);
        //Get best loss function
        double get_Lbest(void){return population[0].GetL();}
        //double get_LbestH(void);

    private:
        std::vector<Individual> population;

        double m_p; //Coefficient p

        //Probabilities
        double m_pc;
        double m_ps,m_pp,m_pi;

        Random rnd;
        unsigned int nstep;
        unsigned int nmig;
};

//Shuffle elements
void shuffle(int* send,int* recive, Random& rnd, int num);
//Find the minimum value
void find_min(double* vec,int size);

Cities city;
