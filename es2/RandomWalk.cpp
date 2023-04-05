/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica:...

...

*****************************************************************
****************************************************************/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "Integranda.h"
#include "funzioni.h"

using namespace arma;

int main(){
	unsigned int block=0;
	unsigned int M=10000;
	unsigned int N=100;
	unsigned int L=100;

	Step m_step;
	
	vec XLactice(3);
	vec XContinous(3);

	mat Mblock(N,2,fill::zeros);

	mat average(N,2,fill::zeros);
	mat error(N,2,fill::zeros);
	
	std::ofstream fout;

	for (unsigned int i=0; i<M ;i++){
		
		for(unsigned int j=0; j<N ;j++){
			m_step.discrete(XLactice);
			m_step.continous(XContinous);

			Mblock(j,0)+=1./static_cast<double>(i-block*L+1)*(dot(XLactice,XLactice)-Mblock(j,0));
			Mblock(j,1)+=1./static_cast<double>(i-block*L+1)*(dot(XContinous,XContinous)-Mblock(j,1));
		}

		XLactice.zeros(3);
		XContinous.zeros(3);

		if ((i+1)%100==0){
			average+=1./static_cast<double>(block+1)*(sqrt(Mblock)-average);
			error+=1./static_cast<double>(block+1)*(Mblock-error);
			block++;

			std::cout<<"Blocco "<<block<<std::endl;

			Mblock.zeros(N,2);
		}

	}

	error=sqrt(1./static_cast<double>(L)*(error-square(average)));

	fout.open("RandomWalk.dat");
	fout<<join_rows(average,error);
	fout.close();

	return 0;
}




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
