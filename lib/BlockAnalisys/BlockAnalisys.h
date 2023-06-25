/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Use the method of block average to analize data.

*****************************************************************
****************************************************************/
#include <iostream>
#include <fstream>

//Virtual class of a system
class Method{
	public:
		virtual ~Method(){;}
		//Update the average
		virtual void Accumulate(void) = 0 ;
		//Run the simulation
		virtual void Run(void) = 0 ;
		//Reset the averages
		virtual void Reset(void) = 0 ;
};


//Block average analisys
class BlockAnalisys{
	public:
		//Initialize with number of smaples M and block dimention N
		BlockAnalisys(unsigned int in_M, unsigned int in_N);
		~BlockAnalisys(){;}
		//Run the simulation
		void Run(Method& simul);
	protected:
		//Number of samples, block  dimention
		unsigned int M, L;
		//Number of block 
		unsigned int N;
};





/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
