g++ -fopenmp main.cpp -O3 -o main
N=$1
OMP_NUM_THREADS=4 ./main $N