/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 05 Mar 2023

Test del generatore di numeri casuali.

*****************************************************************
****************************************************************/

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


int main(int argc,char** argv){
    //Chiamo la mia funzione test
    test_function();

    Input();

    //Riempio il vettore
    std::cout<<"Generazione numeri casuali"<<std::endl;
    fillR(r,M);
    std::cout<<std::endl;

    //Calcolo l'evoluzione delle medie
    std::cout<<"Medie a blocchi con media e varianza"<<std::endl;
    for (unsigned int i=0; i<N ;i++){
        Measure(i);
        Accumulate(i);
        Print(i+1);
    }
    std::cout<<std::endl;

    //Test chi2
    std::cout<<"Test del Chi2"<<std::endl;
    for (unsigned int i=0; i<N ; i++)
        Chi<<chi2(r,i*L,(i+1)*L,N)<<std::endl;
    std::cout<<std::endl;


    return 0;
}




//Carico i dati dal file input.dat
void Input(void){
    //Attribuisco degli indici alle grandezze
    ia=0;   //Media
    iv=1;   //Varianza

    std::ifstream fin("input.dat");

    if(!fin.is_open()){
        std::cerr<<"\tFile \"input.dat\" non trovato!"<<std::endl;
        exit(-1);
    }

    fin>>M;
    fin>>N;
    L=M/N;

    fin.close();

    std::cout<<"Numeri generati=    \t"<<M<<std::endl;
    std::cout<<"Numero di blocchi=  \t"<<N<<std::endl;
    std::cout<<"Densità dei blocchi=\t"<<L<<" num/blk"<<std::endl;
    std::cout<<std::endl;
}

//Stampo a file i valori
void Print(unsigned int N){
    Ave<<N*L<<'\t'<<summ[ia]-0.5<<'\t'<<rms(summ[ia],summ2[ia],N-1)<<std::endl;
    Var<<N*L<<'\t'<<summ[iv]-1./12.<<'\t'<<rms(summ[iv],summ2[iv],N-1)<<std::endl;
}

//Calcolo la media del blocco
void Measure(unsigned int index){
    walker[ia]= average_block(r,L,index);
    walker[iv]= var_block(r,L,index);
}

//Evolvo le somme
void Accumulate(unsigned index){
    summ+=1./static_cast<double>(index+1)*(walker-summ);
    summ2+=1./static_cast<double>(index+1)*(square(walker)-summ2);
}








/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
