#include "IsingModel.hpp"
#include <iostream>
#include <cmath>

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
IsingModel::IsingModel(int L, double J, double T, bool random)
    : J_(J), beta_(1.0 / T), lattice_(L) {
    
    // Lattice initialization
    if (random) lattice_.randomize();   // Random initialization
    else        lattice_.setSpinOne();  // All spins +1

    // Parameter initialization
    initializeBoltzmann();
    computeInitialEM();
}

// -----------------------------------------------------------------------------
// Precompute Boltzmann factors for ΔE = ±4J, ±8J, 0
// -----------------------------------------------------------------------------
void IsingModel::initializeBoltzmann() {
    boltz_[8]  = exp(-beta_ * 8 * J_);
    boltz_[4]  = exp(-beta_ * 4 * J_);
    boltz_[0]  = 1.0;
    boltz_[-4] = exp(beta_ * 4 * J_);
    boltz_[-8] = exp(beta_ * 8 * J_);
}

// -----------------------------------------------------------------------------
// Compute total system energy and magnetization
// -----------------------------------------------------------------------------
void IsingModel::computeInitialEM() {
    E_ = M_ = 0.0; // Initialize energy and magnetization

    for (int i = 0; i < lattice_.getSize(); ++i) {
        for (int j = 0; j < lattice_.getSize(); ++j) {
            int s = lattice_.getSpin(i, j);
            M_ += s;

            // Count only right and down neighbors to avoid double counting
            E_ -= J_ * s * (
                lattice_.getSpin(lattice_.periodic(i, 1), j) +
                lattice_.getSpin(i, lattice_.periodic(j, 1))
            );
        }
    }
}

// -----------------------------------------------------------------------------
// Compute ΔE when flipping spin (i, j)
// -----------------------------------------------------------------------------
double IsingModel::deltaE(int i, int j) {
    int s = lattice_.getSpin(i, j);
    int sumNeighbours = lattice_.neighbourSum(i, j);
    double dE = 2.0 * J_ * s * sumNeighbours;
    return dE;
}

// -----------------------------------------------------------------------------
// Flip spin and update total energy and magnetization
// -----------------------------------------------------------------------------
void IsingModel::flipSpin(int i, int j, double dE) {
    lattice_.flipSpin(i, j);
    E_ += dE;
    M_ += 2 * lattice_.getSpin(i, j);
}

// -----------------------------------------------------------------------------
// Getter functions
// -----------------------------------------------------------------------------
double IsingModel::getE() const { return E_; }
double IsingModel::getM() const { return M_; }

double IsingModel::getBeta() const { return beta_; } 
double IsingModel::getTemperature() const { return 1.0 / beta_; }

double IsingModel::getBoltzmann(double dE) const { return boltz_.at((int)dE); }

// Wrapper functions to access lattice properties (ensures encapsulation)
int IsingModel::getLatticeSize() const { return lattice_.getSize(); }
int IsingModel::getN() const { return lattice_.getN(); }
