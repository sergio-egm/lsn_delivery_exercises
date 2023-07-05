#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <armadillo>

#include "WaveFunction.h"
#include "random.h"
#include "BlockAnalisys.h"

using namespace arma;

void Input(unsigned int& nblk,
	unsigned int& nstep,
	double& delta,
	double& sigma,
	double& mu,
	unsigned int& N,
	double& T,
	double& Tmin,
	double& alpha,
    double& delta_mu,
    double& delta_sigma);

class State: public Method{
    public:
        State(double in_delta,double in_mu,double in_sigma,unsigned int nsamples,unsigned int nblk);

        ~State() override {
            fout.close();
        }
		//Update the average
		void Accumulate(void) override ;
		//Run the simulation
		void Run(void) override ;
		//Reset the averages
		void Reset(void) override ;

        //Wavefunction
        void SetMu(double in_mu){m_wf.SetMu(in_mu);}
        void SetSigma(double in_sigma){m_wf.SetSigma(in_sigma);}

        //Get Loss funtion
        double GetL(void) const{return ave;}
        double GetErr(void) const{return sqrt((ave2-ave*ave)/static_cast<double>(m_nblk-1));}


        void Print(void);

        void Restore(void);

        double Rannyu(void){ return rnd.Rannyu() ;}
    
    private:
        WaveFunction m_wf;

        unsigned int index,step,m_nblk;
        double delta;
        double ave, ave2;
        double walker;
	    double x,xnew;
        int accepted,attempted;

        Random rnd;

        std::ofstream fout;

        vec pos;
        mat ene;
};