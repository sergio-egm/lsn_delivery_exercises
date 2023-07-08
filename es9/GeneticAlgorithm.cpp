#include "GeneticAlgorithm.h"

int main(){
    GeneticAlgorithm m_gen;

    m_gen.Run();

    return 0;
}













//==================================CITIES========================================//

//Initializate cities coordinates
Cities::Cities(void){
    double x, y;
    unsigned int index{0};

    std::cout<<"GENETIC ALGORITHM: TRAVELING SALESMAN PROBLEM"<<std::endl;
    std::cout<<std::endl;

    std::ifstream fin("config.out");

    //Find if input file si open
    if (!fin.is_open()){
        std::cerr<<"PROBLEM: File config.out not found!"<<std::endl;
        exit(-14);
    }

    //Find how many data are there
    do{
        fin>>x>>y;
        index++;
    }while(!fin.eof());
    index--;

    std::cout<<"Number of cities : "<<index<<std::endl;
    std::cout<<std::endl;

    fin.close();

    coordinates.reshape(index,2);

    //Get input form file
    fin.open("config.out");
    
    for (unsigned int i = 0 ; i<index ; i++){
        fin>>x>>y;
        coordinates(i,0)=x;
        coordinates(i,1)=y;
    }
    fin.close();
}

//Compute distace between cities
double Cities::Distance(unsigned int i, unsigned int j) const{
    return norm(coordinates.row(i)-coordinates.row(j));
}


















//=================================INDIVIDUAL==============================//

//Initializers of single individual
Individual::Individual(Random& rnd,unsigned int num):
    genies{num,fill::zeros}
{
    for (unsigned int i=0;i<num;i++)
        genies(i)=i;

    for (unsigned int t=0; t<2*num ;t++)
        shuffle(rnd);
}

Individual::Individual(vec in_vec):
    genies(in_vec)
{
    Eval();
}





//Evaluate the loss function
double Individual::Eval(void){
    L=0;
    unsigned int j,k;
    for (unsigned i=0; i<genies.n_elem ;i++){
        j=genies(i);
        k=genies((i+1)%genies.n_elem);
        L+=pow(city.Distance(j,k),2);
    }
    //check();
    return L;
}






//-------------------MUTATIONS--------------------//

//Shuffle the elements
void Individual::shuffle(Random& rnd){
    unsigned int appo{0};
    unsigned int a,b;

    a=rnd.Rannyu(1,genies.n_elem);
    b=rnd.Rannyu(1,genies.n_elem);

    appo=genies(a);
    genies(a)=genies(b);
    genies(b)=appo;

    Eval();
}

//Permutation of elements
void Individual::permutation(Random &rnd){
    unsigned int m=rnd.Rannyu(1,genies.n_elem/2);
    unsigned int x=rnd.Rannyu(1,genies.n_elem);
    unsigned int n=rnd.Rannyu(m,genies.n_elem-m);
    unsigned int j{x},k{x+n};
    unsigned int appo;

    if(k>=genies.n_elem)
        k-=genies.n_elem-1;

    for (unsigned int i=0; i<m ;i++){
        appo=genies(j);
        genies(j)=genies(k);
        genies(k)=appo;

        j++;
        k++;

        if(j==genies.n_elem)
            j=1;
        if(k==genies.n_elem)
            k=1;
    }
    Eval();
}

//Inversion
void Individual::inversion(Random& rnd){
    double appo=0.;
    unsigned int j,k;
    unsigned int x=rnd.Rannyu(1,genies.n_elem);
    unsigned int n=rnd.Rannyu(0,genies.n_elem-2);

    j=x;
    k=n+x-1;

    if(k>=genies.n_elem)
        k-=genies.n_elem-1;
    
    for(unsigned int i=0; i<n/2 ;i++){
        appo=genies(j);
        genies(j)=genies(k);
        genies(k)=appo;

        j++;
        k--;
        if(j==genies.n_elem)
            j=1;
        if(k==0)
            k=genies.n_elem-1;
    }
    Eval();
}







//Check if the values are unique and in the range
void Individual::check(void){
    vec appo=unique(genies);
    if(any(genies>city.Nelem()-1) || any(genies<0)){
        std::cerr<<"PROBLEM: Invalid value"<<std::endl;
        exit(-1);
    }
    else if(appo.n_elem!=city.Nelem()){
        std::cerr<<"PROBLEM: Not unique values"<<std::endl;
        exit(-1);
    }
}
















//================================GENETIC=====ALGORITHM===============================//


