#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

int main() {
    std::vector<int> L_values = {40, 60, 80, 100};

    double T_min = 2.1;
    double T_max = 2.4;
    double dT = 0.01;

    int cycles = 100000;   // reduce for speed, increase for smoother results
    bool random_start = true;

    for (int L : L_values) {
        std::string filename = "data_output/phase_L" + std::to_string(L) + ".txt";
        std::ofstream file(filename);

        file << "# T   E/N   |M|/N   Cv/N   Chi/N\n";

        for (double T = T_min; T <= T_max + 1e-9; T += dT) {
            IsingModel model(L, 1.0, T, random_start);
            MonteCarlo mc(model, cycles);
            mc.run();

            file << std::fixed << std::setprecision(6)
                 << T << "  "
                 << mc.get_epsilon() << "  "
                 << mc.get_abs_magnetization() << "  "
                 << mc.get_Cv() << "  "
                 << mc.get_susceptibility() << "\n";
        }

        file.close();
        std::cout << "Finished L=" << L << "\n";
    }

    return 0;
}

