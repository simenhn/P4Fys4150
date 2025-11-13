#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>


int main(){

    int L = 20;
    double J = 1.0;

    double T1 = 1.0;
    double T2 = 2.4;

    int burnin = 10000; //Burnin length found to be 10^3
    int samples = 50000; //total samples 50 k. We want 40 k samples after burnin
    int bins = 200; 

    IsingModel model1(L , J , T1 , true); //we set both the function to be randomly sampled
    IsingModel model2(L , J , T2 , true);

    MonteCarlo m1(model1 , 0); //since we want histogram we can ignore cycles
    MonteCarlo m2(model2 , 0);

    auto [bins1 , prob1] = m1.energy_histogram(burnin , samples , bins);
    auto [bins2 , prob2] = m2.energy_histogram(burnin , samples , bins);
}