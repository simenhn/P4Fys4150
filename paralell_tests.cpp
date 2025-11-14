#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>
#include <omp.h> 

// run temps in serial
void run_serial_all_temps(int L, double J, int cycles, const std::vector<double>& temps) {
    double start = omp_get_wtime();

    for (double T : temps) {
        IsingModel model(L, J, T, true);   // build model
        MonteCarlo mc(model, cycles);      // setup MC
        mc.run();                          // run simulation
    }

    double end = omp_get_wtime();
    std::cout << "Serial time: " << (end - start) << " seconds\n";
}

// run temps in parallel with OpenMP
void run_parallel_all_temps(int L, double J, int cycles, const std::vector<double>& temps) {
    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < (int)temps.size(); i++) {
        double T = temps[i];
        IsingModel model(L, J, T, true);   // per-thread model
        MonteCarlo mc(model, cycles);      // per-thread MC
        mc.run();                          // run simulation
    }

    double end = omp_get_wtime();
    std::cout << "Parallel time: " << (end - start) << " seconds\n";
}

int main() {
    int L = 20;
    double J = 1.0;
    int cycles = 50000;
    std::vector<double> temps = {1.0, 2.4, 3.0};

    std::cout << "Running serial version\n";
    run_serial_all_temps(L, J, cycles, temps);

    std::cout << "Running parallel version\n";
    run_parallel_all_temps(L, J, cycles, temps);

    return 0;
}