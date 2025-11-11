#include "Lattice.hpp"

Lattice::Lattice(int L_) : L(L_), spins(L_, std::vector<int>(L_, 1)) {
    std::random_device rd;
    rng.seed(rd());
    uniform = std::uniform_real_distribution<double>(0.0, 1.0);
}

void Lattice::randomize() {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            spins[i][j] = (uniform(rng) < 0.5) ? -1 : 1;
        }
    }
}

void Lattice::setSpinOne() {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++) {
            spins[i][j] = 1;
        }
    }
}

int Lattice::getSpin(int i, int j) const {
    return spins[i][j];
}

void Lattice::flipSpin(int i, int j) {
    spins[i][j] *= -1;
}

int Lattice::periodic(int i, int add) const {
    return (i + L + add) % L;
}

int Lattice::neighbourSum(int i, int j) const {
    int left   = spins[periodic(i, -1)][j];
    int right  = spins[periodic(i, 1)][j];
    int up     = spins[i][periodic(j, -1)];
    int down   = spins[i][periodic(j, 1)];
    return left + right + up + down;
}