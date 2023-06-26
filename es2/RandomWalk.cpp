/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulations of RWs:
- On a lactice.
- In a continous space.

*****************************************************************
****************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "RandomWalk.h"

int main(){
	unsigned int M, N;
	unsigned int L;

	double a;

	std::ifstream fin("RandomWalk.input");

	if(!fin.is_open()){
		std::cerr<<"PROBLEM: Unable to open RandomWalk.input"<<std::endl;
		exit(-1);
	}

	fin>>M>>N;
	fin>>L;
	fin>>a;

	std::cout<<"RANDOM WALK"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Input values:"<<std::endl;
	std::cout<<"- Number of samples: "<<M<<std::endl;
	std::cout<<"- Numder of blocks: "<<N<<std::endl;
	std::cout<<"- Length of a RW: "<<L<<" steps"<<std::endl;
	std::cout<<"- Length of a step: "<<a<<std::endl;
	std::cout<<std::endl;

	RandomWalk rw{a,L};
	BlockAnalisys blk{M,N};

	blk.Run(rw);

	rw.Print(N);

	return 0;
}


RandomWalk::RandomWalk(double a, unsigned int L):
	nblk{0}, index{0},
	m_L{L},
	m_a{a},
	x_c{3,fill::zeros}, x_l{3,fill::zeros},
	appo{3,fill::zeros},
	ave{2,L,fill::zeros}, ave2{2,L,fill::zeros},
	blk{2,L,fill::zeros},r2{2,L,fill::zeros}
{
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

	fout.open("RandomWalk.dat");
}


//Update the average
void RandomWalk::Accumulate(void){
	index++;
	blk+=1./static_cast<double>(index)*(r2-blk);

	r2.zeros();
	x_c.zeros();
	x_l.zeros();
}

//Run the simulation
void RandomWalk::Run(void) {
	for (unsigned int i=0; i<m_L ; i++){
		lactice();
		continous();

		r2(0,i)=cdot(x_l,x_l);
		r2(1,i)=cdot(x_c,x_c);
	}
}

//Reset the averages
void RandomWalk::Reset(void) {
	nblk++;
	ave+=1./static_cast<double>(nblk)*(sqrt(blk)-ave);
	ave2+=1./static_cast<double>(nblk)*(blk-ave2);

	std::cout<<std::endl;
	std::cout<<"Block "<<nblk<<std::endl;
	std::cout<<std::endl;
	std::cout<<"-------------------------------------"<<std::endl;

	blk.zeros();
	index=0;
}

//Print values in a file
void RandomWalk::Print(unsigned int N) {
	mat err { sqrt(1./static_cast<double>(N-1)*(ave2-square(ave))) };

	fout<<trans(join_cols(ave,err));
}


//Make a step in a continous space
void RandomWalk::continous(void){
	do{
		for (unsigned int i=0; i<3 ; i++)
			appo(i)=rnd.Rannyu(-1,1);
	}while(cdot(appo,appo)>1);

	x_c+=m_a/norm(appo)*appo;
}

//Make a step on a lactice
void RandomWalk::lactice(void){
	unsigned int i=rnd.Rannyu(0,3);
	x_l(i)+=(rnd.Rannyu()<0.5)? -m_a : m_a;
}



/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
