#pragma once
#include <vector>
#include <random>

// -----------------------------------------------------------------------------
// Lattice class declaration
//   -> a 2D lattice for the Ising model
// -----------------------------------------------------------------------------
class Lattice {
private:
    int L_; // Lattice size

    // 2D vector to store spins
    std::vector<std::vector<int>> spins_; 

    // Mersenne Twister random number generator (64-bit)
    std::mt19937_64 rng_;

    // Uniform distribution [0, 1)
    std::uniform_real_distribution<double> uniform_;

public:
    // Constructor
    Lattice(int L);

    // -----------------------------------------
    // Initialization functions
    // -----------------------------------------

    // Randomly initialize the lattice spins to +1 or -1
    void randomize();

    // Initialize all spins to +1
    void setSpinOne();

    // -----------------------------------------
    // Spin manipulation functions
    // -----------------------------------------

    // Flip the spin at position (i, j)
    void flipSpin(int i, int j);

    // -----------------------------------------
    // Getter functions
    // -----------------------------------------

    // Get lattice size
    int getSize() const;

    // Get total number of spins (N = L * L)
    int getN() const;

    // Get the spin at position (i, j)
    int getSpin(int i, int j) const;

    // Get the sum of the neighboring spins of position (i, j)
    int neighbourSum(int i, int j) const;

    // Get the periodic boundary condition for the lattice
    int periodic(int i, int add) const;
};
