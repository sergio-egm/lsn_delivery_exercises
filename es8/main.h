#include <iostream>
#include <fstream>
#include <string>

#include "WaveFunction.h"
#include "random.h"

class Input{
    public:
        Input(void);
        ~Input(){;}

        void Move(void);
        void Accumulate(void);
        void Reset(void);

        Random rnd;
        unsigned int nblk, nstep;
        double mu, sigma;
        double delta;
        double ave{0.}, ave2{0.};
        double walker{0.};
	    double x{0.};
        WaveFunction psi;
        int accepted{0},attempted{0};
        int index{0};
        std::ofstream fout;
};