#pragma once
#include "IsingModel.h"

class MonteCarlo {
private:
    IsingModel& model;
    int N, cycles;
    double E_sum, E2_sum, Mabs_sum, M2_sum;

public:
    MonteCarlo(IsingModel& model, int cycles);
    void run();
    void measure();
    void results() const;
};