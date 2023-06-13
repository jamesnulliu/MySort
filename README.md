# MySort
Inplementation of some basic sort algorithms and some simple tests.

## Requirement
Only for visual studio 2022 currently (msvc v143).  
Based on C++ 20 standard.

## Implemented Algorithm
1. bubble sort (origin / stop when no swap happens / narrow the range of iteration)
2. insertion sort
3. selection sort
4. merge sort
5. quick sort
   - Hoare (primitive / randomly choose pivot / insertion sort)
   - Lomuto (primitive / tail recursion optimization / randomly choose pivot / handel duplicated sequence)
6. ...

## Features
### 1. Template
Use template to generalize element type of input sequence (`_RandIt`) and comparsion method (`_Pred`).

### 2. Random Data Generation
Provide an integrated class for normal distribution data generation and uniform distribution data generation.

### 3. Data Visualizer
Provide an easy way to visualize the breif information of a sequence of data.

### 4. Time Counter
Provide an useful tool to record time cost of a certain block of codes.
