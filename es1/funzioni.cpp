/***************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica: 21 Apr 2023

Definizione delle funzioni.

*****************************************************************
****************************************************************/

#include "funzioni.h"


//Test funzioni
//I valori sono abbastanza vicini
bool are_close(double oss, double calc, double eps){
	return abs(oss-calc)<eps;
}

//Testo le mie funzioni
void test_function(){
	double appo=0;

	std::vector<double> r{7,8,6,9,8};

	appo=average_block(r,5,0);
	assert(are_close(appo,7.6));

	appo=rms(7.6,58.8,4);
	assert(are_close(appo,0.509901951));

	appo=var_block(r,1,0,7.6);
	assert(are_close(appo,1.019803903));
}





//Lettura dati
//Riempie un vettore con numeri generati casualente tra [0,1]
//Li salva in un file di output
void fillR(std::vector<double>& r, unsigned int throws){
	Random rnd;

	int seed[4];
	int p1, p2;


	std::ifstream Primes("../random_lsn/Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;
	Primes.close();

	std::ifstream input("../random_lsn/seed.in");
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

	std::ofstream fout("output_numb.dat");
	for(unsigned int i=0; i<throws ; i++){
    		r.push_back(rnd.Rannyu());
			fout<<r[i]<<std::endl;
	}
	fout.close();
}



//Statistica
//Media del blocco
double average_block(const std::vector<double>& r,
		unsigned int dens,
		unsigned int index){
	double ave=0;

	for(unsigned int i=0; i<dens ; i++){
		unsigned int k=index*dens+i;

		ave=1./static_cast<double>(i+1)*(r[k]-ave)+ave;
	}

	return ave;
}


//Deviazione standard
double rms(double AV, double AV2, unsigned int n){
	return (n<1)? 0 : sqrt((AV2-(AV*AV))/static_cast<double>(n));
}


//Varianza blocco
double var_block(const std::vector<double>& r,
		unsigned int dens,
		unsigned int index,
		double xTrue){
	double var=0;
	double delta=0;

	for(unsigned int i=0; i<dens ;i++){
		unsigned int k=index*dens+i;

		delta=r[k]-xTrue;
		var=1./static_cast<double>(i+1)*(delta*delta-var)+var;
	}

	return var;
}


//Test del chi2
double chi2(const std::vector<double>& r,
		unsigned int xi, unsigned int xf,
		unsigned int nBloks){
	double E=(xf-xi)/nBloks;
	double summ=0;
	
	auto start=r.begin()+xi;
	auto endv=r.begin()+xf;

	std::vector<double> appo(xf-xi);
	std::copy(start,endv,appo.begin());

	arma::vec v{appo};
	arma::uvec h = arma::histc(v,arma::linspace(0,1,nBloks+1));
	
	for (unsigned int i=0 ; i<nBloks ; i++)
		summ+=pow(E-static_cast<double>(h[i]),2)/E;
	

	

	return summ;
}



//Inizializza una classe Random
void init_rand(Random& rnd){
	int seed[4];
	int p1, p2;
	std::ifstream Primes("../random_lsn/Primes");
	if (Primes.is_open()){
		Primes >> p1 >> p2 ;
	} else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;
	Primes.close();

	std::ifstream input("../random_lsn/seed.in");
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



void print_std(Random& rnd,unsigned int n, unsigned int M){
	double Sn=0;
	std::string base="std_";
	std::string ext=".dat";
	
	std::ofstream fout(base+std::to_string(n)+ext);

	for (unsigned int i=0; i<M ;i++){
		Sn=0;

		for (unsigned int j=0; j<n ;j++)
			Sn+=1./static_cast<double>(n)*rnd.Rannyu(1,6);

		fout<<Sn<<std::endl;
	}
}


void print_exp(Random& rnd,unsigned int n, unsigned int M){
	double Sn=0;
	std::string base="exp_";
	std::string ext=".dat";
	
	std::ofstream fout(base+std::to_string(n)+ext);

	for (unsigned int i=0; i<M ;i++){
		Sn=0;

		for (unsigned int j=0; j<n ;j++)
			Sn+=1./static_cast<double>(n)*rnd.Exponential(1);

		fout<<Sn<<std::endl;
	}
}

void print_ltz(Random& rnd,unsigned int n, unsigned int M){
	double Sn=0;
	std::string base="ltz_";
	std::string ext=".dat";
	
	std::ofstream fout(base+std::to_string(n)+ext);

	for (unsigned int i=0; i<M ;i++){
		Sn=0;

		for (unsigned int j=0; j<n ;j++)
			Sn+=1./static_cast<double>(n)*rnd.Lorentz(1,0);

		fout<<Sn<<std::endl;
	}
}



//Esperimento di Buffon
double buffon_exp( Random& rnd , double leng , double d , unsigned int L ){
	double x2;
	double y1,y2;
	double dim=d/2;
	double N_hit=0;

	for (unsigned int i=0; i<L ; i++){
		y1=rnd.Rannyu(-dim,dim);
		find_buffon(x2,y2,rnd);

		y2=leng*y2+y1;

		if(sign(sign(y1)*sign(y2))<0)
			N_hit++;
	}

	return static_cast<double>(L)*2.*leng/(d*N_hit);
}


//Segno di x
int sign(double x){
	if (x==0)
		return 0;
	return (x>0)? 1 : -1 ;
}

void find_buffon(double& x, double& y, Random& rnd){
	bool not_found{true};
	double x0, y0 , r;

	while(not_found){
		x0=rnd.Rannyu(-1,1);
		y0=rnd.Rannyu(-1,1);
		r=norm(x0,y0);

		if (r<1)
			not_found=false;
	}

	x= x0/r ;
	y= y0/r ;
}


double norm(double x, double y){
	return sqrt(x*x+y*y);
}

//Inizializza la classe Buffon
Buffon::Buffon(double in_L , double in_d):
	L{in_L} , d{in_d} ,
	m_pi{0.} , m_err_pi{0.},
	y1{0.} , x2{0.} , y2{0.}{
	init_rand(rnd);
}

//Simula l'esperimento di Buffon
void Buffon::Simula(unsigned int N){
	double dim=d/2;		//Dimensione del quadrato dove cadono gli aghi
	double N_hit=0;		//Numero di volte che l'ago cade sulla linea

	for (unsigned int i=0; i<N ; i++){
		y1=rnd.Rannyu(-dim,dim);
		angle();

		y2=L*y2+y1;
		x2*=L;

		if(sign(sign(y1)*sign(y2))<0)
			N_hit++;

	}

	m_pi=2.*L/(d*N_hit)*static_cast<double>(N);
	m_err_pi=m_pi-M_PI;
}

//Genera uniformemente angoli da [0,2pi)
void Buffon::angle(){
	bool not_found{true};
	double x0, y0 , r;

	while(not_found){
		x0=rnd.Rannyu(-1,1);
		y0=rnd.Rannyu(-1,1);
		r=norm(x0,y0);

		if (r<1)
			not_found=false;
	}

	x2= x0/r ;
	y2= y0/r ;
}





/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
