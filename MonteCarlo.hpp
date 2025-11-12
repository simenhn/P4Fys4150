#pragma once
#include "IsingModel.hpp"

class MonteCarlo {
private:
    IsingModel& model;
    int N, cycles;
    double E_sum, E2_sum, Mabs_sum, M2_sum;
    
    std::vector<double> E_inst; // stores instantaneous energy per spin each cycle
    std::vector<double> E_mean; // stores mean of energy per spin each cycle

public:
    MonteCarlo(IsingModel& model, int cycles);
    void run();
    void measure();
    void results() const;

     /*
     Since the E_inst and E_mean are private members of the class, we need to have
     getter functions to be able to ascess them later.
     */
    const std::vector<double>& getEInst() const { return E_inst; }
    const std::vector<double>& getEMean() const { return E_mean; }
    int getCycles() const { return cycles; }

    //We also add in a EnergyHistogram that will sort the energy sampler AFTER burn-in
    void energy_histogram(int burnin_cycles , int n_samples , int bins);
};