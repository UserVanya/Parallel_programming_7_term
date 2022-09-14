g++ -fopenmp -lrt experiment/matrix.cpp main.cpp -O3 -o main

OMP_NUM_THREADS=8 ./main $1