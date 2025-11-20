# ================================
#   COMPILER SETTINGS
# ================================
CXX = g++
CXXFLAGS = -std=c++17 -O0 -g -Wall -Iinclude

# ================================
#   DIRECTORY STRUCTURE
# ================================
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# ================================
#   SOURCE FILES
# ================================
# All .cpp files in src/
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files in obj/
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# ================================
# PROGRAMS (executables)
# ================================
PROGRAMS = \
	validation_2x2 \
	hist_distribution \
	monte_carlo_vs_spins \
	parallel_tests

# ================================
# DEFAULT TARGET
# ================================
all: dirs $(PROGRAMS)

# ================================
# BUILD RULES FOR EACH PROGRAM
# ================================
validation_2x2: $(OBJ_DIR)/validation_2x2.o $(OBJ_DIR)/IsingModel.o $(OBJ_DIR)/MonteCarlo.o $(OBJ_DIR)/Lattice.o
	$(CXX) $^ -o $(BIN_DIR)/$@

hist_distribution: $(OBJ_DIR)/hist_distribution.o $(OBJ_DIR)/IsingModel.o $(OBJ_DIR)/MonteCarlo.o $(OBJ_DIR)/Lattice.o
	$(CXX) $^ -o $(BIN_DIR)/$@

monte_carlo_vs_spins: $(OBJ_DIR)/monte_carlo_vs_spins.o $(OBJ_DIR)/IsingModel.o $(OBJ_DIR)/MonteCarlo.o $(OBJ_DIR)/Lattice.o
	$(CXX) $^ -o $(BIN_DIR)/$@

parallel_tests: $(OBJ_DIR)/parallel_tests.o $(OBJ_DIR)/IsingModel.o $(OBJ_DIR)/MonteCarlo.o $(OBJ_DIR)/Lattice.o
	$(CXX) $^ -o $(BIN_DIR)/$@

# ================================
# SHORTCUTS
# ================================
run_validation: validation_2x2
	./bin/validation_2x2

run_hist: hist_distribution
	./bin/hist_distribution

run_spins: monte_carlo_vs_spins
	./bin/monte_carlo_vs_spins

run_parallel: parallel_tests
	./bin/parallel_tests

# ================================
# GENERIC RULE FOR COMPILING .cpp TO .o
# ================================
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ================================
# CREATE DIRECTORIES
# ================================
dirs:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# ================================
# CLEAN COMMAND
# ================================
clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/*

# ================================
# DEBUG PRINT
# ================================
print:
	@echo "Sources: $(SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Programs: $(PROGRAMS)"
