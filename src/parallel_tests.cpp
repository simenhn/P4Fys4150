#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <omp.h> 

// rFunction for running temperatures in serial
void run_serial_all_temps(int L, double J, int cycles, const std::vector<double>& temps) {
    double start = omp_get_wtime(); // start the clock of the simulation

    for (double T : temps) {
        IsingModel model(L, J, T, true);   // build model
        MonteCarlo mc(model, cycles);      // setup MC
        mc.run();                          // run simulation
    }

    double end = omp_get_wtime(); // end clock as soon as the sim is done
    std::cout << "Serial time: " << (end - start) << " seconds\n"; //write out the length of time it took
}

// run temps in parallel with OpenMP, whivh is parallelization
void run_parallel_all_temps(int L, double J, int cycles, const std::vector<double>& temps) {
    double start = omp_get_wtime(); // Start the clock of the simulation

    #pragma omp parallel for // Using different threads to parallelize the task
    for (int i = 0; i < (int)temps.size(); i++) { // define we want to paralellize the temperatures
        double T = temps[i];
        IsingModel model(L, J, T, true);   // per-thread model
        MonteCarlo mc(model, cycles);      // per-thread MC
        mc.run();                          // run simulation
    }

    double end = omp_get_wtime(); // stop the clock
    std::cout << "Parallel time: " << (end - start) << " seconds\n"; //write out the time of the sim.
}

int main() {
    //we define the structure of the physical model
    int L = 20;
    double J = 1.0;
    int cycles = 50000;
    std::vector<double> temps = {1.0, 2.4, 3.0}; //define the different temperatures we want to test.

    std::cout << "Running serial version\n";
    run_serial_all_temps(L, J, cycles, temps);

    std::cout << "Running parallel version\n";
    run_parallel_all_temps(L, J, cycles, temps);

    return 0;
}
