g++ -fopenmp -lrt experiment/matrix.cpp main.cpp -o main

OMP_NUM_THREADS=8 ./main $1