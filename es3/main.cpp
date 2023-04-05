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
#include <armadillo>

#include "Black-Scholes.h"

using namespace arma;

int main(int argc, char** argv){
	double M{1000}, N{100};
	double K{100.}, T{1.};
	double S0{100.};
	double mu{0.1},sigma{0.25};
	double evol{exp(-mu*T)};

	unsigned int l=0;

	Row<double> block(4,fill::zeros);
	Row<double> result(4,fill::zeros);
	Row<double> result2(4,fill::zeros);
	Row<double> appo(4);
	Row<double> error(4,fill::zeros);

	BSmethod myBS{K,T};
	Price_GBM myGBM{S0,mu,sigma};
	Price_dis my_dis{S0,mu,sigma,100};

	if (argc==3){
		M=atoi(argv[1]);
		N=atoi(argv[2]);
	}

	std::ofstream fout("BS.dat");

	for (unsigned int i=0; i<M ;i++){
		appo={myBS.Call(myGBM),myBS.Call(my_dis),myBS.Put(myGBM),myBS.Put(my_dis)};

		block+=1./static_cast<double>(i-(l*M/N)+1)*(evol*appo-block);

		if((i+1)%static_cast<unsigned int>(M/N)==0){
			l++;
			result+=1./static_cast<double>(l)*(block-result);
			result2+=1./static_cast<double>(l)*(square(block)-result2);
			block.zeros(4);
			if (l>1)
				error= sqrt(1./static_cast<double>(l-1)*(result2-square(result)));
			fout<<join_rows(result,error);
		}
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
