#include "main.h"

int main(){
	//Data blocking
	unsigned int nblk,nstep;
	//Variational Monte Carlo
	double mu,sigma,delta;
	double mu_new,sigma_new;
	//Simulated Aneling
	double L{0.}, Lnew,err{0.};
	double T, Tmin;
	double alpha;
	double beta;
	double delta_mu,delta_sigma;
	unsigned int N, attempted{0}, n{0};

	std::vector<double> m_L;
	std::vector<double> m_err;
	std::vector<double> m_T;
	std::vector<double> m_mu;
	std::vector<double> m_sigma;

	Input(nblk,nstep,delta,sigma,mu,N,T,Tmin,alpha,delta_mu,delta_sigma);
	BlockAnalisys blk(nblk*nstep,nblk);
	State psi(delta,mu,sigma,nblk*nstep,nblk);

	blk.Run(psi);

	L=psi.GetL();
	err=psi.GetErr();
	
	while(T>Tmin){
		n+=N;
		beta=1./T;
		attempted=0;
		while(attempted<n){
			mu_new=mu+delta_mu*(psi.Rannyu()-0.5);
			sigma_new=sigma+delta_sigma*(psi.Rannyu()-0.5);

			psi.Restore();
			psi.SetMu(mu_new);
			psi.SetSigma(sigma_new);

			std::cout<<std::endl;
			std::cout<<"T = "<<T<<std::endl;
			std::cout<<"beta(t) = "<<beta<<std::endl;
			std::cout<<std::endl;
			std::cout<<"- Mu: "<<mu_new<<std::endl;
			std::cout<<"- Sigma: "<<sigma_new<<std::endl;
			std::cout<<std::endl;

			blk.Run(psi);
			Lnew=psi.GetL();

			std::cout<<"- Lnew: "<<Lnew<<std::endl;

			//Metropolis
			if (psi.Rannyu()<exp(-beta*(Lnew-L))){
				L=Lnew;
				err=psi.GetErr();
				mu=mu_new;
				sigma=sigma_new;
			}
			attempted++;

			std::cout<<"---------------------------"<<std::endl;
			m_L.push_back(L);
			m_err.push_back(err);
			m_T.push_back(T);
			m_mu.push_back(mu);
			m_sigma.push_back(sigma);
		}
		T*=alpha;
	}

	std::cout<<std::endl;
	std::cout<<"Final values:"<<std::endl;
	std::cout<<"- Mu : "<<mu<<std::endl;
	std::cout<<"- Sigma : "<<sigma<<std::endl;
	std::cout<<std::endl;

	psi.Restore();
	psi.SetMu(mu);
	psi.SetSigma(sigma);

	blk.Run(psi);

	psi.Print();

	vec armaL{m_L};
	vec armaerr{m_err};
	vec armaT{m_T};
	std::ofstream fout("output_cost.dat");
	fout<<join_rows(armaT,armaL,armaerr);
	fout.close();

	vec armaMu{m_mu};
	vec armaSigma{m_sigma};
	fout.open("parameters.dat");
	fout<<join_rows(armaMu,armaSigma);
	fout.close();

	return 0;
}






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
    double& delta_sigma)
{
	std::ifstream fin("input.dat");
	if(!fin.is_open()){
		std::cerr<<"PROBLEM: input.dat not found!"<<std::endl;
		exit(-100);
	}

	//Get input data form file
	fin>>mu;
	fin>>sigma;
	fin>>delta;
	fin>>nblk;
	fin>>nstep;
	fin>>N;
	fin>>T;
	fin>>Tmin;
	fin>>alpha;
	fin>>delta_mu;
	fin>>delta_sigma;

	fin.close();

	std::cout<<"QUANTUM MONTE CARLO"<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Initial configuration: "<<std::endl;
	std::cout<<" - mu= "<<mu<<std::endl;
	std::cout<<" - sigma= "<<sigma<<std::endl;
	std::cout<<" - T(0)= "<<T<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Monte Carlo values"<<std::endl;
	std::cout<<" - nstep= "<<nstep<<std::endl;
	std::cout<<" - nblk= "<<nblk<<std::endl;
	std::cout<<std::endl;
	std::cout<<"Delta of Each step : "<<delta<<std::endl;
	std::cout<<"Nmax: "<<N<<std::endl;
	std::cout<<"Cooling rate: "<<alpha<<std::endl;
	std::cout<<"Lower temperature: "<<Tmin<<std::endl;
	std::cout<<std::endl;
}


State::State(double in_delta,double in_mu,double in_sigma,unsigned int nsamples,unsigned int nblk):
	m_wf{in_mu,in_sigma},
	index{0},step{0},m_nblk{nblk},
	delta{in_delta},
	ave{0},ave2{0},
	walker{0.},
	x{0.},
	accepted{0},attempted{0},
	fout{"output.dat"},
	pos{nsamples,fill::zeros},
	ene{nblk,4,fill::zeros}
{
	//Get input for random class
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


void State::Run(void){
	xnew=x+delta*(rnd.Rannyu()-0.5);

	if (rnd.Rannyu()<std::min(1.,pow((m_wf.Eval(xnew)),2)/pow((m_wf.Eval(x)),2))){
		x=xnew;
		accepted++;
	}
	pos(step++)=x;
	attempted++;
}


void State::Accumulate(void){
	walker+=1./static_cast<double>(attempted)*(m_wf.hamiltonian(x)-walker);
}


void State::Reset(void){
	index++;
	ave+=1./static_cast<double>(index)*(walker-ave);
	ave2+=1./static_cast<double>(index)*(walker*walker-ave2);

	ene(index-1,0)=index;
	ene(index-1,1)=walker;
	ene(index-1,2)=ave;
	ene(index-1,3)=std::sqrt((ave2-ave*ave)/static_cast<double>(index-1));

	walker=0;

	//std::cout<<"Num= "<<index<<std::endl;
	//std::cout<<"Acceptance= "<<accepted/static_cast<double>(attempted)<<std::endl;
	accepted=0;
	attempted=0;
	//std::cout<<std::endl;
	//std::cout<<"----------------------------------"<<std::endl;
	//std::cout<<std::endl;
}

void State::Print(void){
	std::ofstream traj("traj.dat");

	traj<<pos;

	traj.close();

	fout<<ene;
}

void State::Restore(void){
	index=0;
	step=0;

    ave=0.;
	ave2=0.;
    walker=0.;
	x=0;

    accepted=0;
	attempted=0;

	pos.zeros();
}