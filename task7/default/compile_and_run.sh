g++ -fopenmp isolated_area.cpp main.cpp -O1 -o main


#gdb ./main $2 $3
time OMP_NUM_THREADS=$1 ./main $2 $3

python3 ./anim.py $2 $3