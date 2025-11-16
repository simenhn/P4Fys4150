#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>


// Main program to run Monte Carlo simulations of the Ising model
int main(){

    namespace fs = std::filesystem; // Use filesystem namespace for directory operations
    fs::create_directory("data_output"); // Create output directory if it doesn't exist

    int L = 20;        // Lattice size
    double J = 1.0;    // Coupling constant
    double T1 = 1.0;   // First temperature
    double T2 = 2.4;   // Second temperature

    // Create Ising models with different temperatures and initial states
    IsingModel model1(L , J , T1 , true);   // Random initial state, T1
    IsingModel model2(L, J , T1 , false);   // Ordered initial state, T1
    IsingModel model3(L , J , T2 , true);   // Random initial state, T2
    IsingModel model4(L , J , T2 , false);  // Ordered initial state, T2

    // Monte Carlo simulations for each model (50000 cycles)
    MonteCarlo mc1(model1, 50000);
    MonteCarlo mc2(model2, 50000);
    MonteCarlo mc3(model3, 50000);
    MonteCarlo mc4(model4, 50000);

    // Run simulation for T=1.0, random initial state
    std::cout << "Running T=1.0 random..." << std::endl;
    mc1.run();
    const auto& E_inst1 = mc1.getEInst();   // Instantaneous energies
    const auto& E_mean1 = mc1.getEMean();   // Mean energies
    std::ofstream f1("data_output/energy_T1_random.txt"); // We efine the output where we want to write to
    for (int i = 0; i < 50000; ++i){
        f1 << i << " " << E_inst1[i] << " " << E_mean1[i] << "\n"; // Define the dataset
    }
    f1.close(); //close the file so that we can open a new one and write to it.

    // Run simulation for T=1.0, ordered initial state
    std::cout << "Running T=1.0 not-random..." << std::endl;
    mc2.run();
    const auto& E_inst2 = mc2.getEInst();
    const auto& E_mean2 = mc2.getEMean();
    std::ofstream f2("data_output/energy_T1_not-random.txt");
    for (int i = 0 ; i < 50000; ++i){
        f2 << i << " " << E_inst2[i] << " " << E_mean2[i] << std::endl;
    }
    f2.close();
    
    // Run simulation for T=2.4, random initial state
    std::cout << "Running T=2,4.0 random..." << std::endl;
    mc3.run();
    const auto& E_inst3 = mc3.getEInst();
    const auto& E_mean3 = mc3.getEMean();
    std::ofstream f3("data_output/energy_T2_random.txt");
    for (int i = 0 ; i < 50000; ++i){
        f3 << i << " " << E_inst3[i] << " " << E_mean3[i] << std::endl;
    }
    f3.close();

    // Run simulation for T=2.4, ordered initial state
    std::cout << "Running T=2,4.0 not-random..." << std::endl;
    mc4.run();
    const auto& E_inst4 = mc4.getEInst();
    const auto& E_mean4 = mc4.getEMean();
    std::ofstream f4("data_output/energy_T2_not-random.txt");
    for (int i = 0 ; i < 50000; ++i){
        f4 << i << " " << E_inst4[i] << " " << E_mean4[i] << std::endl;
    }
    f4.close();

}
