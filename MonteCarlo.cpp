#include "MonteCarlo.hpp"
#include <iostream>
#include <random>
#include <cmath>

MonteCarlo::MonteCarlo(IsingModel& model_, int cycles_)
    : model(model_), cycles(cycles_) {
    int L = model_.getLatticeSize();
    N = L * L;

    E_sum = E2_sum = Mabs_sum = M2_sum = 0.0;

    // Prepare storage for Problem 5
    E_inst.resize(cycles); //the storage for the E_inst in that moment/lattice
    E_mean.resize(cycles); //storage for the mean of the lattices we have explored
}

// -----------------------------------------------------------------------------
//  Main Monte Carlo loop 
// -----------------------------------------------------------------------------
void MonteCarlo::run() {
    int L = model.getLatticeSize();
    double beta = model.getBeta();

    // Random number generators
    std::mt19937_64 gen(std::random_device{}());
    std::uniform_int_distribution<int> randSite(0, L - 1);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);



    double cumulative_E = 0.0; // we initialize the cumulative E to be 0 in the start
    // Perform Monte Carlo cycles
    for (int cycle = 0; cycle < cycles; ++cycle) {
        // Try flipping N random spins per cycle (one sweep)
        for (int k = 0; k < N; ++k) {
            int i = randSite(gen);
            int j = randSite(gen);

            double dE = model.deltaE(i, j);


            // Metropolis acceptance test
            if (dE <= 0.0) {
                model.flipSpin(i, j, dE);
            } else {
                double r = uniform(gen);
                if (r < model.getBoltzmann(dE)) {
                    model.flipSpin(i, j, dE);
                }
            }

        }
        double E = model.getE(); //extracting the E
        cumulative_E += E/N; 
        E_inst[cycle] = E/N; 
        E_mean[cycle] = (cumulative_E / (cycle + 1)) ; //have to divide cumulative with cycle +1 to avoid division by 0.
        // Measure observables after each full sweep
        measure();
    }
}

// -----------------------------------------------------------------------------
//  Measure energy and magnetization (accumulate sums for averages)
// -----------------------------------------------------------------------------
void MonteCarlo::measure() {
    double E = model.getE();
    double M = model.getM();

    E_sum   += E;
    E2_sum  += E * E;
    Mabs_sum+= std::fabs(M);
    M2_sum  += M * M;
}

// -----------------------------------------------------------------------------
//  Compute and print final averages
// -----------------------------------------------------------------------------
void MonteCarlo::results() const {
    double beta = model.getBeta();
    double norm = 1.0 / static_cast<double>(cycles);
    double N_inv = 1.0 / static_cast<double>(N);

    double E_avg   = E_sum * norm;
    double E2_avg  = E2_sum * norm;
    double Mabs_avg= Mabs_sum * norm;
    double M2_avg  = M2_sum * norm;

    double Cv = (E2_avg - E_avg * E_avg) * beta * beta * N_inv;
    double Chi = (M2_avg - Mabs_avg * Mabs_avg) * beta * N_inv;

    std::cout << "\n--- Monte Carlo Results ---\n";
    std::cout << "Temperature:  " << 1.0 / beta << "\n";
    std::cout << "<E>/N:        " << (E_avg * N_inv) << "\n";
    std::cout << "<|M|>/N:      " << (Mabs_avg * N_inv) << "\n";
    std::cout << "Cv/N:         " << Cv << "\n";
    std::cout << "Chi/N:        " << Chi << "\n";
    std::cout << "----------------------------\n";
}