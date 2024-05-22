#!/bin/bash
#PBS -N openmp_task
#PBS -l walltime=01:00:00
#PBS -l nodes=1:ppn=8:mem=1gb

cd $PBS_O_WORKDIR

OUTPUT_FILE="results.txt"
echo "Threads, Time" > $OUTPUT_FILE

ml icc
ml openmpi
icc -o main -qopenmp main.cpp

for THREADS in 1 2 3 4 5 6 7 8
do
    export OMP_NUM_THREADS=$THREADS
    TIME=$(./main | grep "Time taken" | awk '{print $3}')
    echo "$THREADS, $TIME" >> $OUTPUT_FILE
done

cat $OUTPUT_FILE
