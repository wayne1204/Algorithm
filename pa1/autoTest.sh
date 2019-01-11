#!/bin/bash
mkdir -p log/
rm log/*
for exe in mergeSort heapSort quickSort insertionSort
do
    echo "Testing $exe"
    for i in {1..4}
    do
        echo ./${exe} ./data/case{$i}.dat
        ./${exe} ./data/case${i}.dat ./log/${exe}_$i.log
    done
done
