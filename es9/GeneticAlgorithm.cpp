#include "GeneticAlgorithm.h"

int main(){
    Points map;
    Travel appo(map.size());

    appo.eval(map);

    return 0;
}

Points::Points(void){
    std::ifstream fin("config.out");
    std::vector<double> appo{0.,0.};

    if(!fin.is_open()){
        std::cerr<<"PROBLEM: config.out not found!"<<std::endl;
        exit(-404);
    }

    fin>>appo[0]>>appo[1];

    while(!fin.eof()){
        m_points.push_back(appo);
        fin>>appo[0]>>appo[1];
    }

    fin.close();
}






void Travel::check(void) const{
    uvec appo=sort(m_x);

    for (unsigned int i=0; i<m_x.n_elem ; i++){
        if (appo(i)!=i){
            std::cerr<<"PROBLEM: Not valid element!"<<std::endl;
            exit(-2);
        }
    }
}

void shuffle (Random& in_rnd){
    unsigned int x=floor(rnd.Rannyu()*m_x.size());
    unsigned int y=floor(rnd.Rannyu()*m_x.size());

    std::swap(m_x)
}


void Travel::eval(const Points& map){
    unsigned int i{0}, j{0};
    cost=0.;

    for (unsigned int k=0; k<map.size() ;k++){
        i=m_x(k%map.size());
        j=m_x((k+1)%map.size());

        cost+=map.distance(i,j);
    }
}