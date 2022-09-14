g++ -fopenmp -lrt matrix.cpp main.cpp -O3 -o main

for ms in 5 10 100 500 1000
do
OMP_NUM_THREADS=8 ./main $ms
done
python3 ./plot.py