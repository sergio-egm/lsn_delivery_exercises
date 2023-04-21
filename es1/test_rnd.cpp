/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Test del generatore di numeri casuali.

*****************************************************************
****************************************************************/

#include "test_rnd.h"

int main(int argc,char** argv){
    //Chiamo la mia funzione test
    test_function();

    Test m_test;

    m_test.Evolve();
    m_test.Test_Chi2();


    return 0;
}


Test::Test(void){
    //Attribuisco degli indici alle grandezze
    ia=0;   //Media
    iv=1;   //Varianza

    //Prendo i dati iniziali da file
    std::ifstream fin("input.dat");

    //Controllo che il file sia aperto
    if(!fin.is_open()){
        std::cerr<<"\tFile \"input.dat\" non trovato!"<<std::endl;
        exit(-1);
    }

    fin>>M;
    fin>>N;
    L=M/N;

    fin.close();

    //Stampo i dati da file
    std::cout<<"Numeri generati=    \t"<<M<<std::endl;
    std::cout<<"Numero di blocchi=  \t"<<N<<std::endl;
    std::cout<<"Densità dei blocchi=\t"<<L<<" num/blk"<<std::endl;
    std::cout<<std::endl;

    //Imposto le variabili di stampa a file
    Ave.open("output_ave.dat");
    Var.open("output_var.dat");
    Chi.open("output_chi2.dat");

    //Riempio il vettore
    std::cout<<"Generazione numeri casuali"<<std::endl;
    fillR(r,M);
    std::cout<<std::endl;
}

//Stampo a file i valori
void Test::Print(unsigned int N){
    Ave<<N*L<<'\t'<<summ[ia]-0.5<<'\t'<<rms(summ[ia],summ2[ia],N-1)<<std::endl;
    Var<<N*L<<'\t'<<summ[iv]-1./12.<<'\t'<<rms(summ[iv],summ2[iv],N-1)<<std::endl;
}

//Calcolo la media del blocco
void Test::Measure(unsigned int index){
    walker[ia]= average_block(r,L,index);
    walker[iv]= var_block(r,L,index);
}

//Evolvo le somme
void Test::Accumulate(unsigned index){
    summ+=1./static_cast<double>(index+1)*(walker-summ);
    summ2+=1./static_cast<double>(index+1)*(square(walker)-summ2);
}

//Faccio l'evoluzione della media a blocchi
void Test::Evolve(void){
    std::cout<<"Medie a blocchi con media e varianza"<<std::endl;
    for (unsigned int i=0; i<N ;i++){
        Measure(i);
        Accumulate(i);
        Print(i+1);
    }
    std::cout<<std::endl;
}

//Test di chi2
void Test::Test_Chi2(void){
    std::cout<<"Test del Chi2"<<std::endl;
    for (unsigned int i=0; i<N ; i++)
        Chi<<chi2(r,i*L,(i+1)*L,N)<<std::endl;
    std::cout<<std::endl;
}



/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
