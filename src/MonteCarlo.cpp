#include "MonteCarlo.hpp"
#include <iostream>
#include <random>
#include <cmath>

MonteCarlo::MonteCarlo(IsingModel& model_, int cycles_)
    : model(model_), cycles(cycles_) {
    int L = model_.getLatticeSize();
    N = L * L;
    beta = model.getBeta();
    E_sum = E2_sum = Mabs_sum = M2_sum = 0.0;

    // Prepare storage for Problem 5
    E_inst.resize(cycles); //the storage for the E_inst in that moment/lattice
    E_mean.resize(cycles); //storage for the mean of the lattices we have explored
}


//  Main Monte Carlo loop 
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


//  Measure energy and magnetization (accumulate sums for averages)
void MonteCarlo::measure() {
    double E = model.getE();
    double M = model.getM();

    E_sum   += E;
    E2_sum  += E * E;
    Mabs_sum+= std::fabs(M);
    M2_sum  += M * M;
}

void MonteCarlo::results() const {
    std::cout << "\n--- Monte Carlo Results ---\n";

    std::cout << "Temperature:  " << 1.0 / beta << "\n";

    std::cout << "<E>/N:        " << get_epsilon() << "\n";
    std::cout << "<|M|>/N:      " << get_abs_magnetization() << "\n";
    std::cout << "Cv/N:         " << get_Cv() << "\n";
    std::cout << "Chi/N:        " << get_susceptibility() << "\n";

    std::cout << "----------------------------\n";
}


// Computes a histogram of the energy per spin after burn-in cycles
std::pair<std::vector<double>, std::vector<double>>
MonteCarlo::energy_histogram(int burnin_cycles, int n_samples, int bins) {

    std::vector<int> hist(bins, 0); // We create the container for the bins
    double eps_min = -2.0; //we define the minimum and maximum value
    double eps_max = 2.0;
    double bin_width = (eps_max - eps_min) / bins; //the width is dependant upon the number of bins and the range

    
    // Here we have the random number generator
    int L = model.getLatticeSize();
    std::mt19937_64 gen(std::random_device{}());
    std::uniform_int_distribution<int> randSite(0, L - 1);
    std::uniform_real_distribution<double> uniform(0.0, 1.0);

    // Here is the burnin cycles that we loop through
    for (int b = 0; b < burnin_cycles; ++b) { // we loop through the burnin cycles that we want to discard
        for (int l = 0; l < N; ++l) {
            int i = randSite(gen); // we randomly pick out the lattice which position is given as [i , j]
            int j = randSite(gen);
            double dE = model.deltaE(i, j);
            if (dE <= 0.0 || uniform(gen) < model.getBoltzmann(dE))
                model.flipSpin(i, j, dE); // if the difference is less than 0 we accept, if not we flip the spin.
        }
    }

    // Sampling after the burnin is complete
    for (int s = 0; s < n_samples; ++s) {
        for (int l = 0; l < N; ++l) {
            int i = randSite(gen); //again get the random lattice position as [i , j]
            int j = randSite(gen);
            double dE = model.deltaE(i, j);
            if (dE <= 0.0 || uniform(gen) < model.getBoltzmann(dE))
                model.flipSpin(i, j, dE); //again we sample the boltzman distribution and accept if the difference is < 0, and spin if not.
        }

        double eps = model.getE() / static_cast<double>(N); // Here we get the energy per spin
        int bin_index = static_cast<int>((eps - eps_min) / bin_width); //we sort this into a bin index,
        if (bin_index >= 0 && bin_index < bins) // this is so we don't go out of bounds
            hist[bin_index]++; //we append to the histogram the bin_index
    }

    // Normalizing the results and returning the centers , propabilities.
    double total = 0.0;
    for (int c : hist) total += c; 

    std::vector<double> probs(bins);
    std::vector<double> centers(bins);

    for (int i = 0; i < bins; ++i) {
        centers[i] = eps_min + (i + 0.5) * bin_width; // here we get the venters for the bins by going manually from the minimum
        probs[i] = hist[i] / total; //and then we extract the propabilities of the bins by dividing the bins by the total propability.
    }

    return {centers, probs};
}

double MonteCarlo::get_epsilon() const {
    return E_sum / (cycles * N);
}

double MonteCarlo::get_abs_magnetization() const {
    return Mabs_sum / (cycles * N);
}

double MonteCarlo::get_Cv() const {
    double E_mean = E_sum / cycles;
    double E2_mean = E2_sum / cycles;
    return beta * beta * (E2_mean - E_mean * E_mean) / N;
}

double MonteCarlo::get_susceptibility() const {
    double Mabs_mean = Mabs_sum / cycles;
    double M2_mean = M2_sum / cycles;
    return beta * (M2_mean - Mabs_mean * Mabs_mean) / N;
}