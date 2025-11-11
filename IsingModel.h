#pragma once
#include "Lattice.h"
#include <map>
#include <cmath>

class IsingModel {
private:
    int L;
    double J, T, beta;
    double E, M;
    Lattice lattice;
    std::map<int, double> boltz;

public:
    IsingModel(int L, double J, double T, bool random = true);
    void initializeBoltzmann();
    void computeInitialEM();
    double deltaE(int i, int j);
    void flipSpin(int i, int j, double dE);

    // ---- Getter functions ----
    double getE() const { return E; }
    double getM() const { return M; }
    double getBeta() const { return beta; }
    double getBoltzmann(double dE) const { return boltz.at((int)dE); }
    int getLatticeSize() const { return L; }
    Lattice& getLattice() { return lattice; }
};