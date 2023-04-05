/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica:...

...

*****************************************************************
****************************************************************/
#pragma once

#include <iostream>
#include <fstream>
#include <cmath>

#include "random.h"
#include "funzioni.h"


class Price{
	public:
		Price(double in_0, double mu, double sigma):
			m_S0{in_0}, m_mu{mu}, m_sigma{sigma}{ init_Rand(rnd); }

		virtual ~Price(){;}
		virtual double Eval(double t) =0;
	protected:
		double m_S0;
		double m_mu, m_sigma;

		Random rnd;
};

class Price_GBM: public Price{
	public:
		Price_GBM(double in_0, double mu, double sigma):
			Price(in_0,mu,sigma){;}
		~Price_GBM() override {;}

		double Eval(double t) override;
};


class Price_dis: public Price{
	public:
		Price_dis(double in_0, double mu, double sigma, unsigned int N):
			Price(in_0,mu,sigma), m_N{N}{;}
		~Price_dis() override {;}

		double Eval(double t) override;
	private:
		unsigned int m_N ;
};



class BSmethod{
	public:
		BSmethod( double K , double T ):
			m_K{K} , m_T{T}{ ;}
		~BSmethod() {;}

		double Call(Price& S){ return std::max(0.,S.Eval(m_T)-m_K); }
		double Put(Price& S){ return std::max(0.,m_K-S.Eval(m_T)); }
	private:
		double m_K, m_T;
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
