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
#include <cmath>
#include <vector>
#include <armadillo>

#include "random.h"
#include "funzioni.h"


class FunzioneBase {
	public:
		virtual double Eval(double x) const =0;
		virtual ~FunzioneBase() {;};
};


class Coseno:public FunzioneBase{
	public:
		Coseno(){m_A=1.;m_omega=1.;m_phi=0.;};
		Coseno(double in_A , double in_omega , double in_phi):m_A(in_A),m_omega(in_omega),m_phi(in_phi){;};
		~Coseno() override {;}

		void setA(double in_A){m_A=in_A;};
		void setOmega(double in_omega){m_omega=in_omega;};
		void setPhi(double in_phi){m_phi=in_phi;};

		double getA() const {return m_A;};
		double getOmega() const {return m_omega;};
		double getPhi() const {return m_phi;};

		double Eval(double x) const override{return getA()*cos(getOmega()*x)+getPhi();};
	
	private:
		double m_A,m_omega,m_phi;
};



class MonteCarlo {
    public:
        MonteCarlo(double a, double b);
        ~MonteCarlo(){;}

        double Unif(const FunzioneBase& funct, unsigned int N);
        double Imp_Semp(const FunzioneBase& funct, unsigned int N);
        
        double error(){return m_error;}
        double value(){return m_value;}

    private:
        void check();

        double m_a, m_b;
        double m_value, m_error;
        
        Random m_rand;
};


class IScoseno:public FunzioneBase{
	public:
		IScoseno(){ m_cos.setA(M_PI*0.5);m_cos.setOmega(M_PI*0.5); m_k=2.; }
		~IScoseno() override{;}
		double Eval (double x) const override{ return m_cos.Eval(x)/(m_k*(1-x)); }

	private:
		Coseno m_cos ;
		double m_k ;
};



class Step{
	public:
		Step( double in_a=1. ): m_a{1.} { init_Rand(rnd); }
		~Step() {;}

		void discrete (arma::vec& v);
		void continous (arma::vec& v);
		
	private:
		double m_a ;
		double m_phi , m_theta ;
		Random rnd ;
};

/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
