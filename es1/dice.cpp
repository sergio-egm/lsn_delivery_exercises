/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Usa il metodo dell'inversiobne per l'estrazione di numeri

*****************************************************************
****************************************************************/
#include <iostream>
#include <fstream>
#include <vector>

#include "funzioni.h"
#include "random.h"
#include "dice.h"

double M;	//Numero di estrazioni
Random rnd;	//Generatore di numeri casuali

void Input(void);	//Inizializza le variabili

int main(){
	init_rand(rnd);

	//Numero di blocchi
	std::vector<unsigned int> N{1,2,10,100};

	for (unsigned int i=0; i<4 ;i++){
		print_std(rnd,N[i],M);
		print_exp(rnd,N[i],M);
		print_ltz(rnd,N[i],M);
	}


	//Coding with class
	Constants m_const;
	Block m_blk;
	Gaussian m_gauss(m_const.get_mu(),m_const.get_sigma());
	Standard m_standard(m_const.get_min(),m_const.get_max());

	m_blk.Analize(m_standard);

	return 0;
}

void Input(void){
	std::ifstream fin("input.dat");

	if(!fin.is_open()){
		std::cerr<<"File \"input.dat\" non trovato!"<<std::endl;
		exit(-1);
	}

	fin>>M;

	fin.close();
}


Dice::Dice(void):dim{10000}{
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
        	m_rnd.SetRandom(seed,p1,p2);
        	}
      	}
	input.close();
    }
}

//Analize different block size for different dices
void Block::Analize(const Dice& in_dice) const{
	double ave{0.};		//Average
	unsigned int nblk;	//Nuber of block
	std::ofstream fout;
	std::string file_name;

	for(unsigned int i=0; i<N.size() ;i++){
		nblk=in_dice.get_dimension()/N[i];

		//Open output file
		file_name=in_dice.get_name()+std::to_string(N[i])+suffix;
		fout.open(file_name);

		//Block analisys
		for(unsigned int j=0; j<nblk ;j++){
			for(unsigned int k=0; k<N[i] ;k++)
				ave+=1./static_cast<double>(k+1)*(in_dice.get_number(j*N[i]+k)-ave);
			
			fout<<ave<<std::endl;
			ave=0.;
		}

		fout.close();
	}
}

//Constants
Constants::Constants(void){
	std::ifstream fin("dice.input");

	if(!fin.is_open()){
		std::cerr<<"PROBLEM: dice.input is not open!"<<std::endl;
		exit(-1);
	}

	fin>>min_unif;
	fin>>max_unif;
	fin>>mu_gauss;
	fin>>sigma_gauss;

	fin.close();
}

//Initialize Gaussian extraction
Gaussian::Gaussian(double in_mu,double in_sigma):
	Dice(),
	m_mu{in_mu},
	m_sigma{in_sigma}
{
	Fill();
}

//Fill the extracted vector with random number form gaussian distribution
void Gaussian::Fill(void){
	extraction.clear();

	for(unsigned int i=0; i<dim ;i++)
		extraction.push_back(m_rnd.Gauss(m_mu,m_sigma));
}

//Initialize uniform extraction
Standard::Standard(double in_min,double in_max):
	Dice(),
	m_min{in_min},
	m_range{in_max-in_min}
{
	Fill();
	name="standard_";
}

//Fill the extracted vector with random number form uniform distribution
void Standard::Fill(void){
	extraction.clear();

	for(unsigned int i=0; i<dim ;i++)
		extraction.push_back(m_min+m_range*m_rnd.Rannyu());
}

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
