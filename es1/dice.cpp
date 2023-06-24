/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Usa il metodo dell'inversiobne per l'estrazione di numeri

*****************************************************************
****************************************************************/
#include "dice.h"

int main(){
	double a,b;
	double lambda;
	double Gamma, mu;

	std::vector<unsigned int> N{1,2,10,100};
	std::ifstream fin("dice.input");

	//Getting input data
	fin>>a>>b;
	fin>>lambda;
	fin>>Gamma>>mu;
	fin.close();

	//Output data
	std::cout<<"CENTRAL LIMIT THEOREM"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Data initialization:"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"STANDARD DICE"<<std::endl;
	std::cout<<"A: "<<a<<std::endl;
	std::cout<<"B: "<<b<<std::endl;
	std::cout<<std::endl;
	std::cout<<"EXPONENTIAL DICE"<<std::endl;
	std::cout<<"Lambda: "<<lambda<<std::endl;
	std::cout<<std::endl;
	std::cout<<"LORENTZIAN DICE"<<std::endl;
	std::cout<<"Gamma: "<<Gamma<<std::endl;
	std::cout<<"Mu: "<<mu<<std::endl;
	std::cout<<std::endl;
	
	//System class
	Dice dice;

	//Extraction kinds
	Standard std(a,b);
	Exponential exp(lambda);
	Lorentz ltz(Gamma,mu);

	for(unsigned int i=0; i<N.size() ;i++){
		std::cout<<"-------------------------------------"<<std::endl;
		std::cout<<std::endl;
		std::cout<<"\tN = "<<N[i]<<std::endl;
		std::cout<<std::endl;

		std::cout<<"\tStandard dice...";
		dice.Evol(std,N[i]);
		std::cout<<"DONE!"<<std::endl;

		std::cout<<"\tExponential dice...";
		dice.Evol(exp,N[i]);
		std::cout<<"DONE!"<<std::endl;

		std::cout<<"\tLorentzian dice...";
		dice.Evol(ltz,N[i]);
		std::cout<<"DONE!"<<std::endl;

		std::cout<<std::endl;
	}
	std::cout<<"-------------------------------------"<<std::endl;


	return 0;
}






//======DICE========//
Dice::Dice(void):
	M{10000}{
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
}


//Evolution of the sistem
void Dice::Evol(Extraction& ext, unsigned int N){
	double Sn=0;
	std::string base="dice/"+ext.get_extr();
	std::string suff=".dat";
	
	std::ofstream fout(base+std::to_string(N)+suff);

	for (unsigned int i=0; i<M ;i++){
		Sn=0;

		for (unsigned int j=0; j<N ;j++)
			Sn+=1./static_cast<double>(N)*ext.Eval(rnd);

		fout<<Sn<<std::endl;
	}
}

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
