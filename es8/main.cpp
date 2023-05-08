#include "main.h"

int main(){
	Input data;

	for (unsigned int i=0; i<data.nblk ; i++){
		for (unsigned int j=0; j<data.nstep ; j++){
			data.Move();
			data.Accumulate();
		}
		data.Reset();
	}

	return 0;
}




Input::Input(void){
	//Get input for random class
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

	std::ifstream fin("input.dat");
	if(!fin.is_open()){
		std::cerr<<"PROBLEM: input.dat not found!"<<std::endl;
		exit(-100);
	}

	//Get input data form file
	fin>>mu;
	fin>>sigma;
	fin>>delta;
	fin>>nblk;
	fin>>nstep;
	
	psi.SetMu(mu);
	psi.SetSigma(sigma);
	fout.open(("output.dat"));
}


void Input::Move(void){
	double xnew{x+delta*(rnd.Rannyu()-0.5)};

	if (rnd.Rannyu()<std::min(1.,pow((psi.Eval(xnew)/psi.Eval(x)),2))){
		x=xnew;
		accepted++;
	}
	attempted++;
}


void Input::Accumulate(void){
	walker+=1./static_cast<double>(attempted)*(psi.Eval(x)-walker);
}


void Input::Reset(void){
	index++;
	ave+=1./static_cast<double>(index)*(walker-ave);
	ave2+=1./static_cast<double>(index)*(walker*walker-ave2);

	fout<<index<<'\t'<<walker<<'\t'<<ave<<'\t'<<std::sqrt((ave2-ave*ave)/static_cast<double>(index-1))<<std::endl;

	walker=0;

	std::cout<<"Num= "<<index<<std::endl;
	std::cout<<"Acceptance= "<<accepted/static_cast<double>(attempted)<<std::endl;
	accepted=0;
	attempted=0;
	std::cout<<std::endl;
}