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

    Test m_test1;

    m_test1.Evolve();
    m_test1.Test_Chi2();

    TestRandom m_test;
    BlockAnalisys blk(1000000,100);

    blk.Run(m_test);

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


TestRandom::TestRandom(void){
    //Initialize random generator
    int seed[4];
	int p1, p2;


	std::ifstream Primes("Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;
	Primes.close();

	std::ifstream input("seed.in");
	std::string property;
	if (input.is_open()){
    	while ( !input.eof() ){
        	input >> property;
        	
			if( property == "RANDOMSEED" ){
        	input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
        	rnd.SetRandom(seed,p1,p2);
        	}
      	}
	input.close();
	} else std::cerr << "PROBLEM: Unable to open seed.in" << std::endl;

    //Open output files
    Ave.open("output_ave.dat");
    Var.open("output_var.dat");
    Chi.open("output_chi2.dat");
	Numb.open("output_numb.dat");
}

//Generate random number
void TestRandom::Run(void){
    number=rnd.Rannyu();
    nsam++;
    Numb<<number<<std::endl;
}

//Update the averages in the block
void TestRandom::Accumulate(void){
    walker(0)+=1./static_cast<double>(nsam)*(number-walker(0));
    walker(1)+=1./static_cast<double>(nsam)*(number*number-walker(1));
}

//Reset the variables of the block
//  print the variebles in a file
void TestRandom::Reset(void){
    nblk++;

    //Compute the rms of the block
    walker(1)=walker(1)-std::pow(walker(0),2);

    //Update block average
    ave+=1./static_cast<double>(nblk)*(walker-ave);
    ave2+=1./static_cast<double>(nblk)*(square(walker)-ave2);

    //Print outputs
    Print();

    //Reset block variables
    walker.zeros();
    nsam=0;
}

void TestRandom::Print(void){
    Ave<<nblk<<'\t'<<walker(0)-0.5<<'\t'<<ave(0)-0.5<<'\t'<<sqrt(1./static_cast<double>(nblk-1)*(ave2(0)-std::pow(ave(0),2)))<<std::endl;
    Var<<nblk<<'\t'<<walker(1)-(1./12.)<<'\t'<<ave(1)-(1./12.)<<'\t'<<sqrt(1./static_cast<double>(nblk-1)*(ave2(1)-std::pow(ave(1),2)))<<std::endl;
}


/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
