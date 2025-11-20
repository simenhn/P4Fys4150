# P4Fys4150

make with g++ main.cpp MonteCarlo.cpp IsingModel.cpp Lattice.cpp -o ising_sim -O2
run with ./ising_sim


This project implements the **2D Ising model** using the **Metropolis Monte Carlo algorithm**, including:

- Burn-in and equilibration analysis  
- Energy time-series sampling  
- Probability density estimation via histograms  
- Parallelisation with OpenMP  
- Python scripts for plotting and analysis  

All physical and numerical components are implemented in **C++17** with a modular object-oriented structure.
## **macOS (Intel / Apple Silicon)**

macOS requires manual OpenMP installation:

```bash
brew install libomp
```

## Paralellisation Benchmark
export OMP_NUM_THREADS=4        # macOS/Linux
set OMP_NUM_THREADS=4           # Windows CMD
$env:OMP_NUM_THREADS=4          # PowerShell

./parallel_sim
### Setting OpenMP Threads
export OMP_NUM_THREADS=N

### Project Structure
│
├── data_output/                  # Output files: energy sampling & histograms
│
├── figs/                         # Figures exported for the report (PDF, PNG)
│
├── Lattice.cpp
├── Lattice.hpp                   # Lattice class (periodic boundaries, spin ops)
│
├── IsingModel.cpp
├── IsingModel.hpp                # Physics: E, delta_E, M, Boltzmann weights
│
├── MonteCarlo.cpp
├── MonteCarlo.hpp                # Metropolis MCMC, burn-in, histogram routines
│
├── main.cpp                      # Basic simulation runner (Part a/b)
│
├── monte_carlo_vs_spins.cpp      # Burn-in & equilibration analysis
├── monte_carlo_vs_spins_plot.py  # Python plotting script (instant + mean energy)
│
├── hist_distribution.cpp         # Energy histogram sampling 
├── hist_distribution_plot.py     # Python plotting for histograms
│
├── paralell_tests.cpp            # Serial vs OpenMP parallel performance tests
│
├── .gitignore
└── README.md                     # This file
