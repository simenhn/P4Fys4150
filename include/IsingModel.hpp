#pragma once
#include "Lattice.hpp"
#include <map>
#include <cmath>

// -----------------------------------------------------------------------------
// IsingModel class declaration
// -----------------------------------------------------------------------------
class IsingModel {
private:
    double J_;         // Interaction strength
    double beta_;      // Inverse temperature
    double E_;         // Energy
    double M_;         // Magnetization

    Lattice lattice_;  // Lattice object

    // Precomputed Boltzmann factors
    std::map<int, double> boltz_;

public:
    // Constructor
    IsingModel(int L, double J, double T, bool random = true);

    // -----------------------------------------
    // Initialization functions
    // -----------------------------------------

    // Precompute Boltzmann factors
    void initializeBoltzmann();

    // Compute initial energy and magnetization
    void computeInitialEM();

    // -----------------------------------------
    // Energy and spin manipulation functions
    // -----------------------------------------

    // Compute energy change for flipping spin at (i, j)
    double deltaE(int i, int j);

    // Flip spin at (i, j) and update E and M
    void flipSpin(int i, int j, double dE);

    // -----------------------------------------
    // Getter functions
    // -----------------------------------------
    
    double getE() const;
    double getM() const;

    double getBeta() const;
    double getTemperature() const;

    double getBoltzmann(double dE) const;

    // Wrapper functions to access lattice properties
    int getLatticeSize() const;
    int getN() const;
};
