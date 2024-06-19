<div align="center">

  <h1> MySort - Benchmark Sorting Algorithms </h1>
  
  ![Static Badge](https://img.shields.io/badge/C%2B%2B-23-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/gcc-13-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/msvc-19-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/clang-18-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/cmake-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/ninja-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) [![license - Apache-2.0](https://img.shields.io/badge/license-Apache--2.0-darkgreen?style=plastic)](https://github.com/jamesnulliu/PrettyLazy0/blob/main/LICENSE)

  <img src="docs\imgs\output_example.png"></img>

</div>


## 1. Features

### 1.1. A Collection of Sorting Algorithms

We provide a collection of sorting algorithms, including:

- std::sort
- std::stable_sort
- Bubble Sort (with different optimizations)
- Insertion Sort
- Selection Sort
- Heap Sort
- Merge Sort
- Quick Sort (Hoare / Lomuto) (with different optimizations)
- PDQ Sort

### 1.2. A Benchmark Framework

We provide a benchmark framework to test the performance of the sorting algorithms. The testing framework is consists of different test patterns, which can be easily customized by users.

The framework can visualize the distribution of the test data, and compare the performance of different sorting algorithms. It is easy to extend any part of the framework by specializing the template classes.


### 1.3. Multi-Platform Support

We provide a cross-platform build system with CMake and Ninja. The project can be easily built on both UNIX-based systems and Windows, with the scripts provided in the repository.

## 2. Environment Setup

Please check [Env Setup Guide for Linux](./docs/Env_Setup_Guide_for_Linux.md) or [Env Setup Guide for Windows](./docs/Env_Setup_Guide_for_Windows.md) for more a detailed guide.

## 3. Quick Start
### 3.1. Build the Required Libs

Run following command to build the required libs:

#### UNIX-based Systems:
```bash
bash scripts/build-libs.sh
```
#### Windows:
> Note that initializing git submodules may failed on windows.  
> If you encounter any error, please use `git bash` instead.
```powershell
.\scripts\build-libs.ps1
```

The generated libs should be in `./libs` directory.

### 3.2. Build MySort

Run following command to build MySort:

#### On UNIX-based Systems:

```bash
bash scripts/build.sh
```

#### On Windows:

```powershell
.\scripts\build.ps1
```

You will find a binary file in `./bin` directory.

### 3.3. Testing

Execute the binary file and the results will be printed on the screen.


## 4. Extend the Benchmark Framework

To do...