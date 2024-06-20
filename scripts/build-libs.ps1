# # Build with MSVC
# $env:CC="cl"
# $env:CXX="cl"
# # Build with GCC
# $env:CC="gcc"
# $env:CXX="g++"
# Build with Clang
$env:CC="clang"
$env:CXX="clang++"

$PROJ_HOME = Get-Location

# Update and Init all submodules
& git submodule update --init --recursive

$YUTILS_HOME = "$PROJ_HOME\vendor\Yutils"
Set-Location $YUTILS_HOME
& powershell ./scripts/build.ps1 Release --libo "$PROJ_HOME\lib"
Set-Location $PROJ_HOME