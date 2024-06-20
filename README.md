<div align="center">

  <h1> MySort -  Some Basic Sort Algos and Simple Test Patterns </h1>
  
  ![Static Badge](https://img.shields.io/badge/C%2B%2B-23-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/gcc-13-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/msvc-19-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/clang-18-blue?style=plastic) ![Static Badge](https://img.shields.io/badge/cmake-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) ![Static Badge](https://img.shields.io/badge/make-navy?style=plastic&link=https%3A%2F%2Fgithub.com%2Fjamesnulliu%2FPrettyLazy0%2Fblob%2Fmain%2FLICENSE) [![license - Apache-2.0](https://img.shields.io/badge/license-Apache--2.0-darkgreen?style=plastic)](https://github.com/jamesnulliu/PrettyLazy0/blob/main/LICENSE)

  <img src="docs\imgs\output_example.jpg"></img>

</div>


## 1. Implemented Algorithm
1. bubble sort (origin / stop when no swap happens / narrow the boundary / narrow the boundary in both directions)
2. insertion sort
3. selection sort
4. merge sort
5. quick sort
   - Hoare (primitive / randomly choose pivot / insertion sort)
   - Lomuto (primitive / tail recursion optimization / randomly choose pivot / handel duplicated sequence)
6. ...

## 2. Environment Setup

- Linux:
    - Compiler: **g++**>=13
    - Other Softwares: **cmake**>=3.21, **make**
    - IDE: **vscode** (optional, recommended)
- Windows:
    - Compiler: **MSVC**>=19, **clang++**>=18
    - Other Softwares: **cmake**>=3.21
    - IDE: **vscode** (optional, recommended)

We strongly recommand to check [Env Setup Guide for Linux](./docs/Env_Setup_Guide_for_Linux.md) or [Env Setup Guide for Windows](./docs/Env_Setup_Guide_for_Windows.md) for more a detailed guide.


## 3. Quick Start
### 3.1. Build the Required Libs

Run following command to build the required libs:

#### UNIX-based Systems:
```bash
bash scripts/build-libs.sh
```
#### Windows:
```powershell
powershell .\scripts\build-libs.ps1
```

The generated libs should be in `./libs` directory.

### 3.2. Build the MySort

Run following command to build MySort:

#### On UNIX-based Systems:
```bash
bash scripts/build.sh
```
#### On Windows:
```powershell
powershell .\scripts\build.ps1
```

You will find a binary file in `./bin` directory.

### 3.3. Testing

Just execute the binary file and the results will be printed on the screen.
