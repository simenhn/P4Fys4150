# 2D Ising Model — Metropolis Monte Carlo (FYS4150 Project 4)

This project implements the two-dimensional Ising model using the Metropolis Monte Carlo algorithm in C++ (C++17).  
It includes burn-in analysis, energy distributions, finite-size phase transition behaviour, and OpenMP parallelisation.  
Python is used for plotting and post-processing.

---

## Features

- Metropolis Monte Carlo sampling
- Burn-in and equilibration analysis
- Energy time-series and running mean measurements
- Normalised histogram estimation of the energy distribution
- Finite-size phase transition study
- Parallel simulations using OpenMP
- Python scripts for plotting and data analysis
- Modular object-oriented C++ structure


## Building and Running the Project

### Build all executables
make


### Run the different simulations

Validate the analytical 2×2 case:
make run_validation

Energy histogram simulation:
make run_hist

Burn-in and equilibration analysis:
make run_spins


Parallel OpenMP benchmark:
make run_parallel


Phase-transition scan:
make run_phase

---
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
P4Fys4150/
│
├── data_output/             # Output files from simulations 
├── figs/                    # Generated plots used in the report
├── include/                 # Header files (.hpp)
├── scripts/                 # Python plotting/analysis scripts
│
├── src/                     # C++ source code implementing model + tasks
│   ├── Lattice.cpp
│   ├── IsingModel.cpp
│   ├── MonteCarlo.cpp
│   ├── energy_histogram.cpp
│   ├── phase_transitions.cpp
│   ├── parallel_tests.cpp
│   ├── burn_in.cpp
│   └── validation_2x2.cpp
│
├── Makefile
└── README.md

