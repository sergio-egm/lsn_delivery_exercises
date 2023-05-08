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
    TestRandom m_test;
    BlockAnalisys blk(1000000,100);

    blk.Run(m_test);

    return 0;
}


TestRandom::TestRandom(void):nsam{0},nblk{0}{
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
    }

    //Open output files
    Ave.open("output_ave.dat");
    Var.open("output_var.dat");
    Chi.open("output_chi2.dat");
	Numb.open("output_numb.dat");
}

//Generate random number
void TestRandom::Run(void){
    number.push_back(rnd.Rannyu());
    Numb<<number[nsam]<<std::endl;
    nsam++;
}

//Update the averages in the block
void TestRandom::Accumulate(void){
    walker(0)+=1./static_cast<double>(nsam)*(number[nsam-1]-walker(0));
    walker(1)+=1./static_cast<double>(nsam)*(std::pow(number[nsam-1],2)-walker(1));
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

    //Chi2 test
    Chi2();

    //Print outputs
    Print();

    //Reset block variables
    walker.zeros();
    nsam=0;
    number.clear();
    chi2=0;
}

void TestRandom::Print(void){
    Ave<<nblk<<'\t'<<walker(0)-0.5<<'\t'<<ave(0)-0.5<<'\t'<<sqrt(1./static_cast<double>(nblk-1)*(ave2(0)-std::pow(ave(0),2)))<<std::endl;
    Var<<nblk<<'\t'<<walker(1)-(1./12.)<<'\t'<<ave(1)-(1./12.)<<'\t'<<sqrt(1./static_cast<double>(nblk-1)*(ave2(1)-std::pow(ave(1),2)))<<std::endl;
    Chi<<chi2<<std::endl;
}

void TestRandom::Chi2(void){
    double E{nsam/static_cast<double>(100)};
    vec appo{number};
    h=histc(appo,linspace(0.,1.,100+1));
    //std::cout<<h;
    for (unsigned int i=0; i<100 ; i++)
        chi2+=pow(E-h(i),2)/E;
}


/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
