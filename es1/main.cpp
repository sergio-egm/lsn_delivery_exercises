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

#include "funzioni.h"

int main(int argc,char** argv){
    //Chiamo la mia funzione test
    test_function();
    
    //Inizializzo le variabili
    unsigned int M= 1000000;      //Numero di numeri generati
    unsigned int N= 100;         //Numero di blocchi
    unsigned int L= M/N;         //Numeri per blocco

    double ave=0;	//Media del blocco
    double var=0;	//Varianza del blocco

    double summA=0;     //Somma progressiva medie
    double summ2A=0;    //Somma progressiva dei quadrati delle medie
    double summV=0;     //Somma progressiva varianze
    double summ2V=0;    //Somma progressiva dei quadrati delle varianze

    std::vector<double> r ;     //Numeri generati casualmente

    //Impostoto i valori passati da terminale
    //Se no passo quelli pre-impostati
    if(argc==3){
        M=atoi(argv[1]);
        N=atoi(argv[2]);
        L=M/N;
    }

    //Riempio il vettore
    fillR(r,M);


    //Apro il file di output1
    std::ofstream fout1("output1.dat");
    std::ofstream fout2("output2.dat");
    
    //Faccio partire il grafico da (0,0)
    fout1<<0<<'\t'<<0<<'\t'<<0<<std::endl;
    fout2<<0<<'\t'<<0<<'\t'<<0<<std::endl;

    //Calcolo l'evoluzione delle medie
    for (unsigned int i=0; i<N ;i++){
        ave= average_block(r,L,i);
        var= var_block(r,L,i);

        //Evolvo le somme
        summA+=1./static_cast<double>(i+1)*(ave-summA);
        summ2A+=1./static_cast<double>(i+1)*(ave*ave-summ2A);
        summV+=1./static_cast<double>(i+1)*(var-summV);
        summ2V+=1./static_cast<double>(i+1)*(var*var-summ2V);

        //Stampo i risultati a file
        fout1<<(i+1)*L<<'\t'<<summA-0.5<<'\t'<<rms(summA,summ2A,i)<<std::endl;
        fout2<<(i+1)*L<<'\t'<<summV-1./12.<<'\t'<<rms(summV,summ2V,i)<<std::endl;
    }

    //Chiudo il file
    fout1.close();
    fout2.close();

    //Test chi2
    unsigned int n=10000;
    unsigned int blk=100;
    unsigned int K=M/n;

    fout1.open("chi2.dat");
    for (unsigned int i=0; i<K ; i++)
        fout1<<chi2(r,i*n,(i+1)*n,blk)<<std::endl;
    
    fout1.close();


    return 0;
}









/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
