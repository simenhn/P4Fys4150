#pragma once
#include <vector>
#include <random>


class Lattice {
private:
    int L;
    std::vector<std::vector<int>> spins;
    std::mt19937_64 rng;
    std::uniform_real_distribution<double> uniform;

public:
    Lattice(int L);
    void randomize();
    void setSpinOne();
    int getSpin(int i, int j) const;
    void flipSpin(int i, int j);
    int neighbourSum(int i, int j) const;
    int periodic(int i, int add) const;
};