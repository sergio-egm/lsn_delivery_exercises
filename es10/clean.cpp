#include <iostream>
#include <fstream>
#include <sstream>

#include <string.h>
#include <vector>

#include <armadillo>

using namespace std;
using namespace arma;

int main(){
    ifstream fin("American_capitals.dat");

    if(!fin.is_open()){
        cout<<"Not open"<<endl;
        exit(-1);
    }

    string line,word,num1,num2;
    mat pippo{50,2,fill::zeros};
    unsigned int count{0};
    istringstream iss;

    while(getline(fin,line)){
        iss.str(line);
        while(iss>>word){
            num2=num1;
            num1=word;
        }

        if(count>0){
            pippo(count-1,0)=stod(num2);
            pippo(count-1,1)=stod(num1);
        }
        count++;
        iss.clear();
    }

    cout<<pippo<<endl;

    return 0;
}