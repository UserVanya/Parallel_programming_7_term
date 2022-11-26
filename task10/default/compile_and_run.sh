g++ -std=c++17 -fopenmp linear-solver.cpp band-matrix.cpp non-linear-solver.cpp main.cpp -o main
OMP_NUM_THREADS=$1 ./main