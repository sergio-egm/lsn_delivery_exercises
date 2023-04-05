/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica:...

...

*****************************************************************
****************************************************************/
#include "Black-Scholes.h"


double Price_GBM::Eval(double t){
	double W=rnd.Gauss(0.,sqrt(t));

	return m_S0*exp( ( m_mu-0.5*m_sigma*m_sigma )*t + m_sigma*W);
}


double Price_dis::Eval(double t){
	double Z=0.;
	double delta=t/static_cast<double>(m_N);
	double S=m_S0;

	for(unsigned int i=0; i<m_N+1 ;i++){
		Z=rnd.Gauss(0,1);
		S*=exp( (m_mu-0.5*m_sigma*m_sigma)*delta + m_sigma*Z*sqrt(delta) );
	}

	return S;
}








/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
