#include "Lattice.hpp"

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

Lattice::Lattice(int L) : L_(L), spins_(L, std::vector<int>(L, 1)) {
    std::random_device rd; // Seed provider for random number generator
    rng_.seed(rd());       // Seed the Mersenne Twister generator
    uniform_ = std::uniform_real_distribution<double>(0.0, 1.0);
}

// -----------------------------------------------------------------------------
// Initialization functions
// -----------------------------------------------------------------------------

void Lattice::randomize() {
    for (int i = 0; i < L_; i++) {
        for (int j = 0; j < L_; j++) {
            // Randomly set spin to +1 or -1
            spins_[i][j] = (uniform_(rng_) < 0.5) ? -1 : 1;
        }
    }
}

void Lattice::setSpinOne() {
    for (int i = 0; i < L_; i++) {
        for (int j = 0; j < L_; j++) {
            // Set spin to +1
            spins_[i][j] = 1;
        }
    }
}

// -----------------------------------------------------------------------------
// Spin manipulation functions
// -----------------------------------------------------------------------------

void Lattice::flipSpin(int i, int j) {
    spins_[i][j] *= -1;
}

// -----------------------------------------------------------------------------
// Getter functions
// -----------------------------------------------------------------------------

int Lattice::getSize() const {
    return L_;
}

int Lattice::getN() const {
    return L_ * L_;
}

int Lattice::getSpin(int i, int j) const {
    return spins_[i][j];
}

int Lattice::periodic(int i, int add) const {
    return (i + L_ + add) % L_;
}

int Lattice::neighbourSum(int i, int j) const {
    int left   = spins_[periodic(i, -1)][j];
    int right  = spins_[periodic(i, 1)][j];
    int up     = spins_[i][periodic(j, -1)];
    int down   = spins_[i][periodic(j, 1)];
    return left + right + up + down;
}
