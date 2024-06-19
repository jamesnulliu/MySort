# MySort
Inplementation of some basic sort algorithms and some simple tests.

## 1. Requirements

g++11

## 2. Implemented Algorithm
1. bubble sort (origin / stop when no swap happens / narrow the boundary / narrow the boundary in both directions)
2. insertion sort
3. selection sort
4. merge sort
5. quick sort
   - Hoare (primitive / randomly choose pivot / insertion sort)
   - Lomuto (primitive / tail recursion optimization / randomly choose pivot / handel duplicated sequence)
6. ...

## 3. Features
### 3.1. Template
Use template to generalize element type of input sequence (`_RandIt`) and comparsion method (`_Pred`).

### 3.2. Random Data Generation
Provide an integrated class for normal distribution data generation and uniform distribution data generation.

### 3.3. Data Visualizer
Provide an easy way to visualize the breif information of a sequence of data.

### 3.4. Time Counter
Provide an useful tool to record time cost of a certain block of codes.

## 4. Quick Start
### 4.1. Build the Required Libs

Run following command to build the required libs:

```bash
bash scripts/build-libs.sh
```

The generated libs should be in `./libs` directory.

### 4.2. Build the MySort

Run following command to build MySort:

```bash
bash scripts/build.sh
```

You will find a binary file in `./bin` directory.

### 4.3. Testing

Just execute the binary file and the results will be printed on the screen.