/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 18 Apr 2023

Test del generatore di numeri casuali.

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <armadillo>

#include "funzioni.h"

using namespace arma;

unsigned int M;     //Numero di numeri generati
unsigned int N;     //Numero di blocchi
unsigned int L;     //Numeri per blocco

vec walker(2,fill::zeros);  //Grandezze progressive
vec summ(2,fill::zeros);    //Somme progressive
vec summ2(2,fill::zeros);   //Somme progressive dei quadrati

unsigned int ia, iv;    //Indici delle grandezze

std::vector<double> r ;     //Numeri generati casualmente

//File di output
std::ofstream Ave("output_ave.dat");
std::ofstream Var("output_var.dat");
std::ofstream Chi("output_chi2.dat");

void Input(void);                   //Inizializzo le mie variabili
void Print(unsigned int index);     //Stampo a file e a terminale
void Measure(unsigned int index);   //Evolvo la media e la varianza
void Accumulate(unsigned index);    //Aggiorno la media e la varianza