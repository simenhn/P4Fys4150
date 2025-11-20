#pragma once
#include "IsingModel.hpp"

// Struct to hold energy histogram results
struct EnergyHistogramResult {
    std::vector<double> bin_centers;
    std::vector<double> probabilities;
};

class MonteCarlo {
private:
    IsingModel& model_; // Reference to the Ising model
    int cycles_;        // Number of Monte Carlo cycles
    double E_sum;      // cumulative sum of energy
    double E2_sum;     // cumulative sum of energy squared
    double Mabs_sum;   // cumulative sum of absolute magnetization
    double M2_sum;     // cumulative sum of magnetization squared

    std::vector<double> E_inst; // stores instantaneous energy per spin each cycle
    std::vector<double> E_mean; // stores mean of energy per spin each cycle

public:
    // Constructor
    MonteCarlo(IsingModel& model, int cycles);

    // Main Monte Carlo loop
    void run();

    // Measure observables
    void measure();

    // Display results
    void results() const;

    // We also add in a EnergyHistogram that will sort the energy sampler AFTER burn-in
    EnergyHistogramResult energyHistogram(int burnin_cycles, int n_samples, int bins);

    // -----------------------------------------
    // Getter functions for observables
    // -----------------------------------------

    // Getter functions for instantaneous and mean energy per spin
    const std::vector<double>& getEInst() const;
    const std::vector<double>& getEMean() const;

    // Getter function for the number of cycles
    int getCycles() const;

    // Energy per spin
    double getEpsilon() const;

    // Absolute magnetization per spin
    double getAbsMagnetization() const;

    // Specific heat per spin
    double getCv() const;

    // Magnetic susceptibility per spin
    double getSusceptibility() const;

};
