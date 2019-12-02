#include <iostream>
#include "armadillo"

using namespace std;
using namespace arma;


#define TAM 5

int main(int argc, char *argv[]){

  
    arma_rng::set_seed_random();
    rowvec a = randi<rowvec>(TAM, distr_param(0,1));
    rowvec b = a;
   
    cout<<"original"<<endl;
    cout<<a<<endl;

    for(int i=0; i<TAM-1; i++){

        if(a(i+1) == 0){
            a(i+1) = b(i);
            a(i) = b(i+1);
            cout<<"posicion"<<i<<endl;
            cout<<a<<endl;
            b=a;
        }else {cout<<"proximo"<<endl;}
         
    }

  
    

    
    
}