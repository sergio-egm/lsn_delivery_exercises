/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Test del generatore di numeri casuali.

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <armadillo>

#include "funzioni.h"

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




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/