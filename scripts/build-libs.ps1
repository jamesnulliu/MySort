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

$YUTILS_HOME = "$PROJ_HOME\vendor\Yutils"
if (Test-Path $YUTILS_HOME) {
    & git submodule update --remote
} else {
    & git submodule update --init --recursive
}

Set-Location $YUTILS_HOME
& powershell ./scripts/build.ps1 Release --libo "$PROJ_HOME\lib"
Set-Location $PROJ_HOME