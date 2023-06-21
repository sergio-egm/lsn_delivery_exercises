#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <armadillo>

#include "random.h"

using namespace arma;


//Get points from configuration collect them
class Points{
    public:
        Points(void);
        ~Points(){;}

        //Get coordinates
        double getX(unsigned int index) const{return m_points[index](0);}
        double getY(unsigned int index) const{return m_points[index](1);}

        //Get number of points
        unsigned int size(void) const{return m_points.size();}

        //Get distance between two points
        double distance(unsigned int x1, unsigned int x2) const {return norm(m_points[x1]-m_points[x2]);}

    private:
        std::vector<vec> m_points;
};


//Single travel
class Travel{
    public:
        Travel(unsigned int n):cost{0.}
        {
            m_x=linspace<uvec>(0,n-1,n);
        }
        ~Travel(){;}

        //Chack my configuration
        void check(void) const;

        //Shuffle elements
        void shuffle (Random& in_rnd);

        //Evaluate cost functoion
        void eval(const Points& map);
    private:
        uvec m_x;
        double cost; 
};