//Initializator
GeneticAlgorithm::GeneticAlgorithm(void){
    unsigned int npop;
    //Initialize random generator
    int seed[4];
    int p1, p2;
    std::ifstream Primes("Primes");
    if (Primes.is_open()){
       Primes >> p1 >> p2 ;
    } else std::cerr << "PROBLEM: Unable to open Primes" << endl;
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
    } else std::cerr << "PROBLEM: Unable to open seed.in" << endl;
    
    //Get input
    std::ifstream fin("input.dat");
    if(!fin.is_open()){
        std::cerr<<"PROBLEM: File input.dat not found"<<std::endl;
        exit(-1);
    }

    fin>>m_pc;
    fin>>m_ps;
    fin>>m_pp;
    fin>>m_pi;
    fin>>nstep;
    fin>>m_p;
    fin>>npop;

    std::cout<<std::endl;
    std::cout<<"Each generation is composed by "<<npop<<" individuals."<<std::endl;
    std::cout<<"Evaluation of "<<nstep<<" generations."<<std::endl;
    std::cout<<"p factor : "<<m_p<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Probabilities : "<<std::endl;
    std::cout<<"- Coss Over :"<<m_pc*100<<" % "<<std::endl;
    std::cout<<"- Shuffle : "<<m_ps*100<<" %"<<std::endl;
    std::cout<<"- Permutation : "<<m_pp*100<<" % "<<std::endl;
    std::cout<<std::endl;

    fin.close();

    //Initialize population vector
    for(unsigned int i=0; i<npop ;i++)
        population.push_back(Individual(rnd,city.Nelem()));
}



//Selctor operator
unsigned int GeneticAlgorithm::Select(void){
    unsigned int appo=population.size()*pow(rnd.Rannyu(),m_p);
    return appo;
}


//Crossover operator
void GeneticAlgorithm::Cross(unsigned int X1,unsigned int X2){
    unsigned int x=rnd.Rannyu(1,city.Nelem());
    unsigned int index{x};
    double appo;

    vec vec1=population[X1].GetGenies();
    vec vec2=population[X2].GetGenies();

    for(unsigned int i=0; i<city.Nelem() ;i++){
        for(unsigned int j=index; j<vec1.n_elem ;j++){
            if(population[X2](i)==vec1[j]){
                appo=vec1(j);
                vec1(j)=vec1(index);
                vec1(index)=appo;
                index++;
            }
        }
    }

    index=x;

    for(unsigned int i=0; i<city.Nelem() ;i++){
        for(unsigned int j=index; j<vec2.n_elem ;j++){
            if(population[X1](i)==vec2[j]){
                appo=vec2(j);
                vec2(j)=vec2(index);
                vec2(index)=appo;
                index++;
            }
        }
    }

    population.push_back(Individual(vec1));
    population.push_back(Individual(vec2));
}


void GeneticAlgorithm::Run(void){
    std::ofstream fout("cost.dat");

    double appo;
    unsigned int G,N,count;
    unsigned int x1,x2;

    //std::cout<<population[0].GetL()<<std::endl;

    N=population.size();


    for (unsigned int i=0; i<nstep ;i++){
        count=0;
        //Create a new generation
        while(count<N/2){
            x1=Select();
            x2=Select();
            if(rnd.Rannyu()<m_pc){
                Cross(x1,x2);
                count++;
            }
        }

        //Eliminate the old one
        population.erase(population.begin(),population.begin()+2*count);
        std::sort(population.begin(),population.end());

        //Check if the size still right
        if(population.size()!=N){
            std::cerr<<"PROBLEM: Something wrong in crossing over."<<std::endl;
            exit(-2);
        }

        //Make some mutation
        for(unsigned int j=0; j<N ;j++){
            G=Select();
            if(rnd.Rannyu()<m_ps){
            population[G].shuffle(rnd);
            std::sort(population.begin(),population.end());
            }
            if(rnd.Rannyu()<m_pp){
                population[G].permutation(rnd);
                std::sort(population.begin(),population.end());
            }
            if(rnd.Rannyu()<m_pi){
                population[G].inversion(rnd);
                std::sort(population.begin(),population.end());
            }
        }

        appo=0;

        //Output data
        std::cout<<std::endl;
        std::cout<<i+1<<" generation"<<std::endl;
        std::cout<<"Lmin : "<<population[0].GetL()<<std::endl;
        std::cout<<std::endl;
        std::cout<<"----------------------------------------------"<<std::endl;

        for(unsigned int j=0; j<population.size()/2 ;j++)
            appo+=1./static_cast<double>(j+1)*(population[j].GetL()-appo);
        fout<<i<<" "<<population[0].GetL()<<" "<<appo<<std::endl;
        
    }
    fout.close();
    
    //Print the best route
    PrintBest();
}

//Print the best route
void GeneticAlgorithm::PrintBest(void){
    std::ofstream fout("output.dat");
    unsigned int index;

    for(unsigned int i=0; i<city.Nelem() ;i++){
        index=population[0].GetGen(i);
        city.PrintCity(index,fout);
    }

    fout.close();
}