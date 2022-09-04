g++ -fopenmp main.cpp -o main
N=$1
OMP_NUM_THREADS=4 ./main $N