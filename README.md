<div align="center">

  <h1> MySort -  Some Basic Sort Algos and Simple Test Patterns </h1>
  
  ![Static Badge](https://img.shields.io/badge/C%2B%2B-23-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/g%2B%2B-13-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/msvc-19-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/cmake-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/make-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/ninja-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) [![license - Apache-2.0](https://img.shields.io/badge/license-Apache--2.0-darkgreen?style=plastic)](https://github.com/jamesnulliu/PrettyLazy0/blob/main/LICENSE)

  <img src="docs\imgs\output_example.jpg"></img>

</div>


## 1. Requirements

- Linux:
    - Compiler: **g++**>=13
    - Other Softwares: **cmake**>=3.21, **make**
    - IDE: **vscode** (optional, recommended)
- Windows:
    - Compiler: **MSVC**>=19, **clang++**>=18
    - Other Softwares: **cmake**>=3.21
    - IDE: **vscode** (optional, recommended)

Check [Env Setup Guide for Linux](./docs/Env_Setup_Guide_for_Linux.md) or [Env Setup Guide for Windows](./docs/Env_Setup_Guide_for_Windows.md) for more details.

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

#### On UNIX-based Systems:
```bash
$ bash scripts/build-libs.sh
```
#### On Windows:
```powershell
> powershell .\scripts\build-libs.ps1
```

The generated libs should be in `./libs` directory.

### 4.2. Build the MySort

Run following command to build MySort:

#### On UNIX-based Systems:
```bash
$ bash scripts/build.sh
```
#### On Windows:
```powershell
> powershell .\scripts\build.ps1
```

You will find a binary file in `./bin` directory.

### 4.3. Testing

Just execute the binary file and the results will be printed on the screen.
