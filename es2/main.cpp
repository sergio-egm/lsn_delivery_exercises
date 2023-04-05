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
#include <cmath>
#include <vector>

#include "funzioni.h"
#include "Integranda.h"

int main(){
	std::vector<double> Media{0,0};
	std::vector<double>  Media2{0,0};
    std::vector<double> Error{0,0};

    Coseno cospi(M_PI*0.5,M_PI*0.5,0.);
    IScoseno is_c;
    MonteCarlo integral(0.,1.);
    double appo=0;

    std::ofstream fout[2];

    fout[0].open("Uniforme.dat");
    fout[1].open("Imp_Sampling.dat");

    for (unsigned int j=0; j<100 ; j++){
        Media[0]+=1./static_cast<double>(j+1)*(integral.Unif(cospi,10000)-Media[0]);
        Media2[0]+=1./static_cast<double>(j+1)*(integral.value()*integral.value()-Media2[0]);
    
    	appo=integral.Imp_Semp(is_c,10000);
    
    	Media[1]+=1./static_cast<double>(j+1)*(appo-Media[1]);
    	Media2[1]+=1./static_cast<double>(j+1)*(integral.value()*integral.value()-Media2[1]);

        if (j!=0){
            Error[0]=sqrt((Media2[0]-Media[0]*Media[0])/static_cast<double>(j));
            Error[1]=sqrt((Media2[1]-Media[1]*Media[1])/static_cast<double>(j));
        }

        fout[0]<<Media[0]<<'\t'<<Error[0]<<std::endl;
    	fout[1]<<Media[1]<<'\t'<<Error[1]<<std::endl;
    }

    fout[0].close();
    fout[1].close();

    return 0;
}








/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
