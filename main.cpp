#include "MonteCarlo.h"
#include "IsingModel.h"
#include <iostream>
#include <iomanip>

int main() {
    {
        int L = 2;          // lattice size (use 2x2 for validation)
        double J = 1.0;     // coupling constant
        double T = 1.0;     // temperature in units of J/k_B
        int cycles = 1000000;  // number of Monte Carlo cycles

        IsingModel model(L, J, T, true);

        MonteCarlo mc(model, cycles);
        mc.run();
        mc.results();
        
    }


    return 0;
}