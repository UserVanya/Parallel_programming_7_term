g++ -fopenmp -lrt main.cpp -O3 -o main

OMP_NUM_THREADS=8 ./main $1