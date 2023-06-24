/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulation of Buffon's experiment.

*****************************************************************
****************************************************************/
#include "buffon.h"

int main(int argc,char** argv){
	//Nuber of throws/blocks
	unsigned int M, N;
	//Nidle lenght and line distance
	double L,d;
	if (Input(M,N,L,d)!=0){
		std::cout<<"PROBLEM: Input problem!"<<std::endl;
		exit(-1);
	}

	BlockAnalisys blk{M,N};
	Buffon buffon{L,d};

	blk.Run(buffon);

	return 0;
}





//Initialize data form buffon.h
int Input(unsigned int& M, unsigned int& N, double& L, double& d){
	std::ifstream fin("buffon.input");

	std::cout<<"BUFFON'S EXPERIMENT"<<std::endl;
	std::cout<<std::endl;

	if (!fin.is_open()){
		std::cerr<<"PROBLEM: File \"buffon.input\" not found!"<<std::endl;
		return -1;
	}

	
	fin>>M;
	std::cout<<"Total number of throws: "<<M<<std::endl;

	fin>>N;
	std::cout<<"Number of blocks: "<<N<<std::endl;
	std::cout<<std::endl;

	fin>>L;
	std::cout<<"Nidle lenght: "<<L<<std::endl;

	fin>>d;
	std::cout<<"Line distance: "<<d<<std::endl;
	std::cout<<std::endl;

	return 0;
}


//Return the sign of a number
int sign(double x){
	if (x>0)
		return 1;
	else if (x==0)
		return 0;
	else
		return -1;
}



//======BUFFON===EXPERIMENT========//
Buffon::Buffon(double L,double d):
	nblk{0},
	m_L{L},m_d{d},
	pi{0}, pi2{0},
	Nthr{0},Nhit{0}
{
	hit=false;

	fout.open("buffon.dat");

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


//Count the number of hits
void Buffon::Accumulate(void){
	Nhit+=hit;
	Nthr++;

	hit=false;
}


//Run the simulation
void Buffon::Run(void){
	double y1=rnd.Rannyu(-m_d/2,m_d/2);
	double y2=y1+m_L*Throw();
	
	//This part doesn't work if m_L>m_d/2
	//hit=(sign(y1)*sign(y2)<0);

	//It always works
	hit=(m_d/2.<static_cast<double>(sign(y2))*y2);
}


//Reset the averages
void Buffon::Reset(void){
	double blk_pi=2.*m_L/(m_d*static_cast<double>(Nhit/Nthr));

	Nhit=0;
	Nthr=0;
	nblk++;

	pi+=1./static_cast<double>(nblk)*(blk_pi-pi);
	pi2+=1./static_cast<double>(nblk)*(blk_pi*blk_pi-pi2);

	Print();

	//Show result
	//std::cout<<std::endl;
	//std::cout<<"\tBlock "<<nblk<<std::endl;
	//std::cout<<std::endl;
	//std::cout<<"\tPi: "<<pi<<" +/- "<<sqrt((pi2-pi*pi)/static_cast<double>(nblk-1)) <<std::endl;
	//std::cout<<std::endl;
	//std::cout<<"-------------------------------"<<std::endl;
	
}


double Buffon::Throw(void){
	double x , y;
	do{
		x=rnd.Rannyu(-1,1);
		y=rnd.Rannyu(-1,1);
	}while(x*x+y*y>1);

	return y/sqrt(x*x+y*y);
}

void Buffon::Print(void){
	double err=(nblk>1)? sqrt((pi2-pi*pi)/static_cast<double>(nblk-1)) : 0.;

	fout<<nblk<<'\t'<<pi<<'\t'<<err<<std::endl;
}


/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
