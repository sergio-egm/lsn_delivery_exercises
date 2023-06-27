/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Simulation of european price option and comparison with Black 
Scholes analitical results.

*****************************************************************
****************************************************************/
#include <iostream>
#include <fstream>
#include <cmath>
#include <armadillo>

#include "random.h"
#include "BlockAnalisys.h"

using namespace arma;

class Price{
	public:
		Price(double in_0, double mu, double sigma):
			m_S0{in_0},
			m_mu{mu},m_sigma{sigma}{;}

		virtual ~Price(){;}
		virtual double Eval(double t, Random& rnd) =0;
	protected:
		double m_S0;
		double m_mu, m_sigma;
};

class Price_GBM: public Price{
	public:
		Price_GBM(double in_0, double mu, double sigma):
			Price(in_0,mu,sigma){;}
		~Price_GBM() override {;}

		double Eval(double t, Random& rnd) override;
};


class Price_dis: public Price{
	public:
		Price_dis(double in_0, double mu, double sigma, unsigned int N):
			Price(in_0,mu,sigma), m_N{N}{;}
		~Price_dis() override {;}

		double Eval(double t,Random& rnd) override;
	private:
		unsigned int m_N ;
};



class Option{
	public:
		Option( double K , double T );
		~Option() {;}

		double Call(Price& S){ return std::max(0.,S.Eval(m_T, rnd)-m_K); }
		double Put(Price& S){ return std::max(0.,m_K-S.Eval(m_T, rnd)); }
	private:
		double m_K, m_T;

		Random rnd;
};


class BlackScholes: public Method{
	public:
		BlackScholes(double S0, double T, double K ,double r, double sigma, unsigned int in_nstep);
		~BlackScholes() override{fout.close();}

		//Update averages
		void Accumulate(void) override;
		//Run the simulation
		void Run(void) override;
		//Restet the counters
		void Reset(void) override;

		void Print(void);
	private:
		unsigned int nblk, index;

		double m_cons;

		Option m_option;

		Price_GBM m_GBM;
		Price_dis m_dis;

		rowvec price,blk;
		rowvec ave, ave2;
		rowvec err;

		std::ofstream fout;
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
