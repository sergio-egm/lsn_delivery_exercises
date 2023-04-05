/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

Ultima modifica:...

...

*****************************************************************
****************************************************************/
#include "funzioni.h"



void init_Rand(Random& rnd){
    int seed[4];
    int p1, p2;
    std::ifstream Primes("../random_lsn/Primes");
    if (Primes.is_open()){
        Primes >> p1 >> p2 ;
    } else std::cerr << "PROBLEM: Unable to open Primes" << std::endl;
    Primes.close();

    std::ifstream input("../random_lsn/seed.in");
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




/****************************************************************
*****************************************************************

Sergio Eligio Giovanni Manfrin
Matricola 968093

Laboratorio di Simulazione Numerica

*****************************************************************
****************************************************************/
