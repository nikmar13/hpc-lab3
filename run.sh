#!/bin/bash

OUTPUT_FILE="results.txt"
echo "Threads, Time" > $OUTPUT_FILE

for THREADS in 1 2 3 4 5 6 7 8
do
    export OMP_NUM_THREADS=$THREADS
    TIME=$(./main | grep "Time taken" | awk '{print $3}')
    echo "$THREADS, $TIME" >> $OUTPUT_FILE
done

cat $OUTPUT_FILE
