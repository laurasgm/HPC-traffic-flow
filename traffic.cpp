#include <iostream>
#include "timer.hh"
#include "armadillo"

using namespace std;
using namespace arma;

//g++ -o traffic traffic.cpp -larmadillo
//./traffic 


int main(int argc, char *argv[]){

    int TAM;
    TAM = strtol(argv[1], NULL, 10);

    arma_rng::set_seed_random();
    rowvec a = randi<rowvec>(TAM, distr_param(0,1));
    rowvec b = a;

    //velocidad promedio = No de automoviles que se mueven en un tiempo / numero total de automoviles 
    float vel;
    double cont;

    //cout<<"original"<<endl;
    //cout<<a<<endl;

    ScopedTimer p;
    for(int i=0; i<TAM-1; i++){

        if(a(i+1) == 0){
            a(i+1) = b(i);
            a(i) = b(i+1);
            //cout<<"posicion"<<i<<endl;
            //cout<<a<<endl;
            cont+=1;
            b=a;
        }
        //else {cout<<"no hay movimiento de coche "<<endl;}
         
    }

    //cout<<"resultante"<<endl;
    //cout<<a<<endl;
    vel=cont/TAM;
    cout<<TAM<<","<<p.elapsed()/1e+6<<","<<vel<<endl; 
    
}