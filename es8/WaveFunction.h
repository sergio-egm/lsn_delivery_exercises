#pragma once

#include <iostream>
#include <cmath>

class WaveFunction{
	public:
		WaveFunction(double in_mu=0.,double in_sigma=0.):
			m_mu{in_mu},m_sigma{in_sigma}{;}
		~WaveFunction(){;}
		double Eval(double x){
			return exp(-0.5*pow((x-m_mu)/m_sigma,2))+exp(-0.5*pow((x+m_mu)/m_sigma,2));
		}
		void SetMu(double in_mu){m_mu=in_mu;}
		void SetSigma(double in_sigma){m_sigma=in_sigma;}
	private:
		double m_mu, m_sigma;
};
