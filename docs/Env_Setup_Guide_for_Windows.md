# Env Setup Guide for Windows

## 1. Install PowerShell 7

Open `terminal` and run the following command:

```cmd
winget install --id Microsoft.Powershell --source winget
```

> Note: Default PowerShell on your windows is not PowerShell 7. We recommend using PowerShell 7 for better compatibility.

Open `terminal` and go to `settings`; In `Startup` section, change the `Default profile` to `PowerShell 7`.

![terminal settings](imgs/pwsh-settings.png)

By default, Powershell may forbid user or process to run scripts for safety reasons. Run following commands to change execution policy to allow running scripts:

```powershell
# Set Execution Policy for CurrentUser
Set-ExecutionPolicy -ExecutionPolicy RemoteSigned -Scope CurrentUser -Force

# Set Execution Policy for Process
[System.Environment]::SetEnvironmentVariable('PSExecutionPolicyPreference', 'RemoteSigned', [System.EnvironmentVariableTarget]::User)
```

## 2. Install Scoop Package Manager

Run the following commands from a regular (non-admin) PowerShell terminal to install Scoop:

```powershell
irm get.scoop.sh -outfile 'install.ps1'

.\install.ps1
```

## 3. Install Required Packages

```powershell
# Can be ignored if you already have git installed
scoop install main/git  
# Build essentials
scoop install main/llvm   # clang
scoop install main/cmake  # cmake
scoop install main/ninja  # Ninja
```

Download and install MSVC and Microsoft C++ Build Tools from the [official website](https://visualstudio.microsoft.com/visual-cpp-build-tools/).

![visual studio installer](imgs/Microsoft_C++_Build_Tools_Installer.png)

Make sure to install AT LEAST the following components:

- Windows 11 SDK
- MSVC v143 - VS 2022 C++ x64/x86 build tools (v14.30)

If you want a more integrated development environment of Visual Studio, you can simply select `Desktop development with C++` under `Workloads` and then start the installation.

If you missed any of the components, you can modify the installation by running the `Visual Studio Installer`.