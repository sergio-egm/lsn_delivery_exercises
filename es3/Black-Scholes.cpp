/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulation of european price option and comparison with Black 
Scholes analitical results.

*****************************************************************
****************************************************************/
#include "Black-Scholes.h"

int main(int argc, char** argv){
	unsigned int M, N;
	unsigned nstep;

	double S0;
	double T, K;
	double r, sigma;

	std::ifstream fin("Black-Scholes.input");

	if(!fin.is_open()){
		std::cerr<<"PROBLEM: File Black-Sholes.input not found"<<std::endl;
		exit(-1);
	}

	std::cout<<"PLAIN VANILLA PRICING OPTION"<<std::endl;
	std::cout<<std::endl;

	std::cout<<"Input data:"<<std::endl;
	std::cout<<std::endl;

	fin>>M>>N;
	std::cout<<"- Number of samples: "<<M<<std::endl;
	std::cout<<"- Number of blocks: "<<N<<std::endl;
	std::cout<<std::endl;

	fin>>S0;
	std::cout<<"- Initial price: "<<S0<<std::endl;
	fin>>T>>K;
	std::cout<<"- Delivery time: "<<T<<std::endl;
	std::cout<<"- Strike price: "<<K<<std::endl;
	fin>>r>>sigma;
	std::cout<<"- Risk-free interest rate:"<<std::endl;
	std::cout<<"- Volatility:"<<std::endl;
	std::cout<<std::endl;

	fin>>nstep;
	std::cout<<"- Number of time steps: "<<nstep<<std::endl;

	
	
	
	BlackScholes myBS(S0, T, K , r, sigma, nstep);
	BlockAnalisys m_blk(M,N);

	m_blk.Run(myBS);


	return 0;
}








//==========================PRICE==============================//
double Price_GBM::Eval(double t,Random& rnd){
	double W=rnd.Gauss(0.,sqrt(t));

	return m_S0*exp( ( m_mu-0.5*m_sigma*m_sigma )*t + m_sigma*W);
}


double Price_dis::Eval(double t, Random& rnd){
	double Z=0.;
	double delta=t/static_cast<double>(m_N);
	double S=m_S0;

	for(unsigned int i=0; i<m_N+1 ;i++){
		Z=rnd.Gauss(0,1);
		S*=exp( (m_mu-0.5*m_sigma*m_sigma)*delta + m_sigma*Z*sqrt(delta) );
	}

	return S;
}

//================================OPTION================================//
Option::Option( double K , double T ):
	m_K{K}, m_T{T}
{
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


//==============================BLACK====SHOLES=============================//
BlackScholes::BlackScholes(double S0,
	double T, double K ,
	double r, double sigma,
	unsigned int in_nstep):
	nblk{0},index{0},
	m_cons{exp(-r*T)},
	m_option{K,T},
	m_GBM{S0,r,sigma}, m_dis{S0,r,sigma,in_nstep},
	price{4,fill::zeros}, blk{4,fill::zeros},
	ave{4,fill::zeros}, ave2{4,fill::zeros},
	err{4,fill::zeros}
{
	fout.open("Black-Scholes.dat");
}




//Update averages
void BlackScholes::Accumulate(void){
	index++;

	blk+=1./static_cast<double>(index)*(price-blk);
}


//Run the simulation
void BlackScholes::Run(void){
	price(0)=m_option.Call(m_GBM);
	price(1)=m_option.Put(m_GBM);
	price(2)=m_option.Call(m_dis);
	price(3)=m_option.Put(m_dis);
}



//Restet the counters
void BlackScholes::Reset(void){
	nblk++;

	ave+=1./static_cast<double>(nblk)*(m_cons*blk-ave);
	ave2+=1./static_cast<double>(nblk)*(square(m_cons*blk)-ave2);

	err=(nblk>1)? sqrt(1./static_cast<double>(nblk-1)*(ave2-square(ave))) : rowvec{4,fill::zeros} ;

	blk.zeros();
	index=0;

	Print();

	
	std::cout<<std::endl;
	std::cout<<"Block "<<nblk<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Averages: "<<ave;
	std::cout<<"Errors:   "<<err;
	std::cout<<std::endl;
	std::cout<<"-----------------------------------"<<std::endl;
}


void BlackScholes::Print(void){
	fout<<join_rows(ave,err);
}







/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
