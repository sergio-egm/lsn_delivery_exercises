#include<iostream>
#include<fstream>

int main(){
    double conta=0;
    double appo;
    std::ifstream fin("output_numb.dat");

    for(int i=0; !fin.eof() ;i++){
        fin>>appo;
        if(appo!=0){
            conta++;
            std::cout<<appo<<'\t'<<i<<std::endl;
        }
    }

    std::cout<<std::endl<<conta<<std::endl;
    return 0;
}