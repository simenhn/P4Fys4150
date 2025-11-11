#include "IsingModel.h"
#include <iostream>
#include <cmath>

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
IsingModel::IsingModel(int L_, double J_, double T_, bool random)
    : L(L_), J(J_), T(T_), beta(1.0 / T_), lattice(L_) {
    if (random) {
        lattice.randomize();
    }
    initializeBoltzmann();
    computeInitialEM();
}

// -----------------------------------------------------------------------------
// Precompute Boltzmann factors for ΔE = ±4J, ±8J, 0
// -----------------------------------------------------------------------------
void IsingModel::initializeBoltzmann() {
    boltz[8]  = exp(-beta * 8 * J);
    boltz[4]  = exp(-beta * 4 * J);
    boltz[0]  = 1.0;
    boltz[-4] = exp(beta * 4 * J);
    boltz[-8] = exp(beta * 8 * J);
}

// -----------------------------------------------------------------------------
// Compute total system energy and magnetization
// -----------------------------------------------------------------------------
void IsingModel::computeInitialEM() {
    E = 0.0;
    M = 0.0;

    for (int i = 0; i < L; ++i) {
        for (int j = 0; j < L; ++j) {
            int s = lattice.getSpin(i, j);
            M += s;

            // Count only right and down neighbors to avoid double counting
            E -= J * s * (
                lattice.getSpin(lattice.periodic(i, 1), j) +
                lattice.getSpin(i, lattice.periodic(j, 1))
            );
        }
    }
}

// -----------------------------------------------------------------------------
// Compute ΔE when flipping spin (i, j)
// -----------------------------------------------------------------------------
double IsingModel::deltaE(int i, int j) {
    int s = lattice.getSpin(i, j);
    int sumNeighbours = lattice.neighbourSum(i, j);
    double dE = 2.0 * J * s * sumNeighbours;
    return dE;
}

// -----------------------------------------------------------------------------
// Flip spin and update total energy and magnetization
// -----------------------------------------------------------------------------
void IsingModel::flipSpin(int i, int j, double dE) {
    lattice.flipSpin(i, j);
    E += dE;
    M += 2 * lattice.getSpin(i, j);
}

// -----------------------------------------------------------------------------
// Getter functions
// -----------------------------------------------------------------------------
//double IsingModel::getE() const { return E; }
//double IsingModel::getM() const { return M; }
//double IsingModel::getBeta() const { return beta; }
//int IsingModel::getLatticeSize() const { return L; }
//Lattice& IsingModel::getLattice() { return lattice; }