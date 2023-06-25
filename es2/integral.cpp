/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Calculation of integral using Monte Carlo tecniques.

*****************************************************************
****************************************************************/
#include "integral.h"

int main(){
    unsigned int M, N;

    std::ifstream fin("integral.input");

    if(!fin.is_open()){
        std::cerr<<"PROBLEM: File integral.input not found!"<<std::endl;
        exit(-1);
    }

    fin>>M>>N;

    fin.close();

    BaseFunction* m_cos=new Cos{M_PI*0.5,M_PI*0.5};
    BaseFunction* m_dist=new Dist{2.};

    MonteCarlo m_MC(m_cos,m_dist,0,1);
    BlockAnalisys m_analisys{1000000,100};

    std::cout<<"MONTE CARLO INTEGRATION"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Integration between 0 and 1 of:"<<std::endl;
    std::cout<<"f(x)=PI/2*cos(PI*x*/2)"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"\tM: "<<M<<std::endl;
    std::cout<<"\tN: "<<M<<std::endl;
    std::cout<<std::endl;

    m_analisys.Run(m_MC);

    delete m_cos;
    delete m_dist;
    
    return 0;
}


MonteCarlo::MonteCarlo(BaseFunction* func, BaseFunction* dist, double a, double b):
    m_a{a}, m_b{b},
    m_func{func},m_dist{dist},
    ave{2,fill::zeros}, ave2{2,fill::zeros},
    blk{2,fill::zeros}, f{2,fill::zeros},
    nblk{0}, index{0}
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

    unif.open("uniform.dat");
    imse.open("importance.dat");
}


//Update the average
void MonteCarlo::Accumulate (void){
    index++;
    blk+=1./static_cast<double>(index)*(f-blk);
}



//Run the simulation
void MonteCarlo::Run(void){
    //std::cout<<"OK";
    double x;
    f(0)=m_func->Eval(rnd.Rannyu(m_a,m_b));
    x=1-sqrt(1-rnd.Rannyu());
    f(1)=m_func->Eval(x)/m_dist->Eval(x);
}


//Reset the averages
void MonteCarlo::Reset(void){
    nblk++;

    ave+=1./static_cast<double>(nblk)*(blk-ave);
    ave2+=1./static_cast<double>(nblk)*(square(blk)-ave2);

    Print();

    //std::cout<<"Block "<<nblk<<std::endl;
    //std::cout<<std::endl;
    //std::cout<<"Block averages"<<std::endl;
    //std::cout<<"\tUniform: "<<blk(0)<<std::endl;
    //std::cout<<"\tImp Semp: "<<blk(1)<<std::endl;
    //std::cout<<std::endl;
    //std::cout<<"General averages"<<std::endl;
    //std::cout<<"\tUniform: "<<blk(0)<<std::endl;
    //std::cout<<"\tImp Semp: "<<blk(1)<<std::endl;
    //std::cout<<std::endl;
    //std::cout<<"-----------------------------------"<<std::endl;
    //std::cout<<std::endl;

    index=0;
    blk.zeros();
}

void MonteCarlo::Print(void){
    double err=(nblk>1)? sqrt(1./static_cast<double>(nblk-1)*(ave2(0)-ave(0)*ave(0))) : 0;
    unif<<nblk<<'\t'<<blk(0)-1<<'\t'<<ave(0)-1<<'\t'<<err<<std::endl;

    err=(nblk>1)? sqrt(1./static_cast<double>(nblk-1)*(ave2(1)-ave(1)*ave(1))) : 0;
    imse<<nblk<<'\t'<<blk(0)-1<<'\t'<<ave(1)-1<<'\t'<<err<<std::endl;
}



/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/