/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 3 Mag 2023

Classes usefull for block average analisys

*****************************************************************
****************************************************************/

#include "BlockAnalisys.h"


BlockAnalisys::BlockAnalisys(
		unsigned int in_M,
	       	unsigned int in_N)
	:M{in_M} , N{in_N}
{
	L=M/N;
	//Check if M is a multiple of N
	if (M%N!=0){
		std::cerr<<"WARNING: ";
		std::cerr<<"The number of samples is not a multiple of block number"<<std::endl;
	}
}

//Run the simulation
void BlockAnalisys::Run(Method& simul){
	for (unsigned int i=0; i<N ;i++){
		for (unsigned int j=0; j<L ;j++){
			simul.Run();
			simul.Accumulate();
		}
		simul.Reset();
	}
}






/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
