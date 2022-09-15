g++ -fopenmp -lrt main.cpp -O3 -o main

OMP_NUM_THREADS=$1 ./main