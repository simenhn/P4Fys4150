#include "MonteCarlo.hpp"
#include "IsingModel.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <filesystem>

// helper function to write the histograms to file so we can plot
void write_histogram_to_file(const std::string& filename, const std::vector<double>& bins, const std::vector<double>& probs){
    std::ofstream out(filename); //take the input of the filename
    for (size_t i = 0; i < bins.size(); ++i) { // Write out all the bins
        out << bins[i] << " " << probs[i] << "\n"; // The file will now contain bins , propabilities which we can easily plot.
    }

    out.close(); // Close the file.
}



int main(){

    /*
    Here we start by defining the physical system with the lattice and the IsingModel, we want to simulate.
    */
    int L = 20; 
    double J = 1.0;

    double T1 = 1.0;
    double T2 = 2.4;

    int burnin1 = 7000; //Burnin length for the model1 found from the burnin_cycle... figs
    int burnin2 = 10000; //Burnin length for the model2 found from the burning_cycle... figs
    int samples = 50000; //total samples 50 k after the burnin
    int bins = 200; //we want to create 200 bins for the range -2 , 2

    IsingModel model1(L , J , T1 , true); //we set both the function to be randomly sampled
    IsingModel model2(L , J , T2 , true);

    MonteCarlo m1(model1 , 0); //since we want histogram we can ignore cycles
    MonteCarlo m2(model2 , 0);

    // We paired the bina and propb's inside the MonteCarlo class so that we can easily extract them as this:
    //We add in printout comments to know the simulations were successfull.
    std::cout << "Running model 1 histogram calculation" << std::endl;
    auto [bins1 , prob1] = m1.energy_histogram(burnin1 , samples , bins); 
    std::cout << "Rnning model 2 histogram calculation" << std::endl;
    auto [bins2 , prob2] = m2.energy_histogram(burnin2 , samples , bins);
    std::cout << "Histograms sucessfully calculated" << std::endl;

    write_histogram_to_file("data_output/energy_hist_T1.txt", bins1, prob1); //we call upon our helper function to write out the file that we have defined.
    write_histogram_to_file("data_output/energy_hist_T24.txt", bins2, prob2);
    std::cout << "Histograms sucessfully saved" << std::endl;

}