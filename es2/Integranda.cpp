/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

...

*****************************************************************
****************************************************************/
#include "Integranda.h"

MonteCarlo::MonteCarlo(double a, double b):m_a{a},m_b(b),m_value{0.},m_error{0.}{
    init_Rand(m_rand);
    check();
}

double MonteCarlo::Unif(const FunzioneBase& funct, unsigned int N){
    double x=0.;

    m_value=0.;
    m_error=0.;
    
    for (unsigned int i=0; i<N ;i++){
        x=funct.Eval(m_rand.Rannyu());
        m_value+=1./static_cast<double>(i+1)*(x-m_value);
        m_error+=1./static_cast<double>(i+1)*(x*x-m_error);
    }
    m_error-=m_value*m_value;

    return m_value;
}

double MonteCarlo::Imp_Semp(const FunzioneBase& funct, unsigned int N){
	double x=0.;

	m_value=0.;
	m_error=0.;

	for (unsigned int i=0; i<N ;i++){
		x=funct.Eval(1.-sqrt(1.-m_rand.Rannyu()));
		m_value+=1./static_cast<double>(i+1)*(x-m_value);
		m_error+=1./static_cast<double>(i+1)*(x*x-m_error);
	}
	m_error-=m_value*m_value;

	return m_value;
}
        

void MonteCarlo::check(){
    double appo=0;

    if(m_a>m_b){
        appo=m_a;
        m_a=m_b;
        m_b=appo;
    }
}



void Step::discrete (arma::vec& v){
	double appo=rnd.Rannyu(0,3);
	unsigned int n{floor(appo)};

	if (appo-static_cast<double>(n)<0.5)
		v[n]-=m_a;
	else
		v[n]+=m_a;
}

void Step::continous (arma::vec& v){
	bool not_found{true};
	double r=0;
	arma::vec appo(arma::size(v)(0),arma::fill::zeros);

	while(not_found){
		for (unsigned int i=0; i<arma::size(v)(0) ;i++)
			appo(i)=rnd.Rannyu(-1,1);
		r=arma::norm(appo);
		if (r<1)
			not_found=false;
	}

	v+=appo/r;
}


/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
