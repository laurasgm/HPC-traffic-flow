#include <iostream>
#include <mpi.h>
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
    double mov;


    //He pensado en partir la matriz en 4 pero voy a revizar donde en la posicion siguiente
    //a i se encuentra un 1, eso no me dejara cambiar y por ende considero que es seguro cambiar de wn

    int dark = TAM/4 //divido mi matriz en 4 
    rowvec posicion;
    posicion << dark;
    //cout<<"original"<<endl;
    //cout<<a<<endl;
    int rank, size;
    int j=0;
    MPI_Status status;
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    ScopedTimer p;
    //master 0 wn1 1 wn2 2 wn3 3
    //master
    if (rank == 0){

        for (int i=0; i<TAM-1; i++){
            if (i>=dark-3 && i<dark+3){//reviso poco antes y poco despues de cada cuarto de matriz 
                if (i+1 == 1){ //si en algun momento i es 1 
                    posicion(j) << i;
                    dark+=dark; //actualizo a dark para el proximo cuarto de matriz
                    j++;
                }
            }
        }
        
        for(int i=0; i<posicion(0)-1; i++){
            if(a(i+1) == 0){
                a(i+1) = b(i);
                a(i) = b(i+1);
                mov+=1;
                b=a;
            }   
        }

        //le envio las otras 3 partes de la matriz a los wn
        MPI_Send(&posicion(1), 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&posicion(2), 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(&posicion(3), 1, MPI_INT, 3, 0, MPI_COMM_WORLD);

        cout<<posicion;
        cout<<a;

        vel=mov/TAM;
        //cout<<TAM<<","<<p.elapsed()/1e+6<<","<<vel<<endl;
    }

    MPI_Finalize();
    
}