#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>


int main(){
    int L = 20;
    double J = 1.0;
    double T1 = 1.0;
    double T2 = 2.4;


    IsingModel model1(L , J , T1 , true);
    IsingModel model2(L, J , T1 , false);
    IsingModel model3(L , J , T2 , true);
    IsingModel model4(L , J , T2 , false);


    MonteCarlo mc1(model1, 50000);   // or however many cycles you want
    MonteCarlo mc2(model2, 50000);
    MonteCarlo mc3(model3, 50000);
    MonteCarlo mc4(model4, 50000);


    std::cout << "Running T=1.0 random..." << std::endl;
    mc1.run();
    const auto& E_inst1 = mc1.getEInst();
    const auto& E_mean1 = mc1.getEMean();
    std::ofstream f1("data_output/energy_T1_random.txt");
    for (int i = 0; i < 50000; ++i)
        f1 << i << " " << E_inst1[i] << " " << E_mean1[i] << "\n";
    f1.close();


    std::cout << "Running T=1.0 not-random..." << std::endl;
    mc2.run();
    const auto& E_inst2 = mc2.getEInst();
    const auto& E_mean2 = mc2.getEMean();
    std::ofstream f2("data_output/energy_T1_not-random.txt");
    for (int i = 0 ; i < 50000; ++i)
        f2 << i << "" << E_inst2[i] << "" << E_mean2[i] << std::endl;
    
    
    
    mc3.run();
    std::ofstream file("energy_vs_cycle_T2_random.txt");
    mc4.run();
    std::ofstream file("energy_vs_cycle_T2_not-random.txt");

    
}