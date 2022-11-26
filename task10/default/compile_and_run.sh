g++ -std=c++17 -fopenmp auxiliary.cpp linear-solver.cpp band-matrix.cpp non-linear-solver.cpp main.cpp -o main
OMP_NUM_THREADS=4 
for b in 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 1.46 1.47 1.48 1.49 1.50 1.51 1.52 1.53 1.54
do
OMP_NUM_THREADS=4 
./main $b
done
