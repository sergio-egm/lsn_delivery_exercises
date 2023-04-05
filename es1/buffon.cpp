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
#include <cmath>

#include "funzioni.h"


int main(int argc,char** argv){
	unsigned int M=1000000;
	unsigned int N=100;
	unsigned int L=0;

	double pi=0;
	double pi2=0;
	double d=2;
	double leng=1;
	double err_pi=0;

	Buffon buffon(leng,d);

	std::ofstream fout;

	
	if (argc==3){
		M=atoi(argv[1]);
		N=atoi(argv[2]);
		if (M>=N && M%N==0){
			std::cout<<"M = "<<M<<std::endl;
			std::cout<<"N = "<<N<<std::endl;
		}
		else{
			M=1000000;
			N=100;
		}
	}
	L=M/N;
	

	fout.open("buffon.dat");
	for (unsigned int i=0; i<N ;i++){
		buffon.Simula(L);

		pi+=1./static_cast<double>(i+1)*(buffon.pi()-pi);
		pi2+=1./static_cast<double>(i+1)*(buffon.pi()*buffon.pi()-pi2);
		err_pi= (i==0) ? 0 : sqrt(1./static_cast<double>(i)*(pi2-pi*pi));


		fout<<i+1<<'\t'<<pi<<'\t'<<err_pi<<std::endl;
	}
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
