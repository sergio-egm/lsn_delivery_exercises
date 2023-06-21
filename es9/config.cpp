#include "config.h"

int main(){
    unsigned int n; //Number of cities
    bool sqr;       //Square
    std::ifstream fin("config.input");

    if (!fin.is_open()){
        std::cerr<<"PROBLEM: config.input not found!"<<std::endl;
        exit(-1);
    }

    fin>>n;
    fin>>sqr;
    
    //Initialize random generator
    Random rnd;

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

    std::cout<<"Random generation of cities"<<std::endl<<std::endl;
    std::cout<<"Number of cities: "<<n<<std::endl;
    std::cout<<"Uniform distribution ";
    if(sqr){
        std::cout<<"in a square"<<std::endl;
        square(n,rnd);
    }
    else{
        std::cout<<"on a circunferance"<<std::endl;
        circle(n,rnd);
    }

    return 0;
}





void square(unsigned int n, Random& rnd){
    std::ofstream fout("config.out");
    double x, y;

    for(unsigned int i=0; i<n ;i++){
        x=rnd.Rannyu();
        y=rnd.Rannyu();

        fout<<x<<'\t'<<y<<std::endl;
    }
}


void circle(unsigned int n, Random& rnd){
    std::ofstream fout("config.out");
    double x, y;
    double r;

    for(unsigned int i=0; i<n ;i++){
        do{
            x=2*(rnd.Rannyu()-0.5);
            y=2*(rnd.Rannyu()-0.5);

            r=std::sqrt(x*x+y*y);
        }while(r>1);

        fout<<x/r<<'\t'<<y/r<<std::endl;
    }
